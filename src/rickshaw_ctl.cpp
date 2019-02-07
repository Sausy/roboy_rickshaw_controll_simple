#include <rickshaw_ctl.hpp>


//uint8_t actorMotorSelect, reactorMotorSelect;
RickshawCtl::RickshawCtl(uint left_motor_,uint right_motor_){
  left_motor=left_motor_;
  right_motor=right_motor_;

  stearingForce_actor=300;
  stearingForce_reactor=1;

  motorData = &motor_Ctl.motorData;
};

void RickshawCtl::Turn(uint actorMotorSelect_,uint reactorMotorSelect_){
  motor_Ctl.setPoint(stearingForce_actor,actorMotorSelect_);
  motor_Ctl.setPoint(stearingForce_reactor,reactorMotorSelect_);
}

void RickshawCtl::TurnBike_Left(){
  Turn(right_motor,left_motor);
}

void RickshawCtl::TurnBike_Right(){
    Turn(left_motor,right_motor);
}

void RickshawCtl::TestMotor(double point_){
  motor_Ctl.setPointAll(point_);
}

int RickshawCtl::ReadOutStearingAngle(){
  for (uint cnt = 0; cnt < A1339_Ctl.StearingData.size(); cnt++) {
    if(A1339_Ctl.StearingData[cnt] > 0)
      return(A1339_Ctl.StearingData[cnt]);
  }
  return 0;
}
