#include <rickshaw_ctl.hpp>

RickshawCtl::RickshawCtl()
{
  total_number_of_motors = 14;


  if (!ros::isInitialized()) {
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "rickshaw_ctl_node");
  }
  nh = ros::NodeHandlePtr(new ros::NodeHandle);


  motorStatus = nh->subscribe("/roboy/middleware/MotorStatus", 1, &RickshawCtl::GetMotorData, this);
  motorCommand = nh->advertise<roboy_middleware_msgs::MotorCommand>("/roboy/middleware/MotorCommand", 1);


  roboy_middleware_msgs::MotorCommand msg_command;
  roboy_middleware_msgs::ControlMode msg_mode;
  msg_mode.request.control_mode = DISPLACEMENT;
  for (uint motor = 0; motor < total_number_of_motors; motor++) {
    //control_mode[0] = DISPLACEMENT;
    //setpoint[motor] = 0;
    /*msg_command.set_points.push_back(setpoint[motor]);*/
  }
  //motorCommand.publish(msg_command);*/
}

void RickshawCtl::GetMotorData(const roboy_middleware_msgs::MotorStatus::ConstPtr &msg){
    //msg->position[motor];
    //msg->velocity[motor];
    //msg->displacement[motor];
    //msg->current[motor];
    motor_data[0] = msg->current[12];

    ROS_INFO("\n%d", motor_data[0]);
}

void RickshawCtl::setPoint(double setPoint, uint motor){
    setpoint[motor] = setPoint;
    setPointAll(setPoint);
}

void RickshawCtl::setPointAll(double setPoint){
  roboy_middleware_msgs::MotorCommand msg;
  double motor_scale = 1; //TODO: change

  for (uint motor = 0; motor < total_number_of_motors; motor++) {
    msg.set_points.push_back(setpoint[motor]);
  }
  motorCommand.publish(msg);
}
