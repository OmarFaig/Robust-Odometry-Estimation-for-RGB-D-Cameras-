#include "dataloader.h"
#include <filesystem>
#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

DataLoader::DataLoader(const std::string& rgb_path, const std::string& depth_path)
    : rgb_path_(rgb_path)
    , depth_path_(depth_path)
    , current_index_(0)
{
    loadImagePaths();
    std::cout << "Found " << rgb_files_.size() << " RGB images and "
              << depth_files_.size() << " depth images" << std::endl;
}

void DataLoader::loadImagePaths() {
    // Clear existing paths
    rgb_files_.clear();
    depth_files_.clear();
    
    // Load RGB files
    for (const auto& entry : fs::directory_iterator(rgb_path_)) {
        if (isImageFile(entry.path().string())) {
            rgb_files_.push_back(entry.path().string());
        }
    }
    
    // Load depth files
    for (const auto& entry : fs::directory_iterator(depth_path_)) {
        if (isImageFile(entry.path().string())) {
            depth_files_.push_back(entry.path().string());
        }
    }
    
    // Sort the file paths to ensure proper ordering
    std::sort(rgb_files_.begin(), rgb_files_.end());
    std::sort(depth_files_.begin(), depth_files_.end());
}

bool DataLoader::isImageFile(const std::string& filename) const {
    std::string ext = fs::path(filename).extension().string();
    return ext == ".png" || ext == ".jpg" || ext == ".jpeg";
}

cv::Mat DataLoader::getCurrentRGB() const {
    if (rgb_files_.empty() || current_index_ >= rgb_files_.size()) {
        return cv::Mat();
    }
    return cv::imread(rgb_files_[current_index_]);
}

cv::Mat DataLoader::getCurrentDepth() const {
    if (depth_files_.empty() || current_index_ >= depth_files_.size()) {
        return cv::Mat();
    }
    return cv::imread(depth_files_[current_index_]);
}

bool DataLoader::next() {
    if (!hasNext()) return false;
    current_index_++;
    return true;
}

bool DataLoader::previous() {
    if (!hasPrevious()) return false;
    current_index_--;
    return true;
}

void DataLoader::reset() {
    current_index_ = 0;
}

bool DataLoader::hasNext() const {
    return current_index_ < rgb_files_.size() - 1;
}

bool DataLoader::hasPrevious() const {
    return current_index_ > 0;
}

size_t DataLoader::getCurrentIndex() const {
    return current_index_;
}

size_t DataLoader::getTotalImages() const {
    return rgb_files_.size();
}

void DataLoader::setCurrentIndex(size_t index) {
    if (index < rgb_files_.size()) {
        current_index_ = index;
    }
}