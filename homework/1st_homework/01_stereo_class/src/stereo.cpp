#include "stereo.h"

// StereoCompute Constructor
StereoCompute::StereoCompute(cv::Mat in_image1, cv::Mat in_image2, stereo_params in_params)
{
    getData(in_image1, in_image2, in_params);
}


/**
 * Initializes the object with the 2 images and the parameters
 *
 * @param[in]   image1 image1 data
 * @param[in]   image2 image1 data
 * @param[in]   in_params image set parameters
 * 
 */
void StereoCompute::getData(cv::Mat in_image1, cv::Mat in_image2, stereo_params in_params)
{
    // TODO perform checks on params
    image1 = in_image1;
    image2 = in_image2;
    params = in_params;
    std::cout << "We entered get data" << std::endl;
}


/**
 * Calculates the disparity matrix based on the 
 * naive approach
 *
 * @return      naive_disp  matrix of disparities
 */
cv::Mat StereoCompute::getStereoNaive()
{
    int height = image1.size().height;
    int width = image1.size().width;

    naive_disp = cv::Mat::zeros(height, width, CV_8UC1);

    int half_window_size = window_size / 2;
    int progress = 0;
  
#pragma omp parallel for

    for (int i = half_window_size; i < height - half_window_size; ++i) 
    {
    
#pragma omp critical
    {
        ++progress;
        std::cout
            << "Calculating disparities for the naive approach... "
            << std::ceil(((progress) / static_cast<double>(height - window_size + 1)) * 100) << "%\r"
            << std::flush;
      }
        for (int j = half_window_size; j < width - half_window_size; ++j) 
        {
            int min_ssd = INT_MAX;
            int disparity = 0;

            for (int d = -j + half_window_size; d < width - j - half_window_size; ++d) 
            {
                int ssd = 0;
                for (int v = -half_window_size; v <= half_window_size; ++v) {
                    for (int u = -half_window_size; u <= half_window_size; ++u) {

                        int pixel_1 = image1.at<uchar>(i + v, j + u);
                        int pixel_2 = image2.at<uchar>(i + v, j + u + d);

                        ssd += (pixel_1-pixel_2)*(pixel_1-pixel_2);
                    }
                }

                if (ssd < min_ssd) {
                    min_ssd = ssd;
                    disparity = d;
                }
            }
            naive_disp.at<uchar>(i - half_window_size, j - half_window_size) = std::abs(disparity);
        }
    }
    std::cout << "Calculating disparities for the naive approach... Done.\r" << std::flush;
    std::cout << std::endl;

    return naive_disp;
}


/**
 * Calculates the disparity matrix based on the 
 * dynamic approach
 *
 * @return      dynamic_disp  matrix of disparities
 */
cv::Mat StereoCompute::getStereoDynamic()
{
    int half_window_size = window_size / 2;
    int progress = 0;

    dynamic_disp = cv::Mat::zeros(height, width, CV_8UC1);

#pragma omp parallel for

    // for each row (scanline)
    for (int y_0 = half_window_size; y_0 < height - half_window_size; ++y_0) {  

#pragma omp critical
        {
            ++progress;
            std::cout
                << "Calculating disparities for the DP approach... "
                << std::ceil(((progress) / static_cast<double>(height - window_size + 1)) * 100) << "%\r"
                << std::flush;
        }

        //dissimilarity (i,j) for each (i,j)
        cv::Mat dissim = cv::Mat::zeros(width, width, CV_32FC1);
        for (int i = half_window_size; i < width - half_window_size; ++i) { // left image
            for (int j = half_window_size; j < width - half_window_size; ++j) { // right image                                         
                
                // options: SSD, SAD, ...          
                               
                float sum = 0;

                for (int u = -half_window_size; u <= half_window_size; ++u) {       // row
                    for (int v = -half_window_size; v <= half_window_size; ++v) {     // column
                        // Calculating the difference btw the pixels
                        float i1 = image1.at<uchar>(y_0 + v, i + u);
                        float i2 = image2.at<uchar>(y_0 + v, j + u);
                        float diff = (i1 - i2);

                        sum += std::abs(diff);                  // we use SAD as the cost function
                        //sum += (diff*diff);                   // If we want to use SSD
                    }
                }
                dissim.at<float>(i, j) = sum;
            }
        }

        //allocate C,M
        // ... but can you save some computation here....? (TODO)
        // match 0, left-occlusion 1, right-occulsion 2, CV_8UC1
        cv::Mat C = cv::Mat::zeros(width, width, CV_32FC1);                                                                
        cv::Mat M = cv::Mat::zeros(width, width, CV_8UC1);    
        
        for (int i = 0; i < width; ++i) {
            M.at<uchar>(0, i) = 2;
        }
        
        for (int i = 0; i < width; ++i) {
            M.at<uchar>(i, 0) = 1;
        }

        //float C_right = 0;
        //float C_left = 0;
        
        for (int i = 1; i < width; ++i) {
            for (int j = 1; j < width; ++j) {

                float min = FLT_MAX;
                int index = 0;
                float C_eval[3];


                C_eval[0] = C.at<float>(i - 1, j - 1) + dissim.at<float>(i, j);
                C_eval[2] = C.at<float>(i, j - 1) + lambda;
                C_eval[1] = C.at<float>(i - 1, j) + lambda;

                for (int n = 0; n < 3; ++n) {
                    if (C_eval[n] < min) {
                        min = C_eval[n];
                        index = n;
                    }
                }

                C.at<float>(i, j) = min;
                M.at<uchar>(i, j) = index;
            }
        }
        
        int i = width - half_window_size;
        int j = width - half_window_size;
        
        cv::Mat path = cv::Mat::zeros(2 * width, 2, CV_32SC1);

        int counter = 0;

        while (i > half_window_size && j > half_window_size) {
            int val = M.at<uchar>(i, j);

            int disp = 4*std::abs(j - i);
            if (disp > 255) {
                disp = 255;
            }

            path.at<int>(counter, 0) = i;
            path.at<int>(counter, 1) = j;
          
            counter++;

            // match
            if (val == 0) {                
                --i;
                --j;
                dynamic_disp.at<uchar>(y_0, j) = disp;
            }

            // left occlusion
            else if (val==1) {      
                i--;
            }

            // Right occlusion
            else if (val == 2) {
                j--;
                dynamic_disp.at<uchar>(y_0, j) = dynamic_disp.at<uchar>(y_0, j + 1);
            }  
        }
        
        counter--;
        
        for (int i = counter; i > 0; i--) {
            int x = path.at<int>(i, 0);
            int y = path.at<int>(i, 1);

            if (M.at<uchar>(x, y) == 1) {
               
                dynamic_disp.at<uchar>(y_0, y) = dynamic_disp.at<uchar>(y_0, y-1);               
            }       
        }
    }

    return dynamic_disp;
}

/**
 * Calculates pointcloud from the disparity matrix
 *
 * @param[in]   disparityMatrix
 * @return point cloud as std::stringstream (.xyz format)
 */
std::stringstream StereoCompute::getPointCloud(cv::Mat disparityMatrix)
{
    std::stringstream out3d;
    out3d << output_file << ".xyz";
    std::ofstream outfile(out3d.str());
    for (int i = 0; i < height - window_size; ++i) 
    {
        std::cout << "Reconstructing 3D point cloud from disparities... " << std::ceil(((i) / static_cast<double>(height - window_size + 1)) * 100) << "%\r" << std::flush;
        for (int j = 0; j < width - window_size; ++j)
        {
            if (disparities.at<uchar>(i, j) == 0) continue;   

            const double disp = disparities.at<uchar>(i, j) + dmin;
            double u1 = j - width / 2;
            double u2 = u1 + disp;
            double v = i - height / 2;

            const double Z = baseline * focal_length / disp;
            const double X = -baseline * (u1 + u2) / (2 * disp);
            const double Y = baseline * v / disp;

            outfile << X << " " << Y << " " << Z << std::endl;
        }
  }

    std::cout << "Reconstructing 3D point cloud from disparities... Done.\r" << std::flush;
    std::cout << std::endl;

    return out3d;
}

/**
 * Calculates the oriented pointcloud from the disparity matrix
 *
 * @param[in]   disparityMatrix
 * @return      point cloud as std::stringstream (.ply format)
 */
void StereoCompute::getOrientedPointCloud(cv::Mat disparityMatrix)
{
    // TODO
}

/**
 * Saves cv::Mat image as a file with name file_name  
 *
 * @param[in]   image cv::Mat
 * @param[in]   file_name std::string
 */
void saveImage(cv::Mat image, std::string file_name)
{
    // TODO
}

/**
 * Displays image to the user 
 *
 * @param[in]   image cv::Mat
 */
void viewImage(cv::Mat image)
{
    // TODO
}