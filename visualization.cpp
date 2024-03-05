#include "visualization.h"
#include <limits>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <pangolin/var/var.h>
#include <pangolin/var/varextra.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/display/widgets.h>
#include <pangolin/display/default_font.h>
#include <pangolin/handler/handler.h>

int testSetup(){
    std::cout<<"HELO vis";
    return 1;
}


int visualizer(/*int argc, char* argv[]*/)
{  
  // Create OpenGL window in single line
  pangolin::CreateWindowAndBind("RGBD Odometry",1280,960);
  
  // 3D Mouse handler requires depth testing to be enabled
  glEnable(GL_DEPTH_TEST);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // Define Camera Render Object (for view / scene browsing)
  pangolin::OpenGlRenderState s_cam(
    pangolin::ProjectionMatrix(640,480,420,420,320,240,0.1,5000),
    pangolin::ModelViewLookAt(-0,0.5,-9, 0,0,0, pangolin::AxisY)
  );

  // Choose a sensible left UI Panel width based on the width of 20
  // charectors from the default font.
  const int UI_WIDTH = 20* pangolin::default_font().MaxWidth();

  // Add named OpenGL viewport to window and provide 3D Handler
  pangolin::View& d_cam = pangolin::CreateDisplay()
    .SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, 1280.0f/960.0f)
    .SetHandler(new pangolin::Handler3D(s_cam));

  pangolin::View& d_img1 = pangolin::Display("img1")
    .SetAspect(640.0f/480.0f);

  pangolin::View& d_img2 = pangolin::Display("img2")
    .SetAspect(640.0f/480.0f);
     pangolin::Display("multi")
      .SetBounds(0.0, 1.0, 0.0, 1.0)
      .SetLayout(pangolin::LayoutEqual)
      .AddDisplay(d_img1)
      .AddDisplay(d_img2)
      .AddDisplay(d_cam);


cv::Mat image = cv::imread("/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb/1305031127.779346.png");
      cv::flip(image, image, 0);

cv::Mat image2 = cv::imread("/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/depth/305031102.295279.png");
      cv::flip(image2, image2, 0);

const int width =  image.cols;
const int height = image.rows;
  ///home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb/1305031102.175304.png
pangolin::GlTexture imageTexture(width,height,GL_RGB,false,0,GL_RGB,GL_UNSIGNED_BYTE);
pangolin::GlTexture imageTexture2(width,height,GL_RGB,false,0,GL_RGB,GL_UNSIGNED_BYTE);

  // Add named Panel and bind to variables beginning 'ui'
  // A Panel is just a View with a default layout and input handling
  pangolin::CreatePanel("ui")
      .SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));

  // Safe and efficient binding of named variables.
  // Specialisations mean no conversions take place for exact types
  // and conversions between scalar types are cheap.
  pangolin::Var<bool> a_button("ui.A_Button",false,false);
  pangolin::Var<double> a_double("ui.A_Double",3,0,5);
  pangolin::Var<int> an_int("ui.An_Int",2,0,5);
  pangolin::Var<double> a_double_log("ui.Log_scale",3,1,1E4, true);
  pangolin::Var<bool> a_checkbox("ui.A_Checkbox",false,true);
  pangolin::Var<int> an_int_no_input("ui.An_Int_No_Input",2);
  pangolin::Var<std::string> a_string("ui.A_String", "Edit ME!");

  // std::function objects can be used for Var's too. These work great with C++11 closures.
  pangolin::Var<std::function<void(void)>> save_window("ui.Save_Window", [](){
      pangolin::SaveWindowOnRender("window");
  });

  pangolin::Var<std::function<void(void)>> save_cube_view("ui.Save_Cube", [&d_cam](){
      pangolin::SaveWindowOnRender("cube", d_cam.v);
  });

  // Demonstration of how we can register a keyboard hook to alter a Var
  pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL + 'b', [&](){
      a_double = 3.5;
  });

  // Default hooks for exiting (Esc) and fullscreen (tab).
  while( !pangolin::ShouldQuit() )
  { 
    // Clear entire screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//white background
    if( pangolin::Pushed(a_button) )
      std::cout << "You Pushed a button!" << std::endl;

    d_img1.Activate();
    glColor4f(1.0f,1.0f,1.0f,1.0f);
     imageTexture.Upload(image.data,GL_BGR,GL_UNSIGNED_BYTE); 

    imageTexture.RenderToViewport();

        d_img2.Activate();
    glColor4f(1.0f,1.0f,1.0f,1.0f);
         imageTexture2.Upload(image2.data,GL_BGR,GL_UNSIGNED_BYTE); 
          imageTexture2.RenderToViewport();

    // Overloading of Var<T> operators allows us to treat them like
    // their wrapped types, eg:
    if( a_checkbox )
      an_int = (int)a_double;

    an_int_no_input = an_int;

    if(d_cam.IsShown()) {
        // Activate efficiently by object
        d_cam.Activate(s_cam);

        // Render some stuff
        glColor3f(1.0,0.0,0.0);
        pangolin::glDrawColouredCube();
    }

    // Swap frames and Process Events
    pangolin::FinishFrame();
  }

  return 0;
}