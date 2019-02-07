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
  char input_kb;
  int count = 0;

  cout << "start control";

  //init ros
  if (!ros::isInitialized()){
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "rickshaw_ctl_node");
  }
  ros::NodeHandle n;
  ros::Rate loop_rate(10);

  RickshawCtl rickshaw(9,10); //currently motor9 and 10 are used to stear


  cout << "please enter command\n";
  while (ros::ok())
  {
    cin >> input_kb;
    if(input_kb == 't')
      rickshaw.TestMotor(200);
    if(input_kb == 'o')
        rickshaw.TestMotor(0);

    rickshaw.TurnBike_Left();
    cout << "angle sensor:" << rickshaw.ReadOutStearingAngle();

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
    if (count >= 1000)
      break;
  }

  return 0;
}
