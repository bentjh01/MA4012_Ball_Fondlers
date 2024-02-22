#include "ball_detection.h"
//add more includes for some of the functions used inside these functions later if needed

void change_search_position(){
  //After not detecting any ball, move to a different spot.
  //This will depend on our strategy and edge detection, etc later on
}

void detect_ball(startup_phase){
  //In the main code, declare a boolean for startup_phase parameter.
  //Pass true if we just started this function for timing purposes. Afterwards, pass false for the same searching instant
  //When changing from true to false, start a timer in the main loop.
  //Once the timer exceeds a certain amount (after robot does 1 full rotation), run change_search_position()
  
  //Rotate in place and search for ball
  if(startup_phase){
    move_robot(lin_vel = 0, ang_vel = 120, lin_dir = 0, ang_dir = 1);
    //where lin_dir = 1 means go forward, 0 means backward, and ang_dir = 1 is ccw, 1 means cw
  }

  //Read distance sensors
  l_dist = read_left_dist();
  r_dist = read_right_dist();
  c_top_dist = read_center_top_dist();
  c_bot_dist = read_center_bot_dist();
  
  //Differentiate detection between ball and opp
}

void go_to_ball(){
  
}
