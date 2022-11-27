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

    std::string fix = "/fix";

    std::vector<std::string>topics;
    topics.push_back(std::string(fix));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    std::cout << "field.header.seq,field.header.stamp,field.header.fream_if,field.status,field.status.service,field.latitude,field.longitude,field.altitude,";
    std::cout << "position_convariance[0],positioon_convariance[1],positioon_convariance[2],positioon_convariance[3],positioon_convariance[4],positioon_convariance[5],positioon_convariance[6],positioon_convariance[7],positioon_convariance[8],position_covariance_type" << std::endl;
    BOOST_FOREACH(rosbag::MessageInstance const m,view)
    {
        if(m.getTopic() == fix)
        {
            sensor_msgs::NavSatFix::ConstPtr msg = m.instantiate<sensor_msgs::NavSatFix>();
            std::cout << msg->header.seq << ",";
            std::cout << msg->header.stamp << ",";
            std::cout << msg->header.frame_id << ",";
            std::cout << (int)msg->status.status << ",";
            std::cout << msg->status.service << ",";
            
            printf("%lf,",msg->latitude);
            printf("%lf,",(float)msg->longitude);
            printf("%lf,",msg->altitude);
            
            //std::cout << msg->latitude << std::endl;
            /*std::cout << (float)msg->longitude << ",";
            std::cout << (float)msg->altitude << ",";*/
            std::cout << msg->position_covariance[0] << ",";
            std::cout << msg->position_covariance[1] << ",";
            std::cout << msg->position_covariance[2] << ",";
            std::cout << msg->position_covariance[3] << ",";
            std::cout << msg->position_covariance[4] << ",";
            std::cout << msg->position_covariance[5] << ",";
            std::cout << msg->position_covariance[6] << ",";
            std::cout << msg->position_covariance[7] << ",";
            std::cout << msg->position_covariance[8] << ",";
            std::cout << (uint)msg->position_covariance_type << std::endl;////////出力できていない
        }
    }

    bag.close();
    return 0;
}