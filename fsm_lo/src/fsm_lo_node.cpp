/*
 * fsm - [IROS'22] Obtain robust odometry from your noisy panoramic 2D LIDAR
 *
 * Copyright (c) 2022 Alexandros PHILOTHEOU
 *
 * Licensed under the MIT License.
 * See LICENSE.MIT for details.
 */
#include <fsm_lo.hpp>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "fsm_lo");
  ros::NodeHandle nh;
  ros::NodeHandle nh_private("~");

  FSMLO fsmlo(nh, nh_private);

  ros::spin();
  return 0;
}
