#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat CreateGaussianKernel(int window_size) {
  cv::Mat kernel(cv::Size(window_size, window_size), CV_32FC1);

  int half_window_size = window_size / 2;

  // see: lecture_03_slides.pdf, Slide 13
  const double k = 2.5;
  const double r_max = std::sqrt(2.0 * half_window_size * half_window_size);
  const double sigma = r_max / k;

  // sum is for normalization 
  float sum = 0.0;

  for (int x = -window_size / 2; x <= window_size / 2; x++) {
    for (int y = -window_size / 2; y <= window_size / 2; y++) {
      float val = exp(-(x * x + y * y) / (2 * sigma * sigma));
      kernel.at<float>(x + window_size / 2, y + window_size / 2) = val;
      sum += val;
    }
  }

  // normalising the Kernel 
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      kernel.at<float>(i, j) /= sum;

  // note that this is a naive implementation
  // there are alternative (better) ways
  // e.g. 
  // - perform analytic normalisation (what's the integral of the gaussian? :))
  // - you could store and compute values as uchar directly in stead of float
  // - computing it as a separable kernel [ exp(x + y) = exp(x) * exp(y) ] ...
  // - ...

  return kernel;
}

void OurFiler_Box(const cv::Mat& input, cv::Mat& output, const int window_size = 5) {

  const auto width = input.cols;
  const auto height = input.rows;

  // TEMPORARY CODE
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      output.at<uchar>(r, c) = 0;
    }
  }

  for (int r = window_size / 2; r < height - window_size / 2; ++r) {
    for (int c = window_size / 2; c < width - window_size / 2; ++c) {

      // box filter
      int sum = 0;
      for (int i = -window_size / 2; i <= window_size / 2; ++i) {
        for (int j = -window_size / 2; j <= window_size / 2; ++j) {
          sum += input.at<uchar>(r + i, c + j);
        }
      }
      output.at<uchar>(r, c) = sum / (window_size * window_size);

    }
  }
}

void OurFiler_Gaussian(const cv::Mat& input, cv::Mat& output, const int window_size = 5) {

  const auto width = input.cols;
  const auto height = input.rows;

  cv::Mat gaussianKernel = CreateGaussianKernel(window_size);

  // TEMPORARY CODE
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
          sum
            += input.at<uchar>(r + i, c + j)
            * gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);
        }
      }
      output.at<uchar>(r, c) = sum;

    }
  }
}

void OurFilter_Bilateral(const cv::Mat& input, cv::Mat& output, const int window_size = 5) {
  const auto width = input.cols;
  const auto height = input.rows;

  cv::Mat gaussianKernel = CreateGaussianKernel(window_size);

  // TEMPORARY CODE
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      output.at<uchar>(r, c) = 0;
    }
  }

  auto p = [](float val) {
    const float sigma = 20;
    const float normalization = TODO;
    return (1/normalization) * std::exp(-val / sigma);
  };

  for (int r = window_size / 2; r < height - window_size / 2; ++r) {
    for (int c = window_size / 2; c < width - window_size / 2; ++c) {

      int sum = 0;
      for (int i = -window_size / 2; i <= window_size / 2; ++i) {
        for (int j = -window_size / 2; j <= window_size / 2; ++j) {
          sum
            += input.at<uchar>(r + i, c + j)
            * p(std::abs(input.at<uchar>(r, c) - input.at<uchar>(r + i, c + j)))
            * gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);
        }
      }
      output.at<uchar>(r, c) = sum;

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
  uchar stddev = 25;
  cv::randn(noise, mean, stddev);


  im += noise;

  cv::imshow("im", im);
  //cv::waitKey();

  // gaussian
  cv::Mat output;
  cv::GaussianBlur(im, output, cv::Size(5, 5), 0, 0);
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

  OurFiler_Box(im, output);
  cv::imshow("OurFiler_Box", output);

  OurFiler_Gaussian(im, output);
  cv::imshow("OurFiler_Gaussian", output);

  OurFilter_Bilateral(im, output);
  cv::imshow("OurFilter_Bilateral", output);

  cv::waitKey();

  // HW (1 point for each metric, max 5 points):
  // - compare your images
  //		- SSD
  //		- RMSE (Root Mean Squared Error)
  //		- PSNR ..
  //	  - ....

  return 0;
}