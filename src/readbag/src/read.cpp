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
    bag.open("/home/haselab15/rosbag/2022-08-19-16-07-21.bag", rosbag::bagmode::Read);

    std::string fix = "/fix";
    std::string velodyne = "/velodyne_points";
    std::string imu = "imu/data_raw";

    std::vector<std::string>topics;
    topics.push_back(std::string(fix));
    topics.push_back(std::string(velodyne));
    topics.push_back(std::string(imu));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    BOOST_FOREACH(rosbag::MessageInstance const m,view)
    {
//        std::cout << m.getTopic() << std::endl;
        if(m.getTopic() == fix)
        {
            sensor_msgs::NavSatFix::ConstPtr msg = m.instantiate<sensor_msgs::NavSatFix>();
            sensor_msgs::NavSatStatus::ConstPtr msg2 = m.instantiate<sensor_msgs::NavSatStatus>();
            std::cout << msg->header.seq << " ";
            std::cout << msg->header.stamp << " ";
            std::cout << msg->header.frame_id << " ";
//            printf("%d\n",msg2->status);
//              std::cout << msg2->status << " ";
            std::cout << msg->status.service << " ";
            std::cout << msg->latitude << " ";
            std::cout << msg->longitude << " ";
            std::cout << msg->altitude << " ";
            std::cout << msg->position_covariance[0] << " ";
            std::cout << msg->position_covariance[1] << " ";
            std::cout << msg->position_covariance[2] << " ";
            std::cout << msg->position_covariance[3] << " ";
            std::cout << msg->position_covariance[4] << " ";
            std::cout << msg->position_covariance[5] << " ";
            std::cout << msg->position_covariance[6] << " ";
            std::cout << msg->position_covariance[7] << " ";
            std::cout << msg->position_covariance[8] << std::endl;
            //std::cout << msg->(uint8_t)position_covariance_type << std::endl;////////出力できていない

        }
/*        if(m.getTopic() == velodyne)
        {
            std::cout << "accord_vel" << std::endl;
        }*/
/*        if(m.getTopic() == imu)
        {

            sensor_msgs::Imu::ConstPtr msg = m.instantiate<sensor_msgs::Imu>();
            std::cout << msg->linear_acceleration.x;
            std::cout << msg->linear_acceleration.y;
            std::cout << msg->linear_acceleration.z << std::endl;
            std::cout << m.getTopic() << std::endl;
        }
*/
    }

    bag.close();
    return 0;
}