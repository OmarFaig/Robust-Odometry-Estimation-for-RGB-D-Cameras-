cmake_minimum_required(VERSION 3.22)
project(RGBD_odometry)
set(CMAKE_CXX_STANDARD 14)



find_package(Pangolin REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
${Pangolin_INCLUDE_DIRS}
${OpenCV_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} SHARED
main.cpp
visualization.cpp
dataloader.cpp
visualization.h  
)



target_link_libraries(${PROJECT_NAME} ${Pangolin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(run main.cpp)

target_link_libraries(run ${PROJECT_NAME})

