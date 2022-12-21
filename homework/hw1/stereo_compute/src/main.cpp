#include <opencv2/opencv.hpp>
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include <chrono>
#include "stereo.h"

#define HELP_STRING "How to use it:\n\
  Basic Naive:\t./prog -nv image1 image2 output_name window_size dmin\n\
  Basic DP:\t./prog -dp image1 image2 output_name window_size dmin lambda\n\
  Both modes:\t./prog -nvdp image1 image2 output_name window_size dmin lambda\n\
  Point cloud:\t./prog -pc image1 image2 output_name window_size dmin\n"

int main(int argc, char** argv)
{
  ////////////////
  // Parameters //
  ////////////////

  stereo_params params;
  // Camera setup parameters
  params.focal_length = 3740;
  params.baseline = 160;
  
  ///////////////////////////
  // Handling arguments //
  ///////////////////////////

  // Mode selection
  // 1 - Basic Naive          (./prog -nv image1 image2 output_name window_size dmin)
  // 2 - Basic DP             (./prog -dp image1 image2 output_name window_size dmin lambda)
  // 3 - Basic Naive & DP     (./prog -nvdp image1 image2 output_name window_size dmin lambda)

  int mode = 0;

  if ((argc == 7) && (strcmp( argv[1], "-nv" ) == 0 ))
  {
    // Basic Naive
    mode = 1;
    params.window_size = std::stoi(argv[5]);
    params.dmin = std::stoi(argv[6]);

  }
  else if ((argc == 8) && (strcmp( argv[1], "-dp" ) == 0 ))
  {
    // Basic DP
    mode = 2;
    params.window_size = std::stoi(argv[5]);
    params.dmin = std::stoi(argv[6]);
    params.lambda = std::stoi(argv[7]);
  }
    else if ((argc == 8) && (strcmp( argv[1], "-nvdp" ) == 0 ))
  {
    // Run both modes at once
    mode = 3;
    params.window_size = std::stoi(argv[5]);
    params.dmin = std::stoi(argv[6]);
    params.lambda = std::stoi(argv[7]);
  }
  else if ((argc == 7) && (strcmp( argv[1], "-pc" ) == 0 ))
  {
    // Point cloud calculation
    mode = 4;
    params.window_size = std::stoi(argv[5]);
    params.dmin = std::stoi(argv[6]);
  }
  else
  {
    std::cout << HELP_STRING;
    return 0;
  }
  
  // Handle image data
  cv::Mat in_image1 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
  cv::Mat in_image2 = cv::imread(argv[3], cv::IMREAD_GRAYSCALE);

  // Verify image data
  if (!in_image1.data)
  {
    std::cerr << "No image1 data" << std::endl;
    return 1;
  }

  if (!in_image2.data)
  {
    std::cerr << "No image2 data" << std::endl;
    return 1;
  }

  StereoCompute stereo(in_image1, in_image2, params);
  stereo.output_name = argv[4];

  // Handle modes
  if (mode == 1)
  {
    // Basic naive
    stereo.computeStereoNaive();
  }
  else if (mode == 2)
  {
    // Basic DP
    stereo.computeStereoDynamic();
  }
  else if (mode == 3)
  {
    // Running both modes
    stereo.computeStereoNaive();
    stereo.computeStereoDynamic();
  }
  else if (mode == 4)
  {
    // Point cloud
    stereo.computePointCloud();
  }
  else
  {
    std::cerr << "Unknown mode...return\n";
    return 1;
  }

  return 0;
}


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
    height = image1.size().height;
    width = image1.size().width;
    params = in_params;
}


/**
 * Calculates the disparity matrix based on the 
 * naive approach
 *
 * @return      naive_disp  matrix of disparities
 */
cv::Mat StereoCompute::getStereoNaive()
{
    cv::Mat naive_disp = cv::Mat::zeros(height, width, CV_8UC1);

    int half_window_size = params.window_size / 2;
    int progress = 0;
  
#pragma omp parallel for

    for (int i = half_window_size; i < height - half_window_size; ++i) 
    {
    
#pragma omp critical
    {
        ++progress;
        std::cout
            << "Calculating disparities for the naive approach... "
            << std::ceil(((progress) / static_cast<double>(height - params.window_size + 1)) * 100) << "%\r"
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
    int half_window_size = params.window_size / 2;
    int progress = 0;

    cv::Mat dynamic_disp = cv::Mat::zeros(height, width, CV_8UC1);

#pragma omp parallel for

    // for each row (scanline)
    for (int y_0 = half_window_size; y_0 < height - half_window_size; ++y_0) {  

#pragma omp critical
        {
            ++progress;
            std::cout
                << "Calculating disparities for the DP approach... "
                << std::ceil(((progress) / static_cast<double>(height - params.window_size + 1)) * 100) << "%\r"
                << std::flush;
        }

        //dissimilarity (i,j) for each (i,j)
        cv::Mat dissim = cv::Mat::zeros(width, width, CV_32FC1);
        for (int i = half_window_size; i < width - half_window_size; ++i) { // left image
            for (int j = half_window_size; j < width - half_window_size; ++j) { // right image                                         
                float sum = 0;
                for (int u = -half_window_size; u <= half_window_size; ++u) {    
                    for (int v = -half_window_size; v <= half_window_size; ++v) {    
                        // Calculating the difference btw the pixels
                        float i1 = image1.at<uchar>(y_0 + v, i + u);
                        float i2 = image2.at<uchar>(y_0 + v, j + u);
                        float diff = (i1 - i2);

                        sum += std::abs(diff);                  

                    }
                }
                dissim.at<float>(i, j) = sum;
            }
        }

        cv::Mat C = cv::Mat::zeros(width, width, CV_32FC1);                                                                
        cv::Mat M = cv::Mat::zeros(width, width, CV_8UC1);    
        
        for (int i = 0; i < width; ++i) {
            M.at<uchar>(0, i) = 2;
        }
        
        for (int i = 0; i < width; ++i) {
            M.at<uchar>(i, 0) = 1;
        }
        
        for (int i = 1; i < width; ++i) {
            for (int j = 1; j < width; ++j) {

                float min = FLT_MAX;
                int index = 0;
                float C_eval[3];


                C_eval[0] = C.at<float>(i - 1, j - 1) + dissim.at<float>(i, j);
                C_eval[2] = C.at<float>(i, j - 1) + params.lambda;
                C_eval[1] = C.at<float>(i - 1, j) + params.lambda;

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

            int disp = std::abs(j - i);
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
 * @param[in]   disparity_matrix
 * @return point cloud as std::stringstream (.xyz format)
 */
std::stringstream StereoCompute::getPointCloud(cv::Mat disparity_matrix, std::string file_name)
{
    // Create stringstream object
    std::stringstream out3d;
    out3d << file_name << ".xyz";
    std::ofstream outfile(out3d.str());

    for (int i = 0; i < height - params.window_size; ++i) 
    {
        std::cout << "Reconstructing 3D point cloud from disparities... " 
        << std::ceil(((i) / static_cast<double>(height - params.window_size + 1)) * 100) << "%\r" << std::flush;
        for (int j = 0; j < width - params.window_size; ++j)
        {
            if (disparity_matrix.at<uchar>(i, j) == 0) continue;   

            const double disp = disparity_matrix.at<uchar>(i, j) + params.dmin;
            double u1 = j - width / 2;
            double u2 = u1 + disp;
            double v = i - height / 2;

            const double Z = params.baseline * params.focal_length / disp;
            const double X = -params.baseline * (u1 + u2) / (2 * disp);
            const double Y = params.baseline * v / disp;

            outfile << X << " " << Y << " " << Z << std::endl;
        }
  }

    std::cout << "Reconstructing 3D point cloud from disparities... Done.\r" << std::flush;
    std::cout << std::endl;

    return out3d;
}


/**
 * Entire process of calculating disparities via
 * the naive approach
 * 
 */
void StereoCompute::computeStereoNaive(void)
{
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  cv::Mat naive_disp = getStereoNaive();
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  // Output result and computation data
  std::cout << "Image size: height = " << height <<" width = " << width << "\n";
  std::cout << "Window size: " << params.window_size << "\n";
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;

  saveImage(naive_disp, "_naive");
}


/**
 * Entire process of calculating disparities via
 * the dynamic approach
 * 
 */
void StereoCompute::computeStereoDynamic()
{
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  cv::Mat dp_disp = getStereoDynamic();
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  
  // Output result and computation data
  std::cout << "Image size: height = " << height <<" width = " << width << "\n";
  std::cout << "Window size: " << params.window_size << "\n";
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::miliseconds>(end - begin).count() << "[s]" << std::endl;

  saveImage(dp_disp, "_dynamic");
}


/**
 * Computing and saving point cloud using disparities from the naive 
 * approach
 * 
 */
void StereoCompute::computePointCloud(void)
{
  cv::Mat naive_disp = getStereoNaive();
  saveImage(naive_disp, "_naive");
  getPointCloud(naive_disp, output_name);
}


/**
 * Saves cv::Mat image as a file with name file_name  
 *
 * @param[in]   image cv::Mat
 * @param[in]   file_name std::string
 */
void StereoCompute::saveImage(cv::Mat image, std::string file_name)
{
  std::stringstream out;
  out << output_name << file_name << "_lamb_" << std::to_string(params.lambda) << "_ws_" \
  << std::to_string(params.window_size) << ".png";
  cv::imwrite(out.str(), image);
}

/**
 * Displays image to the user 
 *
 * @param[in]   image cv::Mat
 */
void StereoCompute::viewImage(cv::Mat image)
{
  cv::imshow("Naive", image);
  cv::waitKey(0);
}