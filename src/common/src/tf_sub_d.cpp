#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "");

  ros::init(argc, argv, "dynamic_tf_sub");
  ros::NodeHandle nh;

  tf2_ros::Buffer buffer;
  tf2_ros::TransformListener listener(buffer);

  ros::Rate r(1);
  while (ros::ok()) {
    geometry_msgs::PointStamped point_laser;
    point_laser.header.frame_id = "turtle1";
    point_laser.header.stamp = ros::Time();
    point_laser.point.x = 1;
    point_laser.point.y = 1;
    point_laser.point.z = 0;
    try {
      geometry_msgs::PointStamped point_base;
      point_base = buffer.transform(point_laser, "world");
      ROS_INFO("坐标点相对于 world 的坐标为:(%.2f,%.2f,%.2f)",
               point_base.point.x, point_base.point.y, point_base.point.z);

    } catch (const std::exception& e) {
      // std::cerr << e.what() << '\n';
      ROS_INFO("程序异常:%s", e.what());
    }

    r.sleep();
    ros::spinOnce();
  }
  return 0;
}