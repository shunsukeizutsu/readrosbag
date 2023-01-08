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
  bag.open("/home/haselab15/rosbag/210601_0858/2021-06-01-08-58-07.bag", rosbag::bagmode::Read);

  std::string velodyne = "/velodyne_points";

  //////////////////一行目、列の名前//////////////////////////////////////
  std::cout << "%time,field.header.seq,field.header.stamp,field.header.frame_id,field.height,field.width,";
  for (int i = 0; i < 6; i++)
  {
    std::cout << "field.fields" << i << ".name,";
    std::cout << "field.fields" << i << ".offset,";
    std::cout << "field.fields" << i << ".datatype,";
    std::cout << "field.fields" << i << ".count,";
  }
  std::cout << "field.is_bigendian,";
  std::cout << "field.point_step,";
  std::cout << "field.row_step,";
  for (int i = 0; i < 200000; i++)
  {
    std::cout << "field.data" << i << ",";
    if (i == 200000 - 1)
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
      
      // data_size = width*point_step
      int total_size = msg->width * msg->point_step;
<<<<<<< HEAD
=======
//      std::cout << total_size << std::endl;
>>>>>>> d10f39d31127be53c67249e31bb5577a87771995
      for (int i = 0; i < total_size; i++)
      {
        std::cout << (uint)msg->data[i] << ",";
      }
      std::cout << (bool)msg->is_dense << std::endl;
      
    }
  }

  bag.close();

  return 0;
}