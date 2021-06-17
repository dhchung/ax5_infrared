#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

class Camera{
public:
    Camera();
    ~Camera();

    Spinnaker::SystemPtr system;
    void print_spinnaker_version();
    bool camera_ready;

    cv::Mat acquire_image();
    void set_camera();


private:

    std::string cam_serial;
    Spinnaker::CameraPtr camptr;
    Spinnaker::CameraList camList;

};