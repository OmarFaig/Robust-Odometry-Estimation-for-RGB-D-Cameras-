// pointCloud.h
#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <opencv2/opencv.hpp>
#include <vector>

// Define the point cloud structure
struct Point3D {
    cv::Vec3f position;
    cv::Vec3b color;
};

// Function declaration
std::vector<Point3D> depthToPointCloud(const cv::Mat& depth_img, const cv::Mat& rgb_img);

#endif // POINTCLOUD_H