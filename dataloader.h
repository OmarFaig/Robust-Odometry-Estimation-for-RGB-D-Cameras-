#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class DataLoader {
public:
    DataLoader(const std::string& rgb_path, const std::string& depth_path);
    
    // Get current images
    cv::Mat getCurrentRGB() const;
    cv::Mat getCurrentDepth() const;
    
    // Navigation methods
    bool next();     // returns false if at end
    bool previous(); // returns false if at beginning
    void reset();    // go back to first image
    
    // Status checks
    bool hasNext() const;
    bool hasPrevious() const;
    size_t getCurrentIndex() const;
    size_t getTotalImages() const;
    void setCurrentIndex(size_t index);

private:
    std::vector<std::string> rgb_files_;
    std::vector<std::string> depth_files_;
    size_t current_index_;
    std::string rgb_path_;
    std::string depth_path_;
    
    // Helper methods
    void loadImagePaths();
    bool isImageFile(const std::string& filename) const;
};