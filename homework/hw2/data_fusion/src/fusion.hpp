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
	cv::Mat kernel(window_size, window_size, CV_32FC1);
	double i, j, sum = 0.0;

    /* Go over the window*/
	for (i = 0; i < window_size; i++) {
		for (j = 0; j < window_size; j++) {
			kernel.at<float>(i, j) = exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
			sum += kernel.at<float>(i, j);
		}
	}

	for (i = 0; i < window_size; i++) {
		for (j = 0; j < window_size; j++) {
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
	cv::Mat output(image.size(), image.type());
	const auto width = image.cols;
	const auto height = image.rows;
	const int window_size = 5;
	cv::Mat gaussianKernel = createGaussianKernel(window_size);
	for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			output.at<uchar>(r, c) = 0;
		}
	}

	for (int r = window_size / 2; r < height - window_size / 2; ++r) {
		for (int c = window_size / 2; c < width - window_size / 2; ++c) {

			int sum = 0;
			for (int i = -window_size / 2; i <= window_size / 2; ++i) {
				for (int j = -window_size / 2; j <= window_size / 2; ++j) {
					sum += image.at<uchar>(r + i, c + j) * 
                    gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);
				}
			}
			output.at<uchar>(r, c) = sum;
		}
	}
	return output;
}

/**
 * Apply gaussian filter to an image 
 *
 * @param[in]   image cv::Mat
 * @param[in]   window_size const int
 * @param[in]   spatial_sigma const int
 * @param[in]   spectral_sigma const int
 * 
 * @returns     output filtered image
 */
cv::Mat applyBilateralFilter(const cv::Mat& image, 
                            const int window_size = 5, 
                            float spatial_sigma = 1, 
                            float spectral_sigma = 5)
{
	const auto width = image.cols;
	const auto height = image.rows;
	cv::Mat output(image.size(), image.type());

	cv::Mat gaussianKernel = createGaussianKernel(window_size, spatial_sigma); // sigma for the spatial filter (Gaussian, \(w_G\) kernel)

	for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			output.at<uchar>(r, c) = 0;
		}
	}

	auto d = [](float a, float b) {
		return std::abs(a - b);
	};

	 /* use of weighting function p : dissimilar pixels get lower weights, 
	 								preserves strong edges, smooths other regions */
	auto p = [](float val, float sigma) {
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

					float range_difference = d(image.at<uchar>(r, c), image.at<uchar>(r + i, c + j));

					float w
						= p(range_difference, spectral_sigma) // spectral filter
						* gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2); // spatial filter

					sum += image.at<uchar>(r + i, c + j) * w;
					sum_w += w;
				}
			}
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
cv::Mat applyJointBilateralFilter(const cv::Mat& input_rgb, 
                        const cv::Mat& input_depth, 
                        cv::Mat& output, 
                        const int window_size = 5, 
                        float sigma = 5)
{
	// converting the bilateral filter to Guided Joint bilateral filter for guided image upsampling 
	// upsampling a low resolution depth image, guided by an RGB image
	// weights formed using colors (image input_rgb), filtering happens by modifying depth (image input_depth)
	const auto width = input_rgb.cols;
	const auto height = input_rgb.rows;

	cv::Mat gaussianKernel = createGaussianKernel(window_size, 0.5); // sigma for the spatial filter (Gaussian, \(w_G\) kernel)
	auto d = [](float a, float b) {
		return std::abs(a - b);
	};

	auto p = [](float val, float sigma) {	// use of weighting function p : dissimilar pixels get lower weights, preserves strong edges, smooths other regions
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

					float range_difference
						= d(input_rgb.at<uchar>(r, c), input_rgb.at<uchar>(r + i, c + j)); // using the rgb image with the spectral filter

					float w = p(range_difference, sigma) // sigma for the spectral filter (\(f\) in the slides
						* gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);

					sum += input_depth.at<uchar>(r + i, c + j) * w; // using the depth image with the spatial filter
					sum_w += w;
				}
			}
			output.at<uchar>(r, c) = sum / sum_w;
		}
	}
	return output;
}


/**
 * Perform upsampling on an RGB image using the depth map
 *
 * @param[in]   input_rgb cv::Mat
 * @param[in]   input_depth cv::Mat
 * 
 * @returns     D output image  
 */
cv::Mat performUpsampling(const cv::Mat& input_rgb, 
                        const cv::Mat& input_depth)
{
	// applying the joint bilateral filter to upsample a depth image, guided by an RGB image -- iterative upsampling
	int uf = log2(input_rgb.rows / input_depth.rows); // upsample factor
	cv::Mat D = input_depth.clone(); // lowres depth image
	cv::Mat I = input_rgb.clone(); // highres rgb image
	for (int i = 0; i < uf; ++i)
	{
		cv::resize(D, D, D.size() * 2); // doubling the size of the depth image
		cv::resize(I, I, D.size());		// resizing the rgb image to depth image size
		applyJointBilateralFilter(I, D, D, 5, 0.1); // applying the joint bilateral filter with changed size depth and rbg images
	}
	cv::resize(D, D, input_rgb.size()); // in the end resizing the depth image to rgb image size
	applyJointBilateralFilter(input_rgb, D, D, 5, 0.1); // applying the joint bilateral filter with full res. size images
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