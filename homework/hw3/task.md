# 3D Sensing HW3

## 1st part -> Implementation of algorithms

1. Perform Nearest-neighbor search using kd-trees
    1. may use nanoflann or any other lib for the task
2. Choose an appropriate representation of rotation, method to estimate rotation:
    - SVD
    - Quaternion, etc
3. Implement ICP
4. Implement Tr-ICP

## 2nd part -> Evaluation

1. Input
    - Use inputs with various overlaps and/or synthetically generated point clouds
        - At least 3 different overlaps / pairs of point clouds
    - Test various misalignments: apply initial rotation and translation differences
        - At least 4 different misalignments 0 5 10 20...
    - Test various noise levels (add gaussian noise to 3D point locations, synthetically)
        - At least 3 noise levels, from 0

2. Measure / evaluate:
    - Alignment precision (angular: rotation error, euclidian: translation error)
    - Runtime, no. of iterations
    - Compare ICP to tr-ICP and to the GT
3. Plot the results (diagrams) 