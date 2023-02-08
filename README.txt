プログラム内容
read_imu.cpp：加速度、角速度
read_gnss.cpp：緯度、経度、高度
read_velodyne.cpp：点群
read_camera.cpp：RGBデータ

************.bag->.csv流れ*****************
1.各プログラムでbagファイルのパスを設定する
12行目 bag.open("bagファイルの名前")

2.terminal内で実行
source devel/setup.bash

3.readrosbag内
catkin_make

4.実行する
IMU   :rosrun readbag read_imu > imu_log.csv
GNSS  :rosrun readbag read_gnss > gnss_log.csv
LiDAR :rosrun readbag read_vel > lidar_log.csv

