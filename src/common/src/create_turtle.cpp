#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  ros::init(argc, argv, "create_turtle");
  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
  ros::service::waitForService("/spawn");

  turtlesim::Spawn spawn;
  spawn.request.name = "turtle2";
  spawn.request.x = 1.0;
  spawn.request.y = 2.0;
  spawn.request.theta = 3.12415926;

  bool flag = client.call(spawn);
  if (flag) {
    ROS_INFO("Success: %s", spawn.response.name.c_str());
  } else {
    ROS_ERROR("Failed to call service /spawn");
    return 1;
  }

  ros::spin();

  return 0;
}