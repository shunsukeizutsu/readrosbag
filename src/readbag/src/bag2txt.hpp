/*地図作成　bagデータをテキストファイルに保存するクラス
 *Date : 2024\02\29
 *Author : S.Izutsu
 */
#ifdef BAG_TO_TXT_HPP_
#define BAG_TO_TXT_HPP_

#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
#include <ifstream>
#include <boost/foreach.hpp>
#include "sensor_msgs/Imu.h"
#include <rosbag/bag.h>
#include <rosbag/view.h>
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

#endif