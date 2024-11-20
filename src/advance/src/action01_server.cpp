#include "ros/ros.h"
#include "actionlib/server/simple_action_server.h"
#include "advance/AddIntsAction.h"

typedef actionlib::SimpleActionServer<advance::AddIntsAction> Server;

void cb(const advance::AddIntsGoalConstPtr& goal, Server* server) {
  int num = goal->num;
  ROS_INFO("收到的目标值：%d", num);

  int result = 0;
  advance::AddIntsFeedback feedback;
  ros::Rate rate(10);
  for (int i = 0; i < num; i++) {
    result += i;
    feedback.progress_bar = i / (double)num;
    server->publishFeedback(feedback);
    rate.sleep();
  }
  advance::AddIntsResult res;
  res.result = result;
  server->setSucceeded(res);
  ROS_INFO("计算结果：%d", result);
}

int main(int argc, char** argv) {
  setlocale(LC_ALL, "");
  ROS_INFO("action服务端实现");

  ros::init(argc, argv, "AddInts_server");
  ros::NodeHandle nh;

  Server server(nh, "addInts", boost::bind(&cb, _1, &server), false);
  server.start();
  ros::spin();
  return 0;
}