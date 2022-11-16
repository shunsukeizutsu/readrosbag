#include <iostream>
#include <ros/time.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <rosbag/bag.h>
//#include <rosbag/chunked_file.h>
#include <rosbag/query.h>
#include <rosbag/message_instance.h>
#include <boost/foreach.hpp>
#include <vector>

int main(int argc, char **argv)
{
	rosbag::Bag bag;
	
	bag.open("/home/shunsuke/rosbag/2022-08-19-16-07-21.bag",rosbag::bagmode::Read);
	

	std::cout << bag.getFileName() << std::endl;

	std::string fix="/fix";
	std::string imu="/imu/data_raw";
	std::string vel="/velodyne_points";


	std::vector<std::string> topics;
	
	topics.push_back(fix);
	topics.push_back(imu);
	topics.push_back(vel);

	
	rosbag::View view(bag, rosbag::TopicQuery(topics));
	


	BOOST_FOREACH(rosbag::MessageInstance const m, view)
	{
		std::cout << m.getTopic() << std::endl;

		std_msgs::Int32::ConstPtr s = m.instantiate<std_msgs::Int32>();
		if(m.getTopic() == fix || ("/" + m.getTopic() == fix))
		{
//			std::cout << m.getTopic() << std::endl;
			std::cout << s->data << std::endl;
		}
/*
		if(m.getTopic() == fix || ("/" + m.getTopic() == fix))
		{
			std::cout << 1 << std::endl;
		}

		if(m.getTopic() == imu || ("/" + m.getTopic() == imu))
		{
			std::cout << 2 << std::endl;
		}

		std::cout << 3 << std::endl;
*/
	}	
	//std::cout << ros::Time getStartTime() << std::endl;



    bag.close();

    return 0;
}
