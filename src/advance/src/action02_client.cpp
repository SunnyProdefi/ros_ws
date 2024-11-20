#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "advance/AddIntsAction.h"

typedef actionlib::SimpleActionClient<advance::AddIntsAction> Client;

void done_cb(const actionlib::SimpleClientGoalState &state,
             const advance::AddIntsResultConstPtr &result) {
  if (state.state_ == state.SUCCEEDED) {
    ROS_INFO("最终结果:%d", result->result);
  } else {
    ROS_INFO("任务失败！");
  }
}

void active_cb() { ROS_INFO("服务已经被激活...."); }

void feedback_cb(const advance::AddIntsFeedbackConstPtr &feedback) {
  ROS_INFO("当前进度:%.2f", feedback->progress_bar);
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  ROS_INFO("action客户端实现");

  ros::init(argc, argv, "AddInts_client");
  ros::NodeHandle nh;

  Client client("addInts", true);
  client.waitForServer();

  advance::AddIntsGoal goal;
  goal.num = 10;

  client.sendGoal(goal, &done_cb, &active_cb, &feedback_cb);
  ros::spin();
  return 0;
}