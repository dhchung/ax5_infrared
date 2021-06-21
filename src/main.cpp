#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>

#include "camera.h"
#include "parameters_json.h"
#include <chrono>

Params params;

int main(int argc, char ** argv) {
    std::string param_dir = "/home/morin/dev/catkin_ws/src/ax5_infrared/include/parameters.json";
    params.read_data(param_dir);

    Camera cam(params.thermalParam.min_temp, params.thermalParam.max_temp);

    ros::init(argc, argv, "ifcamera_send_image");
    ros::NodeHandle nh;

    cv_bridge::CvImage img_bridge;

    sensor_msgs::Image img;
    std_msgs::Header header;

    ros::Publisher pub_img = nh.advertise<sensor_msgs::Image>("infrared_cam/image", 1);

    ros::Rate loop_rate(20);
    int count = 0;
    while(ros::ok()){

        cv::Mat acquired_image =  cam.acquire_image();
        header.seq = count;
        header.stamp = ros::Time::now();
        img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::MONO16, acquired_image);
        img_bridge.toImageMsg(img);

        pub_img.publish(img);

        // ROS_INFO("image sent!");
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    return 0;
}