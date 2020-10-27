#include "ros/ros.h"
#include <franka/robot.h>
#include "franka_plugin/bool_key.h"

#define ROBOT_IP_STR "172.27.23.65"

bool read_status(franka_plugin::bool_key::Request &req,
                            franka_plugin::bool_key::Response &res){
  franka::Robot robot(ROBOT_IP_STR);
  franka::RobotMode robot_mode = robot.readOnce().robot_mode;
  switch(robot_mode){
    case franka::RobotMode::kOther:
      res.reply = "Other";
      break;
    case franka::RobotMode::kIdle:
      res.reply = "Idle";
      break;
    case franka::RobotMode::kMove:
      res.reply = "Move";
      break;
    case franka::RobotMode::kGuiding:
      res.reply = "Guiding";
      break;
    case franka::RobotMode::kReflex:
      res.reply = "Reflex";
      break;
    case franka::RobotMode::kUserStopped:
      res.reply = "UserStopped";
      break;
    case franka::RobotMode::kAutomaticErrorRecovery:
      res.reply = "AutomaticErrorRecovery";
      break;
    default:
      res.reply = "ERROR";
      auto full_state = robot.readOnce();
  }
  return true;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "franka_node");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("franka_node/read_status", read_status);
  ROS_INFO("Ready to return Franka robot status.");
  ros::spin();

  return 0;
}