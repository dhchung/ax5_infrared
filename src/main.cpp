#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>

#include "camera.h"

#include <chrono>

int main(int argc, char ** argv) {
    Camera cam;
    ros::init(argc, argv, "send_image");

    ros::NodeHandle nh;

    cv_bridge::CvImage img_bridge;

    sensor_msgs::Image img;
    std_msgs::Header header;

    ros::Publisher pub_img = nh.advertise<sensor_msgs::Image>("infrared_cam/image", 1);

    ros::Rate loop_rate(2000);
    int count = 0;
    while(ros::ok()){
    // while(1){

        cv::Mat acquired_image =  cam.acquire_image();

        header.seq = count;
        header.stamp = ros::Time::now();
        img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, acquired_image);
        img_bridge.toImageMsg(img);

        pub_img.publish(img);

        ROS_INFO("image sent!");
        ros::spinOnce();
        loop_rate.sleep();
        ++count;

    }
    return 0;
}