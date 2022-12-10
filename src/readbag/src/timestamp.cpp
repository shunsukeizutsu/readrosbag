#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include "std_msgs/String.h"
#include <boost/foreach.hpp>
#include "sensor_msgs/PointCloud2.h"
//#include "velodyne_msgs/VelodyneScan.h"

int main()
{
  rosbag::Bag bag;
  bag.open("/home/haselab15/rosbag/toyosu_park/2022-12-02-15-57-33.bag", rosbag::bagmode::Read);

  std::string velodyne = "/velodyne_points";

  //////////////////一行目、列の名前//////////////////////////////////////
  std::cout << "field.header.stamp" << std::endl;

  
  std::vector<std::string> topics;
  topics.push_back(std::string(velodyne));

  rosbag::View view(bag, rosbag::TopicQuery(topics));

  BOOST_FOREACH (rosbag::MessageInstance const m, view)
  {
    if (m.getTopic() == velodyne)
    {
      sensor_msgs::PointCloud2::ConstPtr msg = m.instantiate<sensor_msgs::PointCloud2>();

     
      std::cout << msg->header.stamp << std::endl;
      
    
    }
  }

  bag.close();

  return 0;
}
