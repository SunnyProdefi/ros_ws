#include "ros/ros.h"
#include "communicate/person.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  ros::init(argc, argv, "talker_person");
  ros::NodeHandle nh;
  ros::Publisher pub =
      nh.advertise<communicate::person>("chatter_person", 1000);

  communicate::person p;
  p.name = "sunwukong";
  p.age = 2000;
  p.height = 1.45;

  ros::Rate r(1);
  while (ros::ok()) {
    pub.publish(p);
    p.age += 1;
    ROS_INFO("我叫:%s,今年%d岁,高%.2f米", p.name.c_str(), p.age, p.height);
    r.sleep();
    ros::spinOnce();
  }
  return 0;
}