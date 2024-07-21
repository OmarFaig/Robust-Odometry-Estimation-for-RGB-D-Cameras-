#include<iostream>
#include<list>
#include<filesystem>
#include <fstream>
#include <sstream>

#include"dataloader.h"

int load_data(std::string& path_to_dataset ){
    std::cout<<" ************** Data loading started **************"<<std::endl;
  ///home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb.txt
  const std::string txt_path = path_to_dataset + "rgb_timestampts.txt";
std::cout<<txt_path<<std::endl;
 {
    std::ifstream file_names (txt_path);
    

int64_t timestamp;
int id =0;
while(file_names || id!=0){
    std::string line;
    std::getline(file_names,line);


    file_names>>timestamp;
    std::stringstream ss;
    ss << path_to_dataset << "rgb" <<"/" << timestamp << ".png";
        //tt= path_to_dataset+ "/rgb" +"/"+timestamp ;
    std::cout<<" hh "<<line<<std::endl;

    std::cout<<ss.str()<<std::endl;
    id++;
}

 }
    return 1;
}