#include <A1339_controll.hpp>

A1339Ctl::A1339Ctl()
{
  if (!ros::isInitialized()) {
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "AngleStatus");
  }
  nh = ros::NodeHandlePtr(new ros::NodeHandle);

  stearingSub = nh->subscribe("/roboy/middleware/StearingAngle", 1, &A1339Ctl::GetStearingData, this);
}

/*
-----msg MotorAngle------
uint8 id
float32[] angles
int32[] raw_angles
int32[] raw_angles_prev
int32[] offset_angles
int32[] relative_angles
int32[] rev_counter
*/

void A1339Ctl::GetStearingData(const roboy_middleware_msgs::MotorAngle::ConstPtr &msg){
  StearingData.clear();
  for (uint cnt = 0; cnt < msg->raw_angles.size(); cnt++) {
    StearingData.push_back(msg->raw_angles[cnt]);
  }
}
