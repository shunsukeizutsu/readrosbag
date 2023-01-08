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
<<<<<<< HEAD
    rosbag::Bag bag;
    bag.open("/home/haselab15/rosbag/210601_0858/2021-06-01-08-58-07.bag", rosbag::bagmode::Read);
=======
    rosbag::Bag bag("/home/shunsukeizutsu/12_02_toyosu/2022-12-02-15-57-33.bag", rosbag::bagmode::Read);
//    bag.open("/home/shunsukeizutsu/12_02_toyosu/2022-12-02-15-57-33.bag", rosbag::bagmode::Read);
>>>>>>> d10f39d31127be53c67249e31bb5577a87771995

    std::string fix = "/fix";

    std::vector<std::string> topics;
    topics.push_back(std::string(fix));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    std::cout << "%time,field.header.seq,field.header.stamp,field.header.frame_id,field.status.status,field.status.service,field.latitude,field.longitude,field.altitude,";
    for(int i=0;i<9;i++)
    {
        std::cout << "field.position_covariance" << i << ",";
    }
    std::cout << "field.position_covariance_type" << std::endl;
    
    BOOST_FOREACH (rosbag::MessageInstance const m, view)
    {
        if (m.getTopic() == fix)
        {
            sensor_msgs::NavSatFix::ConstPtr msg = m.instantiate<sensor_msgs::NavSatFix>();
            std::cout << msg->header.stamp << ",";
            std::cout << msg->header.seq << ",";
            std::cout << msg->header.stamp << ",";
            std::cout << msg->header.frame_id << ",";
            std::cout << (int)msg->status.status << ",";
            std::cout << msg->status.service << ",";

            printf("%0.10f,", msg->latitude);
            //緯度
            printf("%0.10f,", msg->longitude);
            //経度
            printf("%0.10f,", msg->altitude);
            //高度

            for(int i=0;i<9;i++)
            {
                std::cout << msg->position_covariance[i] << ",";
            }
            std::cout << (uint)msg->position_covariance_type << std::endl; 
        }
    }

    bag.close();
    return 0;
}