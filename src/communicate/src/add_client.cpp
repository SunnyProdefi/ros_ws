#include "ros/ros.h"
#include "communicate/add.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  if (argc != 3) {
    ROS_ERROR("请提交两个整数");
    return 1;
  }

  ros::init(argc, argv, "add_client");
  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<communicate::add>("add");
  ros::service::waitForService("add");

  communicate::add a;
  a.request.num1 = atoi(argv[1]);
  a.request.num2 = atoi(argv[2]);

  bool flag = client.call(a);
  if (flag) {
    ROS_INFO("请求正常处理,响应结果:%d", a.response.sum);
  } else {
    ROS_ERROR("请求处理失败....");
    return 1;
  }
  return 0;
}