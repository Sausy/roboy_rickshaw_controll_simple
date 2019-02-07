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
  char input_kb = NULL;
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


  while (ros::ok())
  {

    if(input_kb == 'r'){
      rickshaw.TurnBike_Left();
      cout << "\nangle sensor:" << rickshaw.ReadOutStearingAngle();
      cout << "\ncurrent.data:";
      for(int i=0; i<rickshaw.motorData->current.size();i++)
         cout << rickshaw.motorData->current[i] << " , ";

      ros::spinOnce();
      loop_rate.sleep();
      ++count;
      if (count >= 1000)
        break;
    }else{
      cout << "please enter command \n";
      cout << "r=readoutAngle t=testMotor o=allMotorsOff k=exit\n";
      cin >> input_kb;
      if(input_kb == 't')
        rickshaw.TestMotor(200);
      if(input_kb == 'o')
          rickshaw.TestMotor(0);
      if(input_kb == 'k')
          break;
    }


  }

  return 0;
}


/*

if(input_kb == 'r'){
  rickshaw.TurnBike_Left();
  cout << "angle sensor:" << rickshaw.ReadOutStearingAngle();
  ros::spinOnce();
  loop_rate.sleep();
  ++count;
  if (count >= 1000)
    break;
}else{
  cout << "please enter command \n";
  cout << "r=readoutAngle t=testMotor o=allMotorsOff\n";
  cin >> input_kb;
  if(input_kb == 't')
    rickshaw.TestMotor(200);
  if(input_kb == 'o')
      rickshaw.TestMotor(0);
}


*/
