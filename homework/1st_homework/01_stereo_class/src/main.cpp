#include <opencv2/opencv.hpp>
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include "stereo.h"

#define USAGE_STRING "image1 image2 output_file_name"

int main(int argc, char** argv)
{
  ////////////////
  // Parameters //
  ////////////////

  stereo_params params;
  // Camera setup parameters
  params.focal_length = 1247;
  params.baseline = 213;

  // Stereo estimation parameters
  params.dmin = 67;
  params.window_size = 5;
  
  ///////////////////////////
  // Commandline arguments //
  ///////////////////////////

  // Depending on argc, run it with or without lambda param search
  // Basic mode
  if (argc < 4)
  {
    std::cerr << "Usage: " << argv[0] << USAGE_STRING << std::endl;
    return 1;
  }

  // Handle image data and output file name
  cv::Mat image1 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  cv::Mat image2 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
  const std::string output_file = argv[3];

  if (!image1.data)
  {
    std::cerr << "No image1 data" << std::endl;
    return EXIT_FAILURE;
  }

  if (!image2.data)
  {
    std::cerr << "No image2 data" << std::endl;
    return EXIT_FAILURE;
  }

  // Compute naive disparity
  StereoCompute stereo(image1, image2, params);

  return 0;
}