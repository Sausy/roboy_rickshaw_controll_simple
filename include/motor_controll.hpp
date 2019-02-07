#pragma once

#include <ros/ros.h>
#include <roboy_middleware_msgs/ControlMode.h>
#include <roboy_middleware_msgs/MotorCommand.h>
#include <roboy_middleware_msgs/MotorConfigService.h>
#include <roboy_middleware_msgs/MotorStatus.h>
#include <map>
#include <common_utilities/CommonDefinitions.h>
#include <common_utilities/MotorConfig.hpp>
#include <std_srvs/SetBool.h>

using namespace std;

struct motordata {
    vector<double>    position;
    vector<double>    velocity;
    vector<double>    displacement;
    vector<double>    current;
};

class motorCtl
{
  public:
    motorCtl ();

    ros::NodeHandlePtr  nh;
    ros::Subscriber     motorStatus;
    ros::Publisher      motorCommand;
    ros::ServiceClient  motorControl[6], motorConfig[6], emergencyStop[6];

    //stores all info about the motors
    motordata motorData;

    int total_number_of_motors = 0, number_of_fpgas = 6;

    void GetMotorData(const roboy_middleware_msgs::MotorStatus::ConstPtr &msg);
    void setPoint(double setPoint, uint motor);
    void setPointAll(double setPoint);

  private:
    bool stopButton;
    vector<double> setpoint;
    vector<int> control_mode;
};
