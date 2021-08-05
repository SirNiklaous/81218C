#include "turn.h"
#include "vex.h"

using namespace vex;

const double circumference = 12.5663706143592;
const double width = 17.8;
const double pi = 3.14159265358979;

void turn::turn1(float d, float s) {
  double leftTarget = left_front.position(turns) * circumference + width*2*pi/360*d;
  double rightTarget = right_front.position(turns) * circumference - width*2*pi/360*d;
  if(d >= 0) {
    while(left_front.position(turns) * circumference < leftTarget) {
      left_front.setVelocity(s, percent);
      left_back.setVelocity(s, percent);
    }
  }
  else{
    while(right_front.position(turns) * circumference < rightTarget) {
      right_front.setVelocity(s, percent);
      right_back.setVelocity(s, percent);
    }
  }
  left_front.setVelocity(0, percent);
  left_back.setVelocity(0, percent);
  right_front.setVelocity(0, percent);
  right_back.setVelocity(0, percent);
}

void turn::turn2(float d, float s) {
  double leftTarget = left_front.position(turns) * circumference + width*2*pi/360*d;
  double rightTarget = right_front.position(turns) * circumference - width*2*pi/360*d;
  if(d >= 0) {
    while(right_front.position(turns) * circumference > rightTarget) {
      right_front.setVelocity(-s, percent);
      right_back.setVelocity(-s, percent);
    }
  }
  else{
    while(left_front.position(turns) * circumference > leftTarget) {
      left_front.setVelocity(-s, percent);
      left_back.setVelocity(-s, percent);
    }
  }
  left_front.setVelocity(0, percent);
  left_back.setVelocity(0, percent);
  right_front.setVelocity(0, percent);
  right_back.setVelocity(0, percent);
}