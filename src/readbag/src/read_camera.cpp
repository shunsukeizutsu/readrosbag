#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include "std_msgs/String.h"
#include <boost/foreach.hpp>
#include <stdint.h>
#include <stdio.h>
#include <cstdint>
#include "sensor_msgs/Image.h"

int main()
{
    rosbag::Bag bag;
    bag.open("/home/haselab15/rosbag/2022-12-02_toyosu/2022-12-02-15-57-35.bag", rosbag::bagmode::Read);

    std::string camera = "/usb_cam/image_raw";

    std::vector<std::string> topics;
    topics.push_back(camera);

    rosbag::View view(bag, rosbag::TopicQuery(camera));

    std::cout << "%time,field.header.seq,field.header.stamp,field.header.frame_id,";
    std::cout << "field.height,field.width,field.encoding,field.is_bigendian,field.step,";
    for(int i=0;i<921600;i++)
    {
        std::cout << "field.data" << i << ",";
    }
    std::cout << std::endl;

    BOOST_FOREACH (rosbag::MessageInstance const m, view)
    {
        if (m.getTopic() == camera)
        {
            sensor_msgs::Image::ConstPtr msg = m.instantiate<sensor_msgs::Image>();
            std::cout << "none" << ",";
            std::cout << msg->header.seq << ",";
            std::cout << msg->header.stamp << ",";
            std::cout << msg->header.frame_id << ",";
            std::cout << msg->height << ",";
            std::cout << msg->width << ",";
            std::cout << msg->encoding << ",";
            std::cout << (int)msg->is_bigendian << ",";
            std::cout << msg->step << ",";
            int total_size=msg->step*msg->height;
            //total_size=921600
            for(int i=0;i<total_size;i++)
            {
                std::cout << (int)msg->data[i] << ",";
            }
            std::cout << std::endl;
        }
    }
    bag.close();
    return 0;
}