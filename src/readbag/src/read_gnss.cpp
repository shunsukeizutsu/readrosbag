#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include "std_msgs/String.h"
#include <boost/foreach.hpp>
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/NavSatStatus.h"

int main()
{
    rosbag::Bag bag;
    bag.open("/home/haselab15/rosbag/2022-12-02_toyosu/2022-12-02-15-57-33.bag", rosbag::bagmode::Read);

    std::string fix = "/fix";

    std::vector<std::string> topics;
    topics.push_back(std::string(fix));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    std::cout << "%time,field.header.seq,field.header.stamp,field.header.frame_id,field.status.status,field.status.service,field.latitude,field.longitude,field.altitude,";
    for (int i = 0; i < 9; i++)
    {
        std::cout << "field.position_covariance" << i << ",";
    }
    std::cout << "field.position_covariance_type" << std::endl;

    BOOST_FOREACH (rosbag::MessageInstance const m, view)
    {
        if (m.getTopic() == fix)
        {
            std::cout << m.getTime() << ",";
            sensor_msgs::NavSatFix::ConstPtr msg = m.instantiate<sensor_msgs::NavSatFix>();
            std::cout << msg->header.seq << ",";
            std::cout << msg->header.stamp << ",";
            std::cout << msg->header.frame_id << ",";
            std::cout << (int)msg->status.status << ",";
            std::cout << msg->status.service << ",";

            printf("%0.10f,", msg->latitude);
            // 緯度
            printf("%0.10f,", msg->longitude);
            // 経度
            printf("%0.10f,", msg->altitude);
            // 高度

            for (int i = 0; i < 9; i++)
            {
                std::cout << msg->position_covariance[i] << ",";
            }
            std::cout << (uint)msg->position_covariance_type << std::endl;
        }
    }

    bag.close();
    return 0;
}