#include <motor_controll.hpp>

motorCtl::motorCtl()
{
  total_number_of_motors = 14;

  if (!ros::isInitialized()) {
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "motor_controll");
  }
  nh = ros::NodeHandlePtr(new ros::NodeHandle);

  motorStatus = nh->subscribe("/roboy/middleware/MotorStatus", 1, &motorCtl::GetMotorData, this);
  motorCommand = nh->advertise<roboy_middleware_msgs::MotorCommand>("/roboy/middleware/MotorCommand", 1);
  motorConfig = nh->serviceClient<roboy_middleware_msgs::MotorConfigService>("/roboy/shoulder_left/middleware/MotorConfig");


  roboy_middleware_msgs::ControlMode msg_mode;
  msg_mode.request.control_mode = DISPLACEMENT;
  msg_mode.request.set_point = 1;

  roboy_middleware_msgs::MotorCommand msg_command;
  msg_command.id=3;
  for (uint motor = 0; motor < total_number_of_motors; motor++) {
    control_mode.push_back(DISPLACEMENT);
    setpoint.push_back(1);
    msg_command.set_points.push_back(setpoint[motor]);
  }
  motorCommand.publish(msg_command);
}


//msg->position[motor];
//msg->velocity[motor];
//msg->displacement[motor];
//msg->current[motor];
void motorCtl::GetMotorData(const roboy_middleware_msgs::MotorStatus::ConstPtr &msg){
    motorData = {};
    for (uint cnt = 0; cnt < msg->current.size(); cnt++) {
      motorData.position.push_back(msg->position[cnt]);
      motorData.velocity.push_back(msg->velocity[cnt]);
      motorData.displacement.push_back(msg->displacement[cnt]);
      motorData.current.push_back(msg->current[cnt]);
    }
}

//-------to send out movement data to motor------
void motorCtl::setPoint(double setPoint, uint motor){
    setpoint[motor] = setPoint;
    setPointAll(setPoint);
}

void motorCtl::setPointAll(double setPoint){
  roboy_middleware_msgs::MotorCommand msg_command;
  msg_command.id=3;
  double motor_scale = 1; //TODO: change

  for (uint motor = 0; motor < total_number_of_motors; motor++) {
    msg_command.set_points.push_back(setpoint[motor]);
  }
  motorCommand.publish(msg_command);
}

void motorCtl::update_config(){
    roboy_middleware_msgs::MotorConfigService msg_MotorConfigService;
    for(int i=0;i<total_number_of_motors;i++){
        msg_MotorConfigService.request.config.motors.push_back(i);
        msg_MotorConfigService.request.config.setpoint.push_back(0);
        msg_MotorConfigService.request.config.control_mode.push_back(DISPLACEMENT);
        msg_MotorConfigService.request.config.output_pos_max.push_back(motorConfigData.outputPosMax);
        msg_MotorConfigService.request.config.output_neg_max.push_back(motorConfigData.outputNegMax);
        msg_MotorConfigService.request.config.sp_pos_max.push_back(motorConfigData.spPosMax);
        msg_MotorConfigService.request.config.sp_neg_max.push_back(motorConfigData.spNegMax);
        msg_MotorConfigService.request.config.integral_pos_max.push_back(motorConfigData.integralPosMax);
        msg_MotorConfigService.request.config.integral_neg_max.push_back(motorConfigData.integralNegMax);
        msg_MotorConfigService.request.config.dead_band.push_back(motorConfigData.deadband);
        msg_MotorConfigService.request.config.kp.push_back(motorConfigData.Kp);
        msg_MotorConfigService.request.config.ki.push_back(motorConfigData.Ki);
        msg_MotorConfigService.request.config.kd.push_back(motorConfigData.Kd);
        msg_MotorConfigService.request.config.forward_gain.push_back(motorConfigData.forwardGain);
        msg_MotorConfigService.request.config.output_divider.push_back(motorConfigData.outputDivider);
    }
    motorConfig.call(msg_MotorConfigService);
}
