#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/display/widgets.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/gl/gl.h>
#include <pangolin/handler/handler.h>
#include <pangolin/var/var.h>
#include <pangolin/var/varextra.h>
#include <pangolin/display/default_font.h>


#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include "dataloader.h"

int main()
{
    std::cout << "Starting program..." << std::endl;

    try
    {
        // Create Pangolin window
        pangolin::CreateWindowAndBind("RGBD SLAM", 1024, 768);
        glEnable(GL_DEPTH_TEST);

        // Set white background
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Define camera parameters for 3D view
        pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 420, 420, 512, 384, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.5, -3, 0, 0, 0, pangolin::AxisY));

        // Create Interactive View in bottom half
        pangolin::Handler3D handler(s_cam);
        pangolin::View &d_cam = pangolin::CreateDisplay()
                                    .SetBounds(0.0f, 0.6f, 0.2f, 1.0f)
                                    .SetHandler(&handler);

        // Create views for images in top half
        pangolin::View &img_view1 = pangolin::CreateDisplay()
                                        .SetBounds(0.6f, 1.0f, 0.2f, 0.5f)
                                        .SetLock(pangolin::LockLeft, pangolin::LockTop);

        pangolin::View &img_view2 = pangolin::CreateDisplay()
                                        .SetBounds(0.6f, 1.0f, 0.5f, 0.8f)
                                        .SetLock(pangolin::LockRight, pangolin::LockTop);

        // Create a panel manually
        
        pangolin::View& panel = pangolin::CreatePanel("ui")
            .SetBounds(0.0f, 1.0f, 0.0f, 0.2f)
            .SetLayout(pangolin::LayoutVertical);

        // Set font size for UI text
        //pangolin::GlFont::I().TextSize(20);

        // Create buttons
        pangolin::Var<bool> btn_next("ui.Next Frame", false, true);
        pangolin::Var<bool> btn_prev("ui.Previous Frame", false, true);
        pangolin::Var<bool> btn_reset("ui.Reset", false, true);
        pangolin::Var<bool> running("ui.Auto Play", false, true);
        pangolin::Var<int> slider("ui.Frame Slider", 0, 0, 100);

        // Initialize data loader
        DataLoader loader("/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb", 
                        "/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/depth");

        while (!pangolin::ShouldQuit())
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Handle button presses
            if (btn_next)
            {
                loader.next();
                btn_next = false;
            }
            if (btn_prev)
            {
                loader.previous();
                btn_prev = false;
            }
            if (btn_reset)
            {
                loader.reset();
                btn_reset = false;
            }

            // Update slider value based on current index
            slider = loader.getCurrentIndex();

            // Update current index based on slider value
            if (slider != loader.getCurrentIndex()) {
                loader.setCurrentIndex(slider);
            }

            // Auto-advance if running
            if (running && loader.hasNext())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                loader.next();
            }

            // Get current images
            cv::Mat rgb_img = loader.getCurrentRGB();
            cv::Mat depth_img = loader.getCurrentDepth();

            if (!rgb_img.empty() && !depth_img.empty())
            {
                // Rotate images by 180 degrees
                cv::rotate(rgb_img, rgb_img, cv::ROTATE_180);
                cv::rotate(depth_img, depth_img, cv::ROTATE_180);

                // Convert images to RGB
                cv::cvtColor(rgb_img, rgb_img, cv::COLOR_BGR2RGB);

                // Create textures
                pangolin::GlTexture tex1(rgb_img.cols, rgb_img.rows, GL_RGB, false, 0, GL_RGB, GL_UNSIGNED_BYTE);
                pangolin::GlTexture tex2(depth_img.cols, depth_img.rows, GL_RGB, false, 0, GL_RGB, GL_UNSIGNED_BYTE);

                // Render first image
                img_view1.Activate();
                glColor3f(1.0f, 1.0f, 1.0f);
                tex1.Upload(rgb_img.data, GL_RGB, GL_UNSIGNED_BYTE);
                tex1.RenderToViewport();

                // Render second image
                img_view2.Activate();
                glColor3f(1.0f, 1.0f, 1.0f);
                tex2.Upload(depth_img.data, GL_RGB, GL_UNSIGNED_BYTE);
                tex2.RenderToViewport();

                // Render 3D view
                d_cam.Activate(s_cam);

                // Draw coordinate frame
                glLineWidth(3);
                pangolin::glDrawAxis(3.0f);

                // Draw grid in x-z plane with darker color for visibility on white background
                glLineWidth(1);
                glColor3f(0.3f, 0.3f, 0.3f); // Darker grey for better visibility
                pangolin::glDraw_z0(2.0f, 20);
            }

            pangolin::FinishFrame();
        }

        pangolin::DestroyWindow("RGBD SLAM");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught" << std::endl;
        return -1;
    }

    return 0;
}