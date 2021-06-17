#include "camera.h"


Camera::Camera(){
    system = Spinnaker::System::GetInstance();

    cam_serial = "73400300";

    camera_ready = false;
    camptr = nullptr;
    set_camera();
}
Camera::~Camera(){

    if(camera_ready){
        camptr->EndAcquisition();
        camptr->DeInit();
    }
    camList.Clear();
}

void Camera::print_spinnaker_version(){

    const Spinnaker::LibraryVersion spinnakerLibraryVersion = system->GetLibraryVersion();
    std::cout << "Spinnaker library version: " << spinnakerLibraryVersion.major << "." << spinnakerLibraryVersion.minor
         << "." << spinnakerLibraryVersion.type << "." << spinnakerLibraryVersion.build << std::endl
         << std::endl;
}


void Camera::set_camera(){
    camList = system->GetCameras();
    const unsigned int numCameras = camList.GetSize();
    std::cout<<"Number of cameras detected: "<<numCameras<<std::endl;

    camera_ready = true;
    try{
        camptr = camList.GetBySerial(cam_serial);
        
    }
    catch (Spinnaker::Exception& e){
        std::cout << "Error: " << e.what() << std::endl;
        camera_ready = false;
    }

    if(camera_ready){
        camptr->DeInit();
        camptr->Init();
        camptr->AcquisitionMode.SetValue(Spinnaker::AcquisitionMode_Continuous);
        camptr->BeginAcquisition();
    } else {
        std::cout<<"Camera Fucked"<<std::endl;
    }
}


cv::Mat Camera::acquire_image(){

    Spinnaker::ImagePtr img = camptr->GetNextImage();
    if(img->IsIncomplete()) {
        std::cout<<"Image Incomplete: "<<Spinnaker::Image::GetImageStatusDescription(img->GetImageStatus())<<std::endl;
    }
    const size_t width = img->GetWidth();
    const size_t height = img->GetHeight();


    cv::Mat image;
    return image;
}