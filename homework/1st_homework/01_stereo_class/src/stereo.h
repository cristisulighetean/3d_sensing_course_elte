#ifndef STEREO
#define STEREO

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>


struct stereo_params
    {
        // Camera setup parameters
        double focal_length;
        double baseline;

        // Stereo estimation parameters
        // Dmin: disparity added due to image cropping
        int dmin;
        int window_size;
        // TODO: Why do we use lambda as float?
        // Have default params for lambda
        float lambda = 100.0;
    };

class StereoCompute
{
private:
    cv::Mat image1;
    cv::Mat image2;
    int width, height;
    stereo_params params;

public:
    std::string output_name;

    StereoCompute(cv::Mat in_image1, cv::Mat in_image2, stereo_params in_params);

    // Put the public methods
    void getData(cv::Mat in_image1, cv::Mat in_image2, stereo_params in_params);

    cv::Mat getStereoNaive(void);

    cv::Mat getStereoDynamic(void);

    void computeStereoNaive(void);

    void computeStereoDynamic(void);

    void computePointCloud(void);

    std::stringstream getPointCloud(cv::Mat disparity_matrix, std::string file_name);

    void saveImage(cv::Mat image, std::string file_name);

    void viewImage(cv::Mat image);



    
};



#endif