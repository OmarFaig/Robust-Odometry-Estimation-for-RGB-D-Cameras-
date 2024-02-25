#include "visualization.h"
#include <limits>
#include <iostream>


#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/pangolin.h>

int sayHello(){
    std::cout<<"HELO vis";
    return 1;
}

int TT(){
    pangolin::CreateWindowAndBind("DefSLAM: Map Viewer", 175 + 640, 480);

    // 3D Mouse handler requires depth testing to be enabled
    glEnable(GL_DEPTH_TEST);

    // Issue specific OpenGl we might need
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::CreatePanel("menu").SetBounds(0.0, 1.0, 0.0,
                                            pangolin::Attach::Pix(175));
    pangolin::Var<bool> menuFollowCamera("menu.Follow Camera", true, true);
    pangolin::Var<bool> menuShowPoints("menu.Show Points", true, true);
    pangolin::Var<bool> menuShowKeyFrames("menu.Show KeyFrames", true, true);
    pangolin::Var<bool> menuShowGraph("menu.Show Graph", true, true);
    pangolin::Var<bool> menuShowError("menu.Show Error", true, true);
    pangolin::Var<bool> menuAutoPlay("menu.Autoplay", true, true);

    // Add named OpenGL viewport to window and provide 3D Handler
    // Output 3D
   // pangolin::View &d_cam1 =
   //     pangolin::CreateDisplay()
   //         .SetAspect(640.0f / 480.0f)
   //         .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1, -1024.0f / 768.0f)
   //         .SetHandler(new pangolin::Handler3D(s_cam));
//
    pangolin::OpenGlMatrix Twc;
    Twc.SetIdentity();
    return 0;
    }