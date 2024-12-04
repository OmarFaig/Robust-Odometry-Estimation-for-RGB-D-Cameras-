#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/gl/gl.h>
#include <pangolin/handler/handler.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

int main()
{
    std::cout << "Starting program..." << std::endl;

    try {
        // Create Pangolin window
        pangolin::CreateWindowAndBind("RGBD SLAM", 1024, 768);
        glEnable(GL_DEPTH_TEST);

        // Set white background
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Define camera parameters for 3D view
        pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 420, 420, 512, 384, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.5, -3, 0, 0, 0, pangolin::AxisY)
        );

        // Create Interactive View in bottom half
        pangolin::Handler3D handler(s_cam);
        pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0f, 0.5f, 0.0f, 1.0f)
            .SetHandler(&handler);

        // Create views for images in top half
        pangolin::View& img_view1 = pangolin::CreateDisplay()
            .SetBounds(0.5f, 1.0f, 0.0f, 0.5f)
            .SetLock(pangolin::LockLeft, pangolin::LockTop);

        pangolin::View& img_view2 = pangolin::CreateDisplay()
            .SetBounds(0.5f, 1.0f, 0.5f, 1.0f)
            .SetLock(pangolin::LockRight, pangolin::LockTop);

        // Load images
        std::string img1_path = "/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb/1305031102.175304.png";    // Adjust paths as needed
        std::string img2_path = "/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/depth/1305031102.194330.png";  // Adjust paths as needed
        
        cv::Mat img1 = cv::imread(img1_path);
        cv::Mat img2 = cv::imread(img2_path);

        if (img1.empty() || img2.empty()) {
            std::cerr << "Failed to load images from:" << std::endl;
            std::cerr << "Image 1: " << std::filesystem::absolute(img1_path) << std::endl;
            std::cerr << "Image 2: " << std::filesystem::absolute(img2_path) << std::endl;
            return -1;
        }

        // Convert images to RGB
        cv::cvtColor(img1, img1, cv::COLOR_BGR2RGB);
        cv::cvtColor(img2, img2, cv::COLOR_BGR2RGB);

        // Create textures
        pangolin::GlTexture tex1(img1.cols, img1.rows, GL_RGB, false, 0, GL_RGB, GL_UNSIGNED_BYTE);
        pangolin::GlTexture tex2(img2.cols, img2.rows, GL_RGB, false, 0, GL_RGB, GL_UNSIGNED_BYTE);

        while (!pangolin::ShouldQuit()) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render first image
            img_view1.Activate();
            glColor3f(1.0f, 1.0f, 1.0f);
            tex1.Upload(img1.data, GL_RGB, GL_UNSIGNED_BYTE);
            tex1.RenderToViewport();

            // Render second image
            img_view2.Activate();
            glColor3f(1.0f, 1.0f, 1.0f);
            tex2.Upload(img2.data, GL_RGB, GL_UNSIGNED_BYTE);
            tex2.RenderToViewport();

            // Render 3D view
            d_cam.Activate(s_cam);
            
            // Draw coordinate frame
            glLineWidth(3);
            pangolin::glDrawAxis(3.0f);
            
            // Draw grid in x-z plane with darker color for visibility on white background
            glLineWidth(1);
            glColor3f(0.3f, 0.3f, 0.3f);  // Darker grey for better visibility
            pangolin::glDraw_z0(2.0f, 20);

            pangolin::FinishFrame();
        }

        pangolin::DestroyWindow("RGBD SLAM");

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
        return -1;
    }

    return 0;
}