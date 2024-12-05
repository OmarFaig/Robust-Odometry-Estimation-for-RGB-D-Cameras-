#include "pointCloud.h"

// Camera intrinsic parameters
const float fx = 525.0;  // Focal length in x
const float fy = 525.0;  // Focal length in y
const float cx = 319.5;  // Principal point x
const float cy = 239.5;  // Principal point y

std::vector<Point3D> depthToPointCloud(const cv::Mat& depth_img, const cv::Mat& rgb_img) {
    std::vector<Point3D> point_cloud;

    for (int v = 0; v < depth_img.rows; ++v) {
        for (int u = 0; u < depth_img.cols; ++u) {
            float z = depth_img.at<float>(v, u) / 5000.0f; // Convert from millimeters to meters
            if (z <= 0.0f || z > 6.0f) continue;  // Skip invalid depth or points too far away

            float x = (u - cx) * z / fx;
            float y = (v - cy) * z / fy;

            Point3D point;
            point.position = cv::Vec3f(x, y, z);
            point.color = rgb_img.at<cv::Vec3b>(v, u);
            point_cloud.push_back(point);
        }
    }

    return point_cloud;
}