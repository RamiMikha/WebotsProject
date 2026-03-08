#include <webots/robot.h>
#include <webots/supervisor.h>
#include <stdio.h>
#include <math.h>

#define TIME_STEP  64

#define GOAL_X  0.35
#define GOAL_Y  0.35
#define GOAL_R  0.10

int main(int argc, char **argv) {
  wb_robot_init();

  WbNodeRef epuck = wb_supervisor_node_get_from_def("EPUCK");
  if (!epuck) {
    printf("[goal_checker] ERROR: Could not find EPUCK node.\n");
    wb_robot_cleanup();
    return 1;
  }

  printf("[goal_checker] Watching robot. Goal zone: (%.2f, %.2f) r=%.2f\n",
         GOAL_X, GOAL_Y, GOAL_R);

  while (wb_robot_step(TIME_STEP) != -1) {
    const double *pos = wb_supervisor_node_get_position(epuck);
    double dx = pos[0] - GOAL_X;
    double dy = pos[1] - GOAL_Y;
    double dist = sqrt(dx*dx + dy*dy);

    if (dist < GOAL_R) {
      printf("\n");
      printf("===========================================\n");
      printf("   SUCCESS! Robot reached the exit!\n");
      printf("   Position: (%.3f, %.3f)\n", pos[0], pos[1]);
      printf("===========================================\n");
      wb_supervisor_simulation_set_mode(WB_SUPERVISOR_SIMULATION_MODE_PAUSE);
      break;
    }
  }

  wb_robot_cleanup();
  return 0;
}
