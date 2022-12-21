#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "fusion.hpp"


int main(int argc, char** argv)
{
  
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " folder_path" << std::endl;
    return 1;
  }

  // Load images
  std::string folder_path = argv[1];
  cv::Mat input_rgb = cv::imread(folder_path + "view5.png", 0);
	cv::Mat input_depth = cv::imread(folder_path + "disp5.png", 0);
  cv::Mat mini_depth = resizeImage(input_depth, 0.25);

  // Check for invalid immages
  if (input_rgb.data == nullptr) {
		std::cerr << "Failed to load RGB image" << std::endl;
    return 1;
	}
  if (input_depth.data == nullptr) {
		std::cerr << "Failed to load depth image" << std::endl;
    return 1;
	}

  // Have an original copy of the input
  cv::Mat input_image = input_rgb.clone();

  // Create directory of evaluation results and get path
  // Build command to execute
  std::string str_command = "mkdir -p ";
  str_command = str_command + folder_path + "eval/";
  // Convert string to const char * as system requires
  const char *comman_mk = str_command.c_str();
  std::system(comman_mk);

  // Get path of the eval folder
  std::string eval_path = folder_path + "eval/";

  // Perform the upsampling and save it
  cv::Mat upsampled_image = performUpsampling(input_rgb, mini_depth);
  std::string image_path = eval_path + "upsampled_image.png";
  saveImage(upsampled_image, image_path);

  // Parameters to try out
  std::vector<float> spatial_sigma = { 0.1, 1, 1.5, 3 };
	std::vector<float> spectral_sigma = { 1, 3, 5, 10 };
	
  // Create the file to record the metrics
  uint8_t image_counter = 0;
  std::string eval_results_file_path = eval_path + "eval_results.txt";
  std::ofstream eval_results(eval_results_file_path);

	for (float i : spatial_sigma) {
		for (float j : spectral_sigma) {
      
      // Time the Bilateral filter
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			cv::Mat output_fiter = applyBilateralFilter(input_image, 5, i, j); // implementation of the bilateral filter
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      float processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

      // Compute metrics
      double ssd = SSD(input_image, output_fiter);
			double rmse = RMSE(input_image, output_fiter);
			double psnr = PSNR(input_image, output_fiter);
			double ssim = SSIM(input_image, output_fiter);

      // Write results to file
      eval_results << std::to_string(image_counter) << ",";
      // Parameters evaluated
      eval_results << "spatial_sigma," << std::to_string(i) << ",";
      eval_results << "spectral_sigma," << std::to_string(j) << ",";
      // Write the processing time
      eval_results << "time," << std::to_string(processing_time) << ",us" << ",";
      // Write metric results
      eval_results << "SSD," << std::to_string(ssd) << ",";
      eval_results << "RMSE," << std::to_string(rmse) << ",";
      eval_results << "PSNR," << std::to_string(psnr) << ",";
      eval_results << "SSIM," << std::to_string(ssim);
      eval_results << std::endl;
      
      // Save image
      image_path = eval_path + std::to_string(image_counter) + ".png";
      saveImage(output_fiter, image_path);
      image_counter++; 
		}
	}
  return 0;
}