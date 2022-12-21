# 3D Sensing HW2

## 1st part -> Implementation of algorithms

1. Bilateral filter
2. Guided filter - JB
3. Upsampling algorithm
    1. JBU
    2. Iterative upsampling algorithm

## 2nd part -> Implementation of a tool

1. Tool that converts the upsampled depth or disparity to 3D object.
    1. Point cloud
    2. GUI or real-time console
        1. For tuning params of the upsampling filters (spatial & spectral sigmas)

## 3rd part -> Evaluation

1. Demonstrate through visual examples that the filters work
2. Take 12 pairs of RGB-D or Color-Disparity Images
    1. Middlebury, KITTI, stereo evaluation dataset, etc
3. Compare
    1. Processing time
    2. Quality (compared to GT)
        1. Using various algos (JBU or JBMU) and iterative sampling
        2. 3 Metrics
            1. SSD / MSE, RMSE or SAD / MAD
            2. SSIM
            3. one of my choice
    3. Plots, figures, diagrams
        1. Difference btw GT and Output
        2. Tables and diagrams of Processing time and Quality
4. Documentation of the evaluation
