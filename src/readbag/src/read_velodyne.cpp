#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include "std_msgs/String.h"
#include <boost/foreach.hpp>
#include "sensor_msgs/PointCloud2.h"

int main()
{
   rosbag::Bag bag;
    bag.open("/home/shunsuke/rosbag/2022-08-19-16-07-21.bag", rosbag::bagmode::Read);

    std::string velodyne = "/velodyne_points";

    std::vector<std::string>topics;
    topics.push_back(std::string(velodyne));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    BOOST_FOREACH(rosbag::MessageInstance const m,view)
    {
        if(m.getTopic() == velodyne)
        {
            sensor_msgs::PointCloud2::ConstPtr msg = m.instantiate<sensor_msgs::PointCloud2>();
            std::cout << msg->height << " ";
            std::cout << msg->width << " ";
          //  std::cout << msg->data << " ";
        }
    }

    bag.close();
    
    return 0;
}