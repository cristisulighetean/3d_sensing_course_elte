#include <opencv2/opencv.hpp>
#include <iostream>
#include <string> 
#include <fstream>

struct compute_params
    {
        // Camera setup parameters
        double focal_length;
        double baseline;

        // Stereo estimation parameters
        // Dmin: disparity added due to image cropping
        int dmin;
        int window_size;

        // Image params
        int width;
        int height;

    };

#define HELP_STRING "Usage: ./upsample2PointCloud upsampledImage dmin windowSize\n"

void getPointCloud(cv::Mat upsampledImage, std::string file_name, compute_params params);


int main(int argc, char** argv)
{
 
  compute_params params;
  // Camera setup parameters
  params.focal_length = 3740;
  params.baseline = 160;
  
  // Handle arguments
  cv::Mat image_data = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  std::string file_name = argv[1];
  params.dmin = std::stoi(argv[2]);
  params.window_size = std::stoi(argv[3]);

  // Verify image data
  if (!image_data.data)
  {
    std::cerr << "No image data" << std::endl;
    return 1;
  }

  params.height = image_data.size().height;
  params.width = image_data.size().width;

  getPointCloud(image_data, file_name, params);

  return 0;
}


/**
 * Calculates pointcloud from the disparity matrix
 *
 * @param[in]   upsampledImage
 * @return point cloud as std::stringstream (.xyz format)
 */
void getPointCloud(cv::Mat upsampledImage, std::string file_name, compute_params params)
{
  // Create stringstream object
  std::stringstream out3d;
  out3d << file_name << ".xyz";
  std::ofstream outfile(out3d.str());

  for (int i = 0; i < params.height - params.window_size; ++i) 
  {
    std::cout << "Reconstructing 3D point cloud from disparities... " 
    << std::ceil(((i) / static_cast<double>(params.height - params.window_size + 1)) * 100) << "%\r" << std::flush;
    for (int j = 0; j < params.width - params.window_size; ++j)
    {
      if (upsampledImage.at<uchar>(i, j) == 0) continue;   

      const double disp = upsampledImage.at<uchar>(i, j) + params.dmin;
      double u1 = j - params.width / 2;
      double u2 = u1 + disp;
      double v = i - params.height / 2;

      const double Z = params.baseline * params.focal_length / disp;
      const double X = -params.baseline * (u1 + u2) / (2 * disp);
      const double Y = params.baseline * v / disp;

      outfile << X << " " << Y << " " << Z << std::endl;
    }
  }

  std::cout << "Reconstructing 3D point cloud from disparities... Done.\r" << std::flush;
  std::cout << std::endl;

}