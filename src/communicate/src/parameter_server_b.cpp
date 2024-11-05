#include "ros/ros.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  ros::init(argc, argv, "get_param");

  ros::NodeHandle nh;

  // param函数
  int res1 = nh.param("nh_int", 100);
  int res2 = nh.param("nh_int2", 100);
  ROS_INFO("param获取结果:%d,%d", res1, res2);

  // getPara函数
  int nh_int_value;
  double nh_double_value;
  bool nh_bool_value;
  std::string nh_string_value;
  std::vector<std::string> stus;
  std::map<std::string, std::string> friends;

  nh.getParam("nh_int", nh_int_value);
  nh.getParam("nh_double", nh_double_value);
  nh.getParam("nh_bool", nh_bool_value);
  nh.getParam("nh_string", nh_string_value);
  nh.getParam("nh_vector", stus);
  nh.getParam("nh_map", friends);

  ROS_INFO("getParam获取的结果:%d,%.2f,%s,%d", nh_int_value, nh_double_value,
           nh_string_value.c_str(), nh_bool_value);

  for (auto &stu : stus) {
    ROS_INFO("stus 元素: %s", stu.c_str());
  }

  for (auto &f : friends) {
    ROS_INFO("map 元素 : %s = %s", f.first.c_str(), f.second.c_str());
  }

  // getParamCached()
  nh.getParamCached("nh_int", nh_int_value);
  ROS_INFO("通过缓存获取数据：%d", nh_int_value);

  // getParamNames()
  std::vector<std::string> param_names1;
  nh.getParamNames(param_names1);
  for (auto &name : param_names1) {
    ROS_INFO("名称解析name = %s", name.c_str());
  }

  // hasParam()
  ROS_INFO("存在 nh_int 吗? %d", nh.hasParam("nh_int"));
  ROS_INFO("存在 nh_intttt 吗? %d", nh.hasParam("nh_intttt"));

  // searchParam()
  std::string key;
  nh.searchParam("nh_int", key);
  ROS_INFO("搜索键：%s", key.c_str());
}