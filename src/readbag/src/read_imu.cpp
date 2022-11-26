#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include "std_msgs/String.h"
#include <boost/foreach.hpp>
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/NavSatStatus.h"
#include <stdint.h>
#include <stdio.h>
#include <cstdint>

int main()
{
    rosbag::Bag bag;
    bag.open("/home/shunsuke/rosbag/2022-08-19-16-07-21.bag", rosbag::bagmode::Read);

    std::string imu = "/imu/data_raw";

    std::vector<std::string>topics;
    topics.push_back(std::string(imu));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    BOOST_FOREACH(rosbag::MessageInstance const m,view)
    {
        if(m.getTopic() == imu)
        {
            sensor_msgs::Imu::ConstPtr msg = m.instantiate<sensor_msgs::Imu>();
            std::cout << msg->header.seq << " ";
            std::cout << msg->header.stamp << " ";
            std::cout << msg->header.frame_id << " ";
            std::cout << msg-> orientation.x << " ";
            std::cout << msg-> orientation.y << " ";
            std::cout << msg-> orientation.z << " ";
            std::cout << msg-> orientation.w << " ";
            std::cout << msg-> orientation_covariance[0] << " ";
            std::cout << msg-> orientation_covariance[1] << " ";
            std::cout << msg-> orientation_covariance[2] << " ";
            std::cout << msg-> orientation_covariance[3] << " ";
            std::cout << msg-> orientation_covariance[4] << " ";
            std::cout << msg-> orientation_covariance[5] << " ";
            std::cout << msg-> orientation_covariance[6] << " ";
            std::cout << msg-> orientation_covariance[7] << " ";
            std::cout << msg-> orientation_covariance[8] << " ";
            std::cout << msg->angular_velocity.x << " ";
            std::cout << msg->angular_velocity.y << " ";
            std::cout << msg->angular_velocity.z << " ";
            std::cout << msg->angular_velocity_covariance[0] << " ";
            std::cout << msg->angular_velocity_covariance[1] << " ";
            std::cout << msg->angular_velocity_covariance[2] << " ";
            std::cout << msg->angular_velocity_covariance[3] << " ";
            std::cout << msg->angular_velocity_covariance[4] << " ";
            std::cout << msg->angular_velocity_covariance[5] << " ";
            std::cout << msg->angular_velocity_covariance[6] << " ";
            std::cout << msg->angular_velocity_covariance[7] << " ";
            std::cout << msg->angular_velocity_covariance[8] << " ";
            std::cout << msg->linear_acceleration.x << " ";
            std::cout << msg->linear_acceleration.y << " ";
            std::cout << msg->linear_acceleration.z << " ";
            std::cout << msg->linear_acceleration_covariance[0] << " ";
            std::cout << msg->linear_acceleration_covariance[1] << " ";
            std::cout << msg->linear_acceleration_covariance[2] << " ";
            std::cout << msg->linear_acceleration_covariance[3] << " ";
            std::cout << msg->linear_acceleration_covariance[4] << " ";
            std::cout << msg->linear_acceleration_covariance[5] << " ";
            std::cout << msg->linear_acceleration_covariance[6] << " ";
            std::cout << msg->linear_acceleration_covariance[7] << " ";
            std::cout << msg->linear_acceleration_covariance[8] << std::endl;
        }
    }

    bag.close();
    return 0;
}