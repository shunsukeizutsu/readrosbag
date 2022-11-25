#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include "std_msgs/String.h"
#include <boost/foreach.hpp>
#include "sensor_msgs/PointCloud2.h"
#include "velodyne_msgs/VelodyneScan.h"


int main()
{
   rosbag::Bag bag;
    bag.open("/home/haselab15/rosbag/2022-08-19-16-07-21.bag", rosbag::bagmode::Read);

    std::string velodyne = "/velodyne_points";

    std::vector<std::string>topics;
    topics.push_back(std::string(velodyne));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    BOOST_FOREACH(rosbag::MessageInstance const m,view)
    {
        if(m.getTopic() == velodyne)
        {
            sensor_msgs::PointCloud2::ConstPtr msg = m.instantiate<sensor_msgs::PointCloud2>();
            //std::cout << msg->fields[0].name << " ";
            //std::cout << msg->width << " ";
            for (size_t i = 0; i < msg->fields.size(); i++)
            {
              if (msg->fields[i].datatype == sensor_msgs::PointField::FLOAT32)
              {
                std::cout << msg->fields[i].name << msg->fields[i].offset << msg->fields[i].datatype << " ";
                
          
              }
              else if (msg->fields[i].datatype == sensor_msgs::PointField::UINT16)
              {
                std::cout << msg->fields[i].datatype << msg->fields[i].name << std::endl;
              }   
            }
            //velodyne_msgs::VelodynePacket tmp = m.instantiate<velodyne_msgs::VelodynePacket>();
            //velodyne_msgs::VelodyneScan scan;
          //std::cout << scan.packets << std::endl;
        
        /*std::cout << *((u_int16_t*)(&msg.data[0])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[1])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[2])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[3])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[4])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[5])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[6])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[7])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[8])) << " ";
          std::cout << *((u_int16_t*)(&tmp.data[9])) << std::endl;
        */


        }
    }

    bag.close();
    
    return 0;
}