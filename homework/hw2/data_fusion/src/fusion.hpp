#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>


/**
 * Creates a gaussian kernel based on a window size and sigma
 * 
 * @param[in]   window_size int
 * @param[in]   sigma float
 * 
 * @returns     kernel  
 */
cv::Mat createGaussianKernel(int window_size, float sigma = 1)
{
    // Initialize the kernel with size window_size x window_size, of type float
    cv::Mat kernel(window_size, window_size, CV_32FC1);
    double sum = 0.0;

    // Calculate the Gaussian kernel values based on the window size and sigma
    for (int i = 0; i < window_size; i++) {
        for (int j = 0; j < window_size; j++) {
            double exp_term = -(i * i + j * j) / (2 * sigma * sigma);
            double gaussian_value = exp(exp_term) / (2 * M_PI * sigma * sigma);
            kernel.at<float>(i, j) = gaussian_value;
            sum += gaussian_value;
        }
    }

    // Normalize the values of the kernel to sum up to 1
    for (int i = 0; i < window_size; i++) {
        for (int j = 0; j < window_size; j++) {
            kernel.at<float>(i, j) /= sum;
        }
    }

    return kernel;
}



/**
 * Apply gaussian filter to an image 
 *
 * @param[in]   image cv::Mat
 * @param[in]   factor float
 * 
 * @returns     output filtered image
 */
cv::Mat applyGausianFilter(const cv::Mat& image)
{
    // Output image with the same size and type as the input
    cv::Mat output(image.size(), image.type());
    
    // Get image width and height
    const auto width = image.cols;
    const auto height = image.rows;
    
    // Gaussian window size
    const int window_size = 5;
    
    // Create a Gaussian kernel
    cv::Mat gaussianKernel = createGaussianKernel(window_size);
    
    // Initialize the output image to 0
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            output.at<uchar>(r, c) = 0;
        }
    }
    
    // Go over the image
    for (int r = window_size / 2; r < height - window_size / 2; ++r) {
        for (int c = window_size / 2; c < width - window_size / 2; ++c) {
            
            // Convolve the current pixel with the Gaussian kernel
            int sum = 0;
            for (int i = -window_size / 2; i <= window_size / 2; ++i) {
                for (int j = -window_size / 2; j <= window_size / 2; ++j) {
                    sum += image.at<uchar>(r + i, c + j) * 
                    gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);
                }
            }
            
            // Store the result in the output image
            output.at<uchar>(r, c) = sum;
        }
    }
    
    return output;
}

/**
 * Apply bilateral filter to an image 
 *
 * @param[in]   image cv::Mat
 * @param[in]   window_size const int
 * @param[in]   spatial_sigma const int
 * @param[in]   spectral_sigma const int
 * 
 * @returns     output filtered image
 */
cv::Mat applyBilateralFilter(const cv::Mat& image, 
                            int window_size, 
                            float spatial_sigma, 
                            float spectral_sigma)
{
    // Get image size
    const int width = image.cols;
    const int height = image.rows;

    // Create the output matrix with the same size and type as the input image
    cv::Mat output(image.size(), image.type());

    // Create the Gaussian spatial filter kernel
    cv::Mat gaussianKernel = createGaussianKernel(window_size, spatial_sigma);

    // Clear the output matrix with zeros
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            output.at<uchar>(r, c) = 0;
        }
    }

    // Function to calculate the absolute difference between two values
    auto range_difference = [](float a, float b) {
        return std::abs(a - b);
    };

    // Function to calculate the weight for each pixel based on its range difference and sigma
    auto weighting_function = [](float val, float sigma) {
        const float sigmaSq = sigma * sigma;
        const float normalization = std::sqrt(2 * M_PI) * sigma;
        return (1 / normalization) * std::exp(-val / (2 * sigmaSq));
    };

    // Apply the bilateral filter
    for (int r = window_size / 2; r < height - window_size / 2; ++r) {
        for (int c = window_size / 2; c < width - window_size / 2; ++c) {

            // Variables to store the sum of weighted values and the sum of weights
            float sum_w = 0;
            float sum = 0;

            // Apply the filter for each pixel in the window
            for (int i = -window_size / 2; i <= window_size / 2; ++i) {
                for (int j = -window_size / 2; j <= window_size / 2; ++j) {

                    // Calculate the range difference (range kernel) between the center pixel and the current pixel
                    float range_difference = range_difference(image.at<uchar>(r, c), image.at<uchar>(r + i, c + j));

                    // Calculate the weight for the current pixel
                    float w = weighting_function(range_difference, spectral_sigma) * gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);

                    // Accumulate the weighted values and the weights
                    sum += image.at<uchar>(r + i, c + j) * w;
                    sum_w += w;
                }
            }

            // Calculate the weighted average for the center pixel
            output.at<uchar>(r, c) = sum / sum_w;
        }
    }
    return output;
}


/**
 * Apply JB filter to an image 
 *
 * @param[in]   input_rgb cv::Mat
 * @param[in]   input_depth cv::Mat
 * @param[out]  output cv::Mat
 * @param[in]   window_size int
 * @param[in]   sigma float
 * 
 * @returns     resized_image  
 */
cv::Mat applyJointBilateralFilter(const cv::Mat& input_rgb, const cv::Mat& input_depth, cv::Mat& output, 
            const int window_size, float sigma)
{
	// convert bilateral filter to Guided Joint bilateral filter for guided image upsampling 
	// upsample low resolution depth image guided by RGB image
	// form weights using colors (input_rgb) and filter by modifying depth (input_depth)
	const int width = input_rgb.cols;
	const int height = input_rgb.rows;

	cv::Mat gaussianKernel = createGaussianKernel(window_size, 0.5); // spatial filter sigma

	auto range_difference = [](float a, float b) {
		return std::abs(a - b);
	};

	auto weighting_function = [](float val, float sigma) {	
		// assign lower weight to dissimilar pixels, preserve strong edges, smooth other regions
		const float sigmaSq = sigma * sigma;
		const float normalization = std::sqrt(2 * M_PI) * sigma;
		return (1 / normalization) * std::exp(-val / (2 * sigmaSq));
	};

	for (int r = window_size / 2; r < height - window_size / 2; ++r) {
		for (int c = window_size / 2; c < width - window_size / 2; ++c) {

			float sum_w = 0;
			float sum = 0;

			for (int i = -window_size / 2; i <= window_size / 2; ++i) {
				for (int j = -window_size / 2; j <= window_size / 2; ++j) {

					float rd = range_difference(input_rgb.at<uchar>(r, c), input_rgb.at<uchar>(r + i, c + j)); // use RGB image with spectral filter

					float w = weighting_function(rd, sigma) * gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);

					sum += input_depth.at<uchar>(r + i, c + j) * w; // use depth image with spatial filter
					sum_w += w;
				}
			}
			output.at<uchar>(r, c) = sum / sum_w;
		}
	}
	return output;
}


/**
 * Perform Iterative upsampling on an RGB image using the depth map
 * Algorithm is performed according to the pseudo-code representation
 * in Lecture 4
 *
 * @param[in]   input_rgb cv::Mat
 * @param[in]   input_depth cv::Mat
 * 
 * @returns     D output image  
 */
cv::Mat performIterativeUpsampling(const cv::Mat& input_rgb, const cv::Mat& input_depth)
{
	// Logarithmic upsample factor
	int uf = log2(input_rgb.rows / input_depth.rows);

	// Low-resolution depth image
	cv::Mat D = input_depth.clone(); 

	// High-resolution RGB image
	cv::Mat I = input_rgb.clone(); 

	// Iteratively applying the joint bilateral filter
	for (int i = 0; i < uf; ++i)
	{
		// Doubling the size of the depth image
		cv::resize(D, D, D.size() * 2); 

		// Resizing the RGB image to the depth image size
		cv::resize(I, I, D.size());

		// Applying the joint bilateral filter with the changed size images
		applyJointBilateralFilter(I, D, D, 5, 0.1); 
	}
	// Resizing the depth image to the RGB image size
	cv::resize(D, D, input_rgb.size()); 

	// Final application of the joint bilateral filter with full resolution images
	applyJointBilateralFilter(input_rgb, D, D, 5, 0.1); 

	// Returning the final depth image
	return D;
}


/**
 * Resizes cv::Mat image according to the provided facor 
 *
 * @param[in]   img cv::Mat
 * @param[in]   factor float
 * 
 * @returns     resized_image  
 */
cv::Mat resizeImage(const cv::Mat& img, double factor = 0.25)
{
    cv::Mat out_image(img.cols * factor, img.rows * factor, img.type());
    cv::resize(img, out_image, cv::Size(img.cols * factor, img.rows * factor), 
                                    0, 0, cv::INTER_LINEAR);
    return out_image;

}

/**
 * Saves cv::Mat image as a file with name file_name  
 *
 * @param[in]   img cv::Mat
 * @param[in]   file_name std::string
 */
void saveImage(cv::Mat& img, std::string file_name)
{
  std::stringstream out;
  out << file_name;
  cv::imwrite(out.str(), img);
}

/**
 * Displays image to the user 
 *
 * @param[in]   img cv::Mat
 */
void viewImage(cv::Mat& img)
{
  cv::imshow("fusion_result", img);
  cv::waitKey(0);
}
    

/* Evaluation functions */

/**
 * Returns Sum of squared errors
 *
 * @param[in]   img1 cv::Mat
 * @param[in]   img2 cv::Mat
 * 
 * @returns     ssd value
 */
double SSD(const cv::Mat& img1, const cv::Mat& img2)
{
	double ssd = 0;
	double diff = 0;
	for (int r = 0; r < img1.rows; ++r) {
		for (int c = 0; c < img1.cols; ++c) {
			diff = img1.at<uchar>(r, c) - img2.at<uchar>(r, c);
			ssd += diff * diff;
		}
	}
	return ssd;
}


/**
 * Returns Root mean squared error
 *
 * @param[in]   img1 cv::Mat
 * @param[in]   img2 cv::Mat
 * 
 * @returns     rmse value
 */
double RMSE(const cv::Mat& img1, const cv::Mat& img2)
{
	int size = img1.rows * img1.cols;
	double ssd = 0;
	double diff = 0;
	for (int r = 0; r < img1.rows; ++r) {
		for (int c = 0; c < img1.cols; ++c) {
			diff = img1.at<uchar>(r, c) - img2.at<uchar>(r, c);
			ssd += diff * diff;
		}
	}
	double mse = (double)(ssd / size);
	return sqrt(mse);
}


/**
 * Returns Mean squared error
 *
 * @param[in]   img1 cv::Mat
 * @param[in]   img2 cv::Mat
 * 
 * @returns     mse value 
 */
double MSE(const cv::Mat& img1, const cv::Mat& img2)
{
	int size = img1.rows * img1.cols;
	double ssd = 0;
	double diff = 0;
	for (int r = 0; r < img1.rows; ++r) {
		for (int c = 0; c < img1.cols; ++c) {
			diff = img1.at<uchar>(r, c) - img2.at<uchar>(r, c);
			ssd += diff * diff;
		}
	}
	double mse = (double)(ssd / size);
	return mse;
}


/**
 * Returns Peak signal-to-noise ratio
 *
 * @param[in]   img1 cv::Mat
 * @param[in]   img2 cv::Mat
 * 
 * @returns     psnr value 
 */
double PSNR(const cv::Mat& img1, const cv::Mat& img2)
{
	double max = 255;
	int size = img1.rows * img1.cols;
	double ssd = 0;
	double diff = 0;
	for (int r = 0; r < img1.rows; ++r) {
		for (int c = 0; c < img1.cols; ++c) {
			diff = img1.at<uchar>(r, c) - img2.at<uchar>(r, c);
			ssd += diff * diff;
		}
	}
	double mse = (double)(ssd / size);
	double psnr = 10 * log10((max * max) / mse);
	return psnr;
}


/**
 * Returns mean value of image
 *
 * @param[in]   img cv::Mat
 * 
 * @returns     mean  
 */
long double mean(const cv::Mat& img)
{
	long double sum = 0;
	int size = img.rows * img.cols;
	for (int r = 0; r < img.rows; ++r) {
		for (int c = 0; c < img.cols; ++c) {
			sum += img.at<uchar>(r, c);
		}
	}
	return sum / size;
}


/**
 * Returns variance value of image
 *
 * @param[in]   img cv::Mat
 * 
 * @returns     variance  
 */
long double variance(const cv::Mat& img)
{
	cv::Mat var_matrix = img.clone();
	long double sum = 0;
	int size = var_matrix.rows * var_matrix.cols;
	long double mean_ = mean(var_matrix);

	for (int r = 0; r < var_matrix.rows; ++r) {
		for (int c = 0; c < var_matrix.cols; ++c) {
			var_matrix.at<uchar>(r, c) -= mean_;
			var_matrix.at<uchar>(r, c) *= var_matrix.at<uchar>(r, c);
		}
	}

	for (int r = 0; r < var_matrix.rows; ++r) {
		for (int c = 0; c < var_matrix.cols; ++c) {
			sum += var_matrix.at<uchar>(r, c);
		}
	}
	return sum / size;
}

/**
 * Returns covariance value between the 2 images
 *
 * @param[in]   img1 cv::Mat
 * @param[in]   img2 cv::Mat
 * 
 * @returns     variance  
 */
long double covariance(const cv::Mat& img1, const cv::Mat& img2)
{
	int size = img1.rows * img1.cols;
	long double sum = 0;
	long double mean1 = mean(img1);
	long double mean2 = mean(img2);
	for (int r = 0; r < img1.rows; ++r) {
		for (int c = 0; c < img1.cols; ++c) {
			sum = sum + ((img1.at<uchar>(r, c) - mean1) * (img2.at<uchar>(r, c) - mean2));
		}
	}
	return sum / size;
}

/**
 * Returns Structural Similarity Index of an image
 *
 * @param[in]   img1 cv::Mat
 * @param[in]   img2 cv::Mat
 * 
 * @returns     ssim value  
 */
long double SSIM(const cv::Mat& img1, const cv::Mat& img2)
{
	long double ssim = 0;
	long double k1 = 0.01, k2 = 0.03, L = 255;
	long double C1 = (k1 * L) * (k1 * L);
	long double C2 = (k2 * L) * (k2 * L);

	long double mu_x = mean(img1);
	long double mu_y = mean(img2);
	long double variance_x = variance(img1);
	long double variance_y = variance(img2);
	long double covariance_xy = covariance(img1, img2);

	ssim = ((2 * mu_x * mu_y + C1) * (2 * covariance_xy + C2)) / ((mu_x * mu_x + mu_y * mu_y + C1) * (variance_x * variance_x + variance_y * variance_y + C2));
	return ssim;
}