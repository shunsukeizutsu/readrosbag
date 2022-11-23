#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include "std_msgs/String.h"
#include <boost/foreach.hpp>
#include "sensor_msgs/Imu.h"

int main()
{
    rosbag::Bag bag;
    bag.open("/home/shunsuke/rosbag/2022-08-19-16-07-21.bag", rosbag::bagmode::Read);

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
        /*if(m.getTopic() == fix)
        {
            std::cout << "accord" << std::endl;
        }
        if(m.getTopic() == velodyne)
        {
            std::cout << "accord_vel" << std::endl;
        }*/
        if(m.getTopic() == imu)
        {
 //           std::cout << "accord_imu" << std::endl;
 //           std_msgs::String::ConstPtr msg = m.instantiate<std_msgs::String>();
 //           std::cout << msg->data << std::endl;
            sensor_msgs::Imu::ConstPtr msg = m.instantiate<sensor_msgs::Imu>();
            std::cout << msg->linear_acceleration.x;
            std::cout << msg->linear_acceleration.y;
            std::cout << msg->linear_acceleration.z << std::endl;
        }
    }

    bag.close();
    return 0;
}