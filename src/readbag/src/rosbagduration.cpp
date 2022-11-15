#include <ros/time.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <rosbag/bag.h>
//#include <rosbag/chunked_file.h>
#include <rosbag/query.h>
#include <rosbag/message_instance.h>
#include <boost/foreach.hpp>
#include <vector>

int main(int argc, char **argv)
{
	rosbag::Bag bag;
	
	bag.open("/home/shunsuke/turtlebag/2022-11-16-00-48-39.bag",rosbag::bagmode::Read);
	
	std::string rosout="/rosout";
	std::string rosout_agg="/rosout_agg";
	std::string vel="turtle1/cmd_vel";
	std::string colorsen="turtle1/color_sensor";
	std::string pose="turtle1/pose";



	std::vector<std::string> topics;
	
	topics.push_back(rosout);
	topics.push_back(rosout_agg);
	topics.push_back(vel);
	topics.push_back(colorsen);
	topics.push_back(pose);
	
	rosbag::View view(bag, rosbag::TopicQuery(topics));
	
	//std::cout << "なし" << std::endl;

	BOOST_FOREACH(rosbag::MessageInstance const m, view)
	{
		if(m.getTopic() == rosout || ("/" + m.getTopic() == rosout))
		{
			std::cout << m.getTopic() << std::endl;
			std::cout << "rosourtrue" << std::endl;
		}
		if(m.getTopic() == rosout_agg || ("/" + m.getTopic() == rosout_agg))
		{
			std::cout << "aggtrue" << std::endl;
		}
		if(m.getTopic() == vel || ("/" + m.getTopic() == vel))
		{
			std::cout << "veltrue" << std::endl;
		}
		
		if(m.getTopic() == colorsen || ("/" + m.getTopic() == colorsen))
		{
			std::cout << "colorsentrue" << std::endl;
		}
		
		if(m.getTopic() == pose || ("/" + m.getTopic() == pose))
		{
			std::cout << "posetrue" << std::endl;
		}
		//std::cout << "なし" << std::endl;
		
	}
	
	
	
	//std::cout << ros::Time getStartTime() << std::endl;

//	std::cout << bag.getSize() << std::endl;
//	std::cout << bag.getMajorVersion() << std::endl;
//	std::cout << bag.getMinorVersion() << std::endl;
//	std::cout << bag.getMode() << std::endl;//Write=1,Read=2,Append=4

    bag.close();

    return 0;
}
