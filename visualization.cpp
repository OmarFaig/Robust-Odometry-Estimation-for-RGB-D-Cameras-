#include "visualization.h"

#include <limits>
#include <iostream>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <thread>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <pangolin/display/image_view.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/image/image.h>
#include <pangolin/image/image_io.h>
#include <pangolin/image/typed_image.h>
#include <pangolin/pangolin.h>

int testSetup(){
  //  std::cout<<"HELO vis";
    return 1;
}

constexpr int UI_WIDTH = 200;

int visualizer(/*int argc, char* argv[]*/)
{ 
  bool show_gui = false;

  pangolin::Var<bool> continue_next("ui.continue_next", false, false, true);
  using Button = pangolin::Var<std::function<void(void)>>;
  //Button next_step_btn("ui.next_step", &next_step);
  //Button save_trajectory_btn("ui.save_trajectory", &save_trajectory);
  
  if(show_gui){
  pangolin::CreateWindowAndBind("Main", 1800, 1000);
    glEnable(GL_DEPTH_TEST);

    // main parent display for images and 3d viewer
    pangolin::View& main_view =
        pangolin::Display("main")
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0)
            .SetLayout(pangolin::LayoutEqualVertical);
     // parent display for images
    pangolin::View& img_view_display =
        pangolin::Display("images").SetLayout(pangolin::LayoutEqual);
    main_view.AddDisplay(img_view_display);
  // main ui panel
    pangolin::CreatePanel("ui").SetBounds(0.0, 1.0, 0.0,pangolin::Attach::Pix(UI_WIDTH));
         std::vector<std::shared_ptr<pangolin::ImageView>> img_view;
   while (img_view.size() < 2) {
     std::shared_ptr<pangolin::ImageView> iv(new pangolin::ImageView);

     size_t idx = img_view.size();
     img_view.push_back(iv);

     img_view_display.AddDisplay(*iv);
     //iv->extern_draw_function =
     //    std::bind(&draw_image_overlay, std::placeholders::_1, idx);
   }
   
  
  

    // 3D visualization (initial camera view optimized to see full map)
    pangolin::OpenGlRenderState camera(
        pangolin::ProjectionMatrix(640, 480, 400, 400, 320, 240, 0.001, 10000),
        pangolin::ModelViewLookAt(-3.4, -3.7, -8.3, 2.1, 0.6, 0.2,
                                  pangolin::AxisNegY));
      pangolin::View& display3D =
        pangolin::Display("scene")
            .SetAspect(640 / 480.0)
            .SetHandler(new pangolin::Handler3D(camera));
    main_view.AddDisplay(display3D);

      
 while( !pangolin::ShouldQuit() )
 { 
   // Clear entire screen
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  if (ui_show_hidden.GuiChanged()) {
    //    hidden_panel.Show(ui_show_hidden);
    //    const int panel_width = ui_show_hidden ? 2 * UI_WIDTH : UI_WIDTH;
    //    main_view.SetBounds(0.0, 1.0, pangolin::Attach::Pix(panel_width), 1.0);
    //  }
     pangolin::Var<bool> a_button("ui.A_Button",false,false);

   if( pangolin::Pushed(a_button) )
     std::cout << "You Pushed a button!" << std::endl;

      display3D.Activate(camera);
      glClearColor(0.95f, 0.95f, 0.95f, 1.0f);  // light gray background

      img_view_display.Activate();

           pangolin::FinishFrame();

        }

  }




 
  // main parent display for images and 3d viewer
// pangolin::View& main_view =
//     pangolin::Display("main")
//         .SetBounds(0.0, 1.0, pangolin::Attach::Pix(200), 1.0)
//         .SetLayout(pangolin::LayoutEqualVertical);
//
// // parent display for images
// pangolin::View& img_view_display =
//     pangolin::Display("images").SetLayout(pangolin::LayoutEqual);
// main_view.AddDisplay(img_view_display);
//
// // main ui panel
// pangolin::CreatePanel("ui").SetBounds(0.0, 1.0, 0.0,
//                                       pangolin::Attach::Pix(200));
//
  // Choose a sensible left UI Panel width based on the width of 20
  // charectors from the default font.
// const int UI_WIDTH = 20* pangolin::default_font().MaxWidth();
//
// // Add named OpenGL viewport to window and provide 3D Handler
// pangolin::View& d_cam = pangolin::CreateDisplay()
//   .SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, 1000.0f/1000.0f)
//   .SetHandler(new pangolin::Handler3D(s_cam));
//
// pangolin::View& d_img1 = pangolin::Display("img1")
//   .SetAspect(640.0f/480.0f);
//
// pangolin::View& d_img2 = pangolin::Display("img2")
//   .SetAspect(640.0f/480.0f);
// 
// pangolin::Display("multi")
//     .SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0)
//     .SetLayout(pangolin::LayoutEqualVertical)
//     .AddDisplay(d_img1)
//     .AddDisplay(d_img2)
//     .AddDisplay(d_cam);
//
//
//v::Mat image = cv::imread("/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb/1305031127.779346.png");
//     cv::flip(image, image, 0);
//
//v::Mat image2 = cv::imread("/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/depth/305031102.295279.png");
//     cv::flip(image2, image2, 0);
//
//onst int width =  image.cols;
//onst int height = image.rows;
// ///home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb/1305031102.175304.png
//angolin::GlTexture imageTexture(width,height,GL_RGB,false,0,GL_RGB,GL_UNSIGNED_BYTE);
//angolin::GlTexture imageTexture2(width,height,GL_RGB,false,0,GL_RGB,GL_UNSIGNED_BYTE);
//
// // Add named Panel and bind to variables beginning 'ui'
// // A Panel is just a View with a default layout and input handling
// pangolin::CreatePanel("ui")
//     .SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));
//
// // Safe and efficient binding of named variables.
// // Specialisations mean no conversions take place for exact types
// // and conversions between scalar types are cheap.
// pangolin::Var<bool> a_button("ui.A_Button",false,false);
// pangolin::Var<double> a_double("ui.A_Double",3,0,5);
// pangolin::Var<int> an_int("ui.An_Int",2,0,5);
// pangolin::Var<double> a_double_log("ui.Log_scale",3,1,1E4, true);
// pangolin::Var<bool> a_checkbox("ui.A_Checkbox",false,true);
// pangolin::Var<int> an_int_no_input("ui.An_Int_No_Input",2);
// pangolin::Var<std::string> a_string("ui.A_String", "Edit ME!");
//
// // std::function objects can be used for Var's too. These work great with C++11 closures.
// pangolin::Var<std::function<void(void)>> save_window("ui.Save_Window", [](){
 //     pangolin::SaveWindowOnRender("window");
// });
//
// pangolin::Var<std::function<void(void)>> save_cube_view("ui.Save_Cube", [&d_cam](){
  //    pangolin::SaveWindowOnRender("cube", d_cam.v);
// });
//
// // Demonstration of how we can register a keyboard hook to alter a Var
// pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL + 'b', [&](){
   //   a_double = 3.5;
// });
//
// // Default hooks for exiting (Esc) and fullscreen (tab).
// while( !pangolin::ShouldQuit() )
// { 
//   // Clear entire screen
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
///glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//white background
//   glLineWidth(1.0);
//   glClearColor(0.95f, 0.95f, 0.95f, 1.0f);  // light gray background
//
//   if( pangolin::Pushed(a_button) )
//     std::cout << "You Pushed a button!" << std::endl;
//
//   d_img1.Activate();
//   glClearColor(0.95f, 0.95f, 0.95f, 1.0f);  // light gray background
//    imageTexture.Upload(image.data,GL_BGR,GL_UNSIGNED_BYTE); 
//
//   imageTexture.RenderToViewport();
//
//       d_img2.Activate();
//   glClearColor(0.95f, 0.95f, 0.95f, 1.0f);  // light gray background
//        imageTexture2.Upload(image2.data,GL_BGR,GL_UNSIGNED_BYTE); 
//         imageTexture2.RenderToViewport();
//
//   // Overloading of Var<T> operators allows us to treat them like
//   // their wrapped types, eg:
//   if( a_checkbox )
//     an_int = (int)a_double;
//
//   an_int_no_input = an_int;
//
//   if(d_cam.IsShown()) {
//       // Activate efficiently by object
//       d_cam.Activate(s_cam);
//
//       // Render some stuff
//       glColor3f(1.0,0.0,0.0);
//       pangolin::glDrawColouredCube();
//   }
//
//   // Swap frames and Process Events
//   pangolin::FinishFrame();
// }

  return 0;
}