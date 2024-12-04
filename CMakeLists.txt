cmake_minimum_required(VERSION 3.22)
project(RGBD_odometry)
set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(Pangolin REQUIRED)
find_package(OpenCV REQUIRED)

# Print Pangolin version and components
message(STATUS "Found Pangolin version: ${Pangolin_VERSION}")
message(STATUS "Pangolin_LIBRARIES: ${Pangolin_LIBRARIES}")

include_directories(
    ${Pangolin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
)

# List your source files
set(SOURCES
    main.cpp
    dataloader.cpp
)

# List your header files
set(HEADERS
    dataloader.h
)

# Create the library
add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
    ${HEADERS}
)

# Link libraries to your project
target_link_libraries(${PROJECT_NAME}
    ${Pangolin_LIBRARIES}
    ${OpenCV_LIBS}
    pthread
    stdc++fs
)

# Create the executable
add_executable(run main.cpp)
target_link_libraries(run 
    ${PROJECT_NAME}
    ${Pangolin_LIBRARIES}
    ${OpenCV_LIBS}
)

# Print some debug information
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
message(STATUS "Pangolin_INCLUDE_DIRS: ${Pangolin_INCLUDE_DIRS}")

