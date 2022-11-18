#include "ros/ros.h"
#include <time.h>
#include <rosbag/bag.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>


int main()
{
    
    rosbag::Bag bag;
    ros::start();

    bag.open("test.bag");
    std_msgs::String str;
    str.data=std::string("foo");

    //std_msgs::Int32 i;
    //i.data = 42;
    //ros::Time::waitForValid();
    bag.write("chatter",ros::Time::now(), str);
    //bag.write("numbers",ros::Time::now(), i);

    bag.close();

    return 0;
}