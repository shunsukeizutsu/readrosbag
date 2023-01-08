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
    bag.open("/home/haselab15/rosbag/210601_0858/2021-06-01-08-58-07.bag", rosbag::bagmode::Read);

    std::string imu = "/imu/data_raw";

    std::vector<std::string> topics;
    topics.push_back(std::string(imu));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    std::cout << "%time,field.header.seq,field.header.stamp,field.header.frame_id,field.orientation.x,field.orientation.y,field.orientation.z,field.orientation.w,";
    for (int i = 0; i < 9; i++)
    {
        std::cout << "field.orientation_covariance" << i << ",";
    }
    std::cout << "field.angular_velocity.x,field.angular_velocity.y,field.angular_velocity.z,";
    for (int j = 0; j < 9; j++)
    {
        std::cout << "field.angular_velocity_convariance" << j << ",";
    }
    std::cout << "field.linear_acceleration.x,field.linear_acceleration.y,field.linear_acceleration.z,";
    for (int i = 0; i < 9; i++)
    {
        std::cout << "field.linear_acceleration_covariance" << i << ",";
    }
    std::cout << std::endl;

    BOOST_FOREACH (rosbag::MessageInstance const m, view)
    {
        if (m.getTopic() == imu)
        {
            sensor_msgs::Imu::ConstPtr msg = m.instantiate<sensor_msgs::Imu>();
            std::cout << msg->header.stamp << ",";
            std::cout << msg->header.seq << ",";
            std::cout << msg->header.stamp << ",";
            std::cout << msg->header.frame_id << ",";
            std::cout << msg->orientation.x << ",";
            std::cout << msg->orientation.y << ",";
            std::cout << msg->orientation.z << ",";
            std::cout << msg->orientation.w << ",";

            for (int i = 0; i < 9; i++)
            {
                printf("%lf,",(double)msg->orientation_covariance[i]);//covariance共分散
            }

            //角速度
            printf("%0.16f,%0.16f,%0.16f,",msg->angular_velocity.x,msg->angular_velocity.y,msg->angular_velocity.z);
            for (int i = 0; i < 9; i++)
            {
                printf("%0.16f,",msg->angular_velocity_covariance[i]);
            }
            //加速度
            printf("%0.14f,%0.14f,%0.14f,",msg->linear_acceleration.x,msg->linear_acceleration.y,msg->linear_acceleration.z);
            for (int i = 0; i < 9; i++)
            {
                printf("%0.12f,",(double)msg->linear_acceleration_covariance[i]);
            }
            printf("\n");
        }
    }
    bag.close();
    return 0;
}