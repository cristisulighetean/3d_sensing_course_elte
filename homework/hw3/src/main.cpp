#include <fstream>
#include <iostream>
#include <chrono> 
#include <random>
#include "utils.hpp"

using namespace std;
using namespace std::chrono;

const int MAX_ITERATIONS = 50;
string OUTPUT_FILE = ("OUTPUT.xyz");
const double ERROR_DROP_THRESH = 0.0001;
const bool APPLY_OFFSET_AND_GAUSSIAN_ON_SECOND_CLOUD = 1;

int main(int argc, char** argv) {

    // Handling arguments
    if (argc != 5) {
        std::cerr << "Invalid number of arguments. 6 arguments expected:\npointCloud1 pointCloud2 rotDeg gaussianNoiseLevel" << std::endl;
        return 1;
    }

    std::vector<cv::Point3d> points1, points2;
    if (!loadXYZCloudPointFromFile(argv[1], points1)) {
        std::cerr << "Failed to load point cloud 1" << std::endl;
        return 1;
    }

    if (!loadXYZCloudPointFromFile(argv[2], points2)) {
        std::cerr << "Failed to load point cloud 2" << std::endl;
        return 1;
    }
     
    float rotAngle  = std::stof(argv[3]);
    float gaussianNoiseLevel = std::stof(argv[4]);

    Eigen::MatrixXf src(points1.size(), 3);
    for (int i = 0; i < points1.size(); i++) {
        src(i, 0) = points1[i].x;
        src(i, 1) = points1[i].y;
        src(i, 2) = points1[i].z;
    }

    ofstream outputFile3("/src.xyz");
    for (int g = 0; g < src.rows(); g++) {
        for (int gh = 0; gh < 3; gh++) {
            outputFile3 << src(g, gh) << " ";
        }
        outputFile3 << endl;
    }
    outputFile3.close();


    Eigen::MatrixXf dst(points2.size(), 3);
    Eigen::MatrixXf noiseRotation = Eigen::MatrixXf::Zero(3, 3);

    //Add noisy rotation on Y axis
    double angle = rotAngle * (M_PI / 180);
    noiseRotation << cos(angle), 0, sin(angle),
                         0, 1, 0,
                        -sin(angle), 0, cos(angle);


    // offsets the second pointcloud with static and gaussian offsets
    if (APPLY_OFFSET_AND_GAUSSIAN_ON_SECOND_CLOUD) {
        random_device rd; 
        normal_distribution<float> d(0, gaussianNoiseLevel);
        mt19937 gen(rd());
      
        float sample;
        Eigen::MatrixXf data2 = Eigen::MatrixXf::Zero(3, 1);
        for (int i = 0; i < points2.size(); i++) {
            sample = d(gen);
            data2(0, 0) = points2[i].x;
            data2(1, 0) = points2[i].y;
            data2(2, 0) = points2[i].z;

            data2 = noiseRotation * data2;

            dst(i, 0) = data2(0, 0) + sample;
            dst(i, 1) = data2(1, 0) + sample;
            dst(i, 2) = data2(2, 0) + sample;
            
        }
    }
    else {
        for (int i = 0; i < points2.size(); i++) {
            dst(i, 0) = points2[i].x;
            dst(i, 1) = points2[i].y;
            dst(i, 2) = points2[i].z;
        }
    }

    ofstream outputFile("dst.xyz");
    for (int g = 0; g < dst.rows(); g++) {
        for (int gh = 0; gh < 3; gh++) {
            outputFile << dst(g, gh) << " ";
        }
        outputFile << endl;
    }
    outputFile.close();


    Eigen::MatrixXf out(dst.rows(), 3);
 
    auto start = high_resolution_clock::now();
    icp(src, dst, out, MAX_ITERATIONS, ERROR_DROP_THRESH);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Finished in " + to_string(duration.count()) + "ms and saved result into: " + OUTPUT_FILE << endl;

    // save the result into output file
    ofstream outputFile1(OUTPUT_FILE);
    for (int g = 0; g < src.rows(); g++) {
        for (int gh = 0; gh < 3; gh++) {
            outputFile1 << out(g, gh) << " ";
        }
        outputFile1 << endl;
    }
    outputFile1.close();
    return 0;
}


