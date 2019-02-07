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

#include "A1339_controll.hpp"
#include "motor_controll.hpp"

using namespace std;

class RickshawCtl
{
  public:
    RickshawCtl (uint left_motor_,uint right_motor_);

    void TurnBike_Left();
    void TurnBike_Right();
    int ReadOutStearingAngle();

    void TestMotor(double point_);

    motordata *motorData;


  private:
    motorCtl motor_Ctl;
    A1339Ctl A1339_Ctl;
    vector<double> motorData_point;
    vector<int> motorData_mode;
    uint left_motor, right_motor;

    double stearingForce_actor=300, stearingForce_reactor=1;

    void Turn(uint actorMotorSelect_,uint reactorMotorSelect_);
};
