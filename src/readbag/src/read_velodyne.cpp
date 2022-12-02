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

  std::cout << "%time,field.header.seq,field.header.stamp,field.header.fream_id,field.height,field.width,";
  for(int i=0;i<6;i++)
  {
    std::cout << "field.field" << i << ".name,";
    std::cout << "field.field" << i << ".offset,";
    std::cout << "field.field" << i << ".datatype,";
    std::cout << "field.field" << i << ".count,";
  }
  std::cout << "field.is_bigendian,";
  std::cout << "field.point_step,";
  std::cout << "field.row_step,";
  for(int i=0;i<1206;i++)
  { 
    std::cout << "field.data" << i << ",";
    if(i==1205)
    {
      std::cout << std::endl;
    }
  }



  std::vector<std::string> topics;
  topics.push_back(std::string(velodyne));

  rosbag::View view(bag, rosbag::TopicQuery(topics));

  BOOST_FOREACH (rosbag::MessageInstance const m, view)
  {
    if (m.getTopic() == velodyne)
    {
      sensor_msgs::PointCloud2::ConstPtr msg = m.instantiate<sensor_msgs::PointCloud2>();
      std::cout << msg->header.stamp << ",";
      std::cout << msg->header.seq << ",";
      std::cout << msg->header.stamp << ",";
      std::cout << msg->header.frame_id << ",";
      std::cout << msg->height << ",";
      std::cout << msg->width << ",";
      for (size_t i = 0; i < msg->fields.size(); i++)
      {
        if (msg->fields[i].datatype == sensor_msgs::PointField::FLOAT32)
        {
          std::cout << msg->fields[i].name << ",";
          std::cout << msg->fields[i].offset << ",";
          std::cout << (uint)msg->fields[i].datatype << ",";
          std::cout << msg->fields[i].count << ",";
        }
        else if (msg->fields[i].datatype == sensor_msgs::PointField::UINT16)
        {
          std::cout << msg->fields[i].name << ",";
          std::cout << msg->fields[i].offset << ",";
          std::cout << (uint)msg->fields[i].datatype << ",";
          std::cout << msg->fields[i].count << ",";
        }
      }
      std::cout << (bool)msg->is_bigendian << ",";
      std::cout << msg->point_step << ",";
      std::cout << msg->row_step << ",";
      // data[1206]
      for (int i = 0; i < 1206; i++)
      {
        if (i != 1205)
        {
          std::cout << (uint)msg->data[i] << ",";
        }
        else
        {
          std::cout << (uint)msg->data[i] << std::endl;
        }
/*
      std::cout << msg->header.seq << " ";
      std::cout << msg->header.stamp << " ";
      std::cout << msg->header.frame_id << " ";
      std::cout << msg->height << " ";
      std::cout << msg->width << " ";

      for (size_t i = 0; i < msg->fields.size(); i++)
      {
        if (msg->fields[i].datatype == sensor_msgs::PointField::FLOAT32)
        {
          std::cout << msg->fields[i].name << " ";
          std::cout << msg->fields[i].offset << " ";
          std::cout << (uint)msg->fields[i].datatype << " ";
          std::cout << msg->fields[i].count << " ";
        }
        else if (msg->fields[i].datatype == sensor_msgs::PointField::UINT16)
        {
          std::cout << msg->fields[i].name << " ";
          std::cout << msg->fields[i].offset << " ";
          std::cout << (uint)msg->fields[i].datatype << " ";
          std::cout << msg->fields[i].count << " ";
        }
      }
      std::cout << (bool)msg->is_bigendian << " ";
      std::cout << msg->point_step << " ";
      std::cout << msg->row_step << " ";
      // data[1206]
      for (int i = 0; i < 1206; i++)
      {
        if (i != 1205)
        {
          std::cout << (uint)msg->data[i] << " ";
        }
        else
        {
          std::cout << (uint)msg->data[i] << std::endl;
        }
*/
      }
    }
  }

  bag.close();

  return 0;
}