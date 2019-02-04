#include <ros/ros.h>
#include <roboy_middleware_msgs/ControlMode.h>
#include <roboy_middleware_msgs/MotorCommand.h>
#include <roboy_middleware_msgs/MotorConfigService.h>
#include <roboy_middleware_msgs/MotorStatus.h>
#include <common_utilities/CommonDefinitions.h>
#include <common_utilities/MotorConfig.hpp>

#include "rickshaw_ctl.hpp"

using namespace std;

int main(int argc, char **argv){
  cout << "start control";


  RickshawCtl rickshaw;

  //init ros
  if (!ros::isInitialized()) {
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "rickshaw_ctl_node");
  }
  ros::NodeHandle n;
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    cout << "please enter command\n";

    //rickshaw.setPointAll(20);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
    if (count >= 1000)
      break;
  }

  return 0;
}
