#include "ros/ros.h"
#include "dynamic_reconfigure/server.h"
#include "dynamicreconfigure/drConfig.h"

void cb(dynamicreconfigure::drConfig& config, uint32_t level) {
  ROS_INFO("动态参数解析数据:%d,%.2f,%d,%s,%d", config.int_param,
           config.double_param, config.bool_param, config.string_param.c_str(),
           config.list_param);
}

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "");

  ros::init(argc, argv, "dr");

  dynamic_reconfigure::Server<dynamicreconfigure::drConfig> server;
  dynamic_reconfigure::Server<dynamicreconfigure::drConfig>::CallbackType
      cbType;
  cbType = boost::bind(&cb, _1, _2);
  server.setCallback(cbType);

  ros::spin();

  return 0;
}