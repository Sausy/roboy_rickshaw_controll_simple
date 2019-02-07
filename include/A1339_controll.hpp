#pragma once

#include <ros/ros.h>
#include <roboy_middleware_msgs/ControlMode.h>
#include <roboy_middleware_msgs/MotorCommand.h>
#include <roboy_middleware_msgs/MotorConfigService.h>
#include <roboy_middleware_msgs/MotorStatus.h>
#include <roboy_middleware_msgs/MotorAngle.h>
#include <map>
#include <common_utilities/CommonDefinitions.h>
#include <common_utilities/MotorConfig.hpp>
#include <std_srvs/SetBool.h>

using namespace std;

class A1339Ctl
{
  public:
    A1339Ctl ();

    ros::NodeHandlePtr nh;
    ros::Subscriber stearingSub;

    vector<int> StearingData;

    void GetStearingData(const roboy_middleware_msgs::MotorAngle::ConstPtr &msg);
};
