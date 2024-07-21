#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>

#include<iostream>
#include<list>

#include<filesystem>
#include <opencv2/opencv.hpp>
#include "visualization.h"
#include "dataloader.h"
int main()
{
    //std::cout << "cpp version -- "<<__cplusplus;

   //std::cout<<"HELLO MAIN";
testSetup();
visualizer();
std::string path="/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/";
//load_data(path);
//using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

//for (const auto& dirEntry : recursive_directory_iterator("/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb/1305031102.175304.png"))
 //    std::cout << dirEntry << std::endl;
std::list<cv::Mat> imgs={};
    return 0;
}