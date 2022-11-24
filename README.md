# readrosbag
rosbagファイルを読み込むためのリポジトリ

11-23
・practice_rosをもとにimuのデータを出力するプログラムを作成したが、中身がない
・m.getTopic()を行ったところ、velodyne and fixしか表示されていないため、velodyne and fix のプログラムを先に作成することにした。

・fixのデータを出力するプログラムを作成することはできた
しかし、バイナリ形式の部分がありそこは改善しなければいけない

次回、velodyneのデータを作成する
また、IMUのデータの在り処を見つける

11-24
・velodyneのデータを出力するプログラムを作成したが、data[]が出力できずにいる。
・まず、velodyne_msgs::VelodynePoints2 or velodyne_msgs::VelodynePacketのどちらをインスタンス化すればよいかわからない。（velodyne_msgs::VelodynePacketはインスタンス化されない）
・しかし、driverではdataはvelodyne_msgs::VelodynePacketに保存されているように見えるが、はっきりしない

