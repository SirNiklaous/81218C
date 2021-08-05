#include "move.h"
#include "vex.h"

using namespace vex;

const double circumference = 12.5663706143592;

void move::moveBot(float d, float s) {
  double leftTarget = left_front.position(turns) * circumference + d;
  double rightTarget = right_front.position(turns) * circumference - d;
  if(d >= 0) {
    while(left_front.position(turns) * circumference < leftTarget && right_front.position(turns) * circumference > rightTarget) {
      left_front.setVelocity(s, percent);
      left_back.setVelocity(s, percent);
      right_front.setVelocity(s, percent);
      right_back.setVelocity(s, percent);
    }
  }
  else{
    while(left_front.position(turns) * circumference > leftTarget && right_front.position(turns) * circumference < rightTarget) {
      left_front.setVelocity(-s, percent);
      left_back.setVelocity(-s, percent);
      right_front.setVelocity(-s, percent);
      right_back.setVelocity(-s, percent);
    }
  }
  left_front.setVelocity(0, percent);
  left_back.setVelocity(0, percent);
  right_front.setVelocity(0, percent);
  right_back.setVelocity(0, percent);
}