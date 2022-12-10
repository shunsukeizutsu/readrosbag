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
    bag.open("/home/haselab15/rosbag/toyosu_park/2022-12-02-15-57-35.bag", rosbag::bagmode::Read);

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
            /*std::cout << msg->orientation_covariance[0] << ",";
            std::cout << msg->orientation_covariance[1] << ",";
            std::cout << msg->orientation_covariance[2] << ",";
            std::cout << msg->orientation_covariance[3] << ",";
            std::cout << msg->orientation_covariance[4] << ",";
            std::cout << msg->orientation_covariance[5] << ",";
            std::cout << msg->orientation_covariance[6] << ",";
            std::cout << msg->orientation_covariance[7] << ",";
            std::cout << msg->orientation_covariance[8] << ",";*/
            /*
            std::cout << msg->angular_velocity.x << ",";
            std::cout << msg->angular_velocity.y << ",";
            std::cout << msg->angular_velocity.z << ",";*/
            /*std::cout << msg->angular_velocity_covariance[0] << ",";
            std::cout << msg->angular_velocity_covariance[1] << ",";
            std::cout << msg->angular_velocity_covariance[2] << ",";
            std::cout << msg->angular_velocity_covariance[3] << ",";
            std::cout << msg->angular_velocity_covariance[4] << ",";
            std::cout << msg->angular_velocity_covariance[5] << ",";
            std::cout << msg->angular_velocity_covariance[6] << ",";
            std::cout << msg->angular_velocity_covariance[7] << ",";
            std::cout << msg->angular_velocity_covariance[8] << ",";
            std::cout << msg->linear_acceleration.x << ",";
            std::cout << msg->linear_acceleration.y << ",";
            std::cout << msg->linear_acceleration.z << ",";
            */
            /*std::cout << msg->linear_acceleration_covariance[0] << ",";
            std::cout << msg->linear_acceleration_covariance[1] << ",";
            std::cout << msg->linear_acceleration_covariance[2] << ",";
            std::cout << msg->linear_acceleration_covariance[3] << ",";
            std::cout << msg->linear_acceleration_covariance[4] << ",";
            std::cout << msg->linear_acceleration_covariance[5] << ",";
            std::cout << msg->linear_acceleration_covariance[6] << ",";
            std::cout << msg->linear_acceleration_covariance[7] << ",";
            std::cout << msg->linear_acceleration_covariance[8] << std::endl;*/
            printf("\n");
        }
    }
    bag.close();
    return 0;
}