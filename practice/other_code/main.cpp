#include <iostream>
#include <opencv2/opencv.hpp>

void OurFiler(const cv::Mat& input, cv::Mat& output) {

	const auto width = input.cols;
	const auto height = input.rows;

	const int window_size = 7;

	// TEMPORARY CODE
	for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			output.at<uchar>(r, c) = 0;
		}
	}

	const double hw = window_size / 2;
	const double sigma = std::sqrt(2.0) * hw / 2.5; // ? maybe half_window_size / 2.5
	const double sigmaSq = sigma * sigma;

	// rmax = 2.5 * sigma
	// sigma = rmax / 2.5

	cv::Size mask_size(window_size, window_size);
	cv::Mat mask(mask_size, output.type());
	for (int r = 0; r < window_size; ++r) {
		for (int c = 0; c < window_size; ++c) {
			//mask.at<uchar>(r, c) = 1; // box filter

			// TODO: implement Gaussian filter
			double r2 = (r - hw) * (r - hw) + (c - hw) * (c - hw); // distance squared from center of the mask
			mask.at<uchar>(r, c) = 255 * std::exp(-r2 / (2*sigmaSq));
			std::cout << static_cast<int>(mask.at<uchar>(r, c)) << std::endl;
			// 0..1 -> 0..255
		}
		std::cout << std::endl;
	}


	std::cout << mask << std::endl;

	int sum_mask = 0; // in order to normalize filtering
	for (int r = 0; r < window_size; ++r) {
		for (int c = 0; c < window_size; ++c) {
			sum_mask += static_cast<int>(mask.at<uchar>(r, c));
		}
	}

	for (int r = window_size / 2; r < height - window_size / 2; ++r) {
		for (int c = window_size / 2; c < width - window_size / 2; ++c) {

			int sum = 0;
			for (int i = -window_size / 2; i <= window_size / 2; ++i) {
				for (int j = -window_size / 2; j <= window_size / 2; ++j) {
					int intensity = static_cast<int>(input.at<uchar>(
						r + i,
						c + j));
					int weight = static_cast<int>(mask.at<uchar>(
						i + window_size / 2,
						j + window_size / 2));

					sum += intensity * weight; // convolution happening...
				}
			}
			output.at<uchar>(r, c) = sum / sum_mask; // normalization
		}
	}
}

int main() {

	cv::Mat im = cv::imread("lena.png", 0);

	if (im.data == nullptr) {
		std::cerr << "Failed to load image" << std::endl;
	}

	//cv::imshow("im", im);
	//cv::waitKey();

	cv::Mat noise(im.size(), im.type());
	uchar mean = 0;
	uchar stddev = 25; // standard deviation
	cv::randn(noise, mean, stddev);

	//im.copyTo(...) // gt...

	im += noise; // "input"

	cv::imshow("im", im);
	//cv::waitKey();

	// gaussian
	cv::Mat output;
	cv::GaussianBlur(im, output, cv::Size(7, 7), 0, 0);
	cv::imshow("gaussian", output);
	//cv::waitKey();

	// median
	cv::medianBlur(im, output, 3);
	cv::imshow("median", output);
	//cv::waitKey();

	// bilateral
	double window_size = 11;
	cv::bilateralFilter(im, output, window_size, 2 * window_size, window_size / 2);
	cv::imshow("bilateral", output);

	OurFiler(im, output);
	cv::imshow("OurFiler", output);


	cv::waitKey();

	// HW (1 point for each metric, max 5 points):
	// - compare your images
	//		- SSD
	//		- RMSE (Root Mean Squared Error)
	//		- PSNR ..
	//	  - ....

	return 0;
}