#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <Eigen/Dense>
#include "math.h"
#include "nanoflann.hpp"

using namespace std;
using namespace cv;
using namespace nanoflann;
using namespace std::chrono;

const int K_NEIGHBORS = 5;
const double ICP_ERROR_LOW_THRESH = 0.01;

/**
 * It takes two point clouds, `cloud1` and `cloud2`, and finds the `k` nearest neighbors of each point
 * in `cloud2` in `cloud1`
 * 
 * @param cloud1 The first point cloud.
 * @param cloud2 The query points.
 * @param k The number of nearest neighbors to search for.
 * @param indices A matrix of size (N, k) where N is the number of points in cloud2 and k is the number
 * of nearest neighbors to search for. Each row of indices contains the indices of the k nearest
 * neighbors of the corresponding point in cloud2.
 * @param dists A matrix of size (N, k) where N is the number of points in cloud2 and k is the number
 * of nearest neighbors to search for. Each row of dists contains the distances to the k nearest
 * neighbors of the corresponding point in cloud2.
 */
void searchNN(const Eigen::MatrixXf& cloud1, const Eigen::MatrixXf& cloud2, const size_t k, Eigen::MatrixXi& indices, Eigen::MatrixXf& dists) {
    // Maximum number of points in a leaf node of KDTree
    const int max_leaf = 10;

    // Extract first 3 columns from cloud1 and cloud2 as coordinates
    auto coords1 = cloud1.leftCols(3);
    auto coords2 = cloud2.leftCols(3);

    // Create KDTree for `coords1`
    using KDTree = nanoflann::KDTreeEigenMatrixAdaptor<decltype(coords1)>;
    KDTree mat_index(3, coords1, max_leaf);
    // Build KDTree index
    mat_index.index->buildIndex();

    // Resize indices and dists matrices to store KNN results
    indices.resize(cloud2.rows(), k);
    dists.resize(cloud2.rows(), k);

    // Iterate over each row of `coords2`
    for (int i = 0; i < coords2.rows(); ++i) {
        // Current query point
        Eigen::Vector3f query_pt = coords2.row(i);
        // Stores indices of KNN
        std::vector<size_t> ret_indices(k);
        // Stores distances to KNN
        std::vector<float> out_dists_sqr(k);
        // Result set to store KNN results
        nanoflann::KNNResultSet<float> resultSet(k);
        resultSet.init(&ret_indices[0], &out_dists_sqr[0]);
        // Find KNN using KDTree
        mat_index.index->findNeighbors(resultSet, query_pt.data(), nanoflann::SearchParams(10));
        // Store KNN results in indices and dists matrices
        for (size_t j = 0; j < k; ++j) {
            indices(i, j) = ret_indices[j];
            dists(i, j) = std::sqrt(out_dists_sqr[j]);
        }
    }
}


/**
 * It reads a file containing a list of 3D points and returns them in a vector
 * 
 * @param filePath The path to the file containing the 3D points.
 * @param cloudPoints The vector of 3D points that will be filled with the points from the file.
 * 
 * @return 1 if the file is opened and read correctly, and -1 if the file is not opened correctly.
 */
int loadXYZCloudPointFromFile(const std::string& filePath, std::vector<cv::Point3d>& cloudPoints)
{
    std::ifstream file(filePath);
    if(!file.is_open()) {
        std::cout << "Error opening the xyz file" << std::endl;
        return -1;
    }

    cv::Point3d tmp;
    while (file >> tmp.x && file >> tmp.y && file >> tmp.z) {
        cloudPoints.push_back(tmp);
    }
    file.close();
    return 1;
}


/**
 * > Given two sets of 3D points, find the rotation (R) and translation (t) that best maps the first
 * set to the second
 * 
 * @param A The source points
 * @param B The set of points in the target frame
 * @param R The rotation matrix
 * @param t the translation vector
 * 
 * @return Rotation matrix and translation vector
 */
int bestFitTransformation(const Eigen::MatrixXd &pointsA, const Eigen::MatrixXd &pointsB, Eigen::Matrix3d &rotation, Eigen::Vector3d &translation)
{
    Eigen::Vector3d centroidA(0, 0, 0);
    Eigen::Vector3d centroidB(0, 0, 0);
    Eigen::MatrixXd centeredPointsA = pointsA;
    Eigen::MatrixXd centeredPointsB = pointsB;
    int numPoints = pointsA.rows();

    // Calculate centroids of pointsA and pointsB
    for (int i = 0; i < numPoints; i++) 
    {
        centroidA += pointsA.block<1, 3>(i, 0).transpose();
        centroidB += pointsB.block<1, 3>(i, 0).transpose();
    }
    centroidA /= numPoints;
    centroidB /= numPoints;

    // Center pointsA and pointsB
    for (int i = 0; i < numPoints; i++) 
    {
        centeredPointsA.block<1, 3>(i, 0) = pointsA.block<1, 3>(i, 0) - centroidA.transpose();
        centeredPointsB.block<1, 3>(i, 0) = pointsB.block<1, 3>(i, 0) - centroidB.transpose();
    }

    // Calculate cross-covariance matrix
    Eigen::MatrixXd crossCovariance = centeredPointsA.transpose() * centeredPointsB;
    Eigen::MatrixXd U;
    Eigen::VectorXd S;
    Eigen::MatrixXd V;
    Eigen::MatrixXd Vt;

    // Perform SVD on cross-covariance matrix
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(crossCovariance, Eigen::ComputeFullU | Eigen::ComputeFullV);
    U = svd.matrixU();
    S = svd.singularValues();
    V = svd.matrixV();
    Vt = V.transpose();

    // Calculate rotation matrix
    rotation = Vt.transpose() * U.transpose();

    // Ensure determinant is positive
    if (rotation.determinant() < 0) 
    {
        Vt.block<1, 3>(2, 0) *= -1;
        rotation = Vt.transpose() * U.transpose();
    }

    // Calculate translation vector
    translation = centroidB - rotation * centroidA;

    return 1;
}


/**
 * The function takes in two point clouds, src and dst, and an initial guess of the transformation
 * matrix, src_trans. It then iteratively finds the nearest neighbours of src_trans in dst, and uses
 * the best fit transformation to update src_trans. It repeats this process until the mean error
 * between src_trans and dst is low enough, or the error is dropping fast enough
 * 
 * @param src The source point cloud
 * @param dst The destination point cloud
 * @param src_trans The source point cloud that will be transformed to fit the destination point cloud.
 * @param max_iterations The maximum number of iterations to run ICP for.
 * @param error_drop_thresh The threshold for the change in mean error between iterations. If the
 * change in mean error is less than this threshold, the ICP search will stop.
 * 
 * @return error code
 */
int icp(const Eigen::MatrixXf& src, const Eigen::MatrixXf& dst, 
    Eigen::MatrixXf& src_trans, const int max_iterations, 
    const double error_drop_thresh) {
    
    // Initialize variables
    Eigen::MatrixXi indices;
    Eigen::MatrixXf dists;
    src_trans = src;
    double prev_error = 0;
    float prev_dist_sum = FLT_MAX;

    // Create a matrix to store src points ordered as closest to dst points
    Eigen::MatrixXf src_neighbours(dst.rows(), 3);
    double mean_error = 0;

    // Loop through optimisation until max_iterations is reached or break condition met
    for (int i = 0; i < max_iterations; i++) {
        // Find nearest neighbours in src_trans for each point in dst
        searchNN(src_trans, dst, K_NEIGHBORS, indices, dists);

        // Calculate mean error between src and dst points
        float dist_sum = 0;
        for (int d = 0; d < dists.size(); d++) {
            dist_sum += dists(d);
        }
        mean_error = dist_sum / dists.size();

        // Check if error is dropping fast enough, if not, finish search
        if(abs(prev_error-mean_error) < error_drop_thresh) {
             cout << "ICP has sucessfully reached the necessary error_drop_thresh." << endl;
             return 1;
        }

        // Check if mean error is low enough, if so, finish search
        if (abs(mean_error) < ICP_ERROR_LOW_THRESH) {
            cout << "ICP has sucessfully reached the necessary error_low_thresh." << endl;
            return 1;
        }

        // Reorder src points to fit nearest neighbour scheme
        for (int j = 0; j < src_neighbours.rows(); j++) {
            int ind = indices(j, 1);
            src_neighbours(j, 0) = src_trans(ind, 0);
            src_neighbours(j, 1) = src_trans(ind, 1);
            src_neighbours(j, 2) = src_trans(ind, 2);
        }

        // Find the best fit transformation matrix
        Eigen::Matrix3d tR;
        Eigen::Vector3d tt;
        bestFitTransformation(src_neighbours.cast <double>(), dst.cast <double>(), tR, tt);
        Eigen::Matrix3f R = tR.cast<float>();
        Eigen::Vector3f t = tt.cast<float>();

        // Apply rotation to src_trans
        src_trans = (R * src_trans.transpose()).transpose();

        // Apply translation to src_trans
        for (int fs = 0; fs < src_trans.rows();fs++) {
            for (int a = 0; a < 3; a++) {
                src_trans(fs, a) = src_trans(fs, a) + t(a);
            }
        }

        // Output status update
        cout << "ICP Cycle: " << to_string(i) << endl;
        cout << "MSE: " + to_string(mean_error) + "/" + to_string(ICP_ERROR_LOW_THRESH) << endl;
        cout << "Change of MSE: " + to_string(abs(prev_error - mean_error)) + "/" + to_string(error_drop_thresh) << endl;

        prev_error = mean_error;
        prev_dist_sum = dist_sum;
    }
    return 1;
}

