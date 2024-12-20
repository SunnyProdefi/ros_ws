#include "ros/ros.h"
#include "hello.h"

namespace hello_ns {
void HelloPub::run() { ROS_INFO("自定义头文件的使用...."); }
}  // namespace hello_ns

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  ros::init(argc, argv, "test_head_node");
  hello_ns::HelloPub helloPub;
  helloPub.run();
  return 0;
}