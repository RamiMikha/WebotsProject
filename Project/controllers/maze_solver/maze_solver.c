#include <webots/robot.h>
#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <stdio.h>
#include <stdbool.h>

#define TIME_STEP       64
#define MAX_SPEED       4.0
#define WALL_THRESHOLD  120.0

int main(int argc, char **argv) {
  wb_robot_init();

  WbDeviceTag ps[8];
  char ps_names[8][4] = {"ps0","ps1","ps2","ps3","ps4","ps5","ps6","ps7"};
  for (int i = 0; i < 8; i++) {
    ps[i] = wb_robot_get_device(ps_names[i]);
    wb_distance_sensor_enable(ps[i], TIME_STEP);
  }

  WbDeviceTag left_motor  = wb_robot_get_device("left wheel motor");
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor,  INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor,  0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  printf("[maze_solver] Started.\n");

  while (wb_robot_step(TIME_STEP) != -1) {
    double v[8];
    for (int i = 0; i < 8; i++)
      v[i] = wb_distance_sensor_get_value(ps[i]);

    bool wall_front = v[0] > WALL_THRESHOLD || v[7] > WALL_THRESHOLD;
    bool wall_left  = v[5] > WALL_THRESHOLD || v[6] > WALL_THRESHOLD;
    bool wall_right = v[1] > WALL_THRESHOLD || v[2] > WALL_THRESHOLD;

    double left_speed, right_speed;

    if (!wall_left && !wall_front) {
      left_speed  = -MAX_SPEED * 0.5;
      right_speed =  MAX_SPEED * 0.5;
    } else if (wall_left && !wall_front) {
      left_speed  = MAX_SPEED * 0.75;
      right_speed = MAX_SPEED * 0.75;
    } else if (wall_front && !wall_right) {
      left_speed  =  MAX_SPEED * 0.5;
      right_speed = -MAX_SPEED * 0.5;
    } else {
      left_speed  =  MAX_SPEED * 0.5;
      right_speed = -MAX_SPEED * 0.5;
    }

    wb_motor_set_velocity(left_motor,  left_speed);
    wb_motor_set_velocity(right_motor, right_speed);
  }

  wb_robot_cleanup();
  return 0;
}
