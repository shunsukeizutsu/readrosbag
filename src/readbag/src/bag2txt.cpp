#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include <boost/foreach.hpp>
#include "sensor_msgs/Imu.h"
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include "utility.hpp"
class Bag2Txt_Base
{
protected:
    FILE *savefp;
    bool flag_first_loop;
    double start_time;

public:
    Bag2Txt_Base(void) : start_time(0), flag_first_loop(true) {}
    ~Bag2Txt_Base(void) {}
    void openSaveFile(const char *save_filename);
    void closeSaveFile(void)
    {
        fclose(savefp);
    }
};
//****IMU****
class Bag2Txt_IMU : public Bag2Txt_Base
{
public:
    Bag2Txt_IMU(void) {}
    ~Bag2Txt_IMU(void) {}
    bool bag2txt(sensor_msgs::Imu::ConstPtr msg, ros::Time time);
};
void Bag2Txt_Base:: openSaveFile(const char *save_filename)
{
	char filename[STRLEN];
	sprintf(filename, "../data/%s", save_filename);
	printf("Save File = %s\n", filename); // 確認用
	savefp = isValidFile(filename, "w", "dat");
	flag_first_loop = true;
}
// ************************** for IMU ********************************
bool Bag2Txt_IMU::bag2txt(sensor_msgs::Imu::ConstPtr msg, ros::Time time)
{
	if (flag_first_loop)
	{
		flag_first_loop = false;
		return false;
	}
	else
	{
		fprintf(savefp, "%u,", time);
		fprintf(savefp, "%d,%f,%f,", msg->header.seq, msg->header.stamp, msg->header.frame_id);
		fprintf(savefp, "%f,%f,%f,%f,", msg->orientation.x, msg->orientation.y, msg->orientation.z, msg->orientation.w);
		for (int i = 0; i < 9; i++)
		{
			fprintf(savefp, "%lf,", (double)msg->orientation_covariance[i]);
		}
		fprintf(savefp, "%0.16f,%0.16f,%0.16f,", msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z);
		for (int i = 0; i < 9; i++)
		{
			fprintf(savefp, "%lf,", msg->angular_velocity_covariance[i]);
		}
		fprintf(savefp, "%0.14f,%0.14f,%0.14f,", msg->linear_acceleration.x, msg->linear_acceleration.y, msg->linear_acceleration.z);
		/*for (int i = 0; i < 9; i++)
		{
			fprintf(savefp, "%lf,", (double)msg->linear_acceleration_covariance[i]);
		}*/
		fprintf(savefp,"\n");
	}
	return true;
}
