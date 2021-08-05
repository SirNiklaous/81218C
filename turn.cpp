#include "turn.h"
#include "vex.h"

using namespace vex;

const double circumference = 12.5663706143592;
const double width = 17.8;
const double pi = 3.14159265358979;


//turning left wheels forward [d = distance, s = speed]
void turn::turn1(float d, float s) 
{
  double leftTarget = left_front.position(turns) * circumference + width*2*pi/360*d;
  double rightTarget = right_front.position(turns) * circumference - width*2*pi/360*d;
  if(d >= 0) 
  {
    while(left_front.position(turns) * circumference < leftTarget) 
    {
      left_front.setVelocity(s, percent);
      left_back.setVelocity(s, percent);
    }
  }
  else
  {
    while(right_front.position(turns) * circumference < rightTarget) 
    {
      right_front.setVelocity(s, percent);
      right_back.setVelocity(s, percent);
    }
  }
  left_front.setVelocity(0, percent);
  left_back.setVelocity(0, percent);
  right_front.setVelocity(0, percent);
  right_back.setVelocity(0, percent);
}

//turning left wheels backwards
void turn::turn2(float d, float s) 
{
  double leftTarget = left_front.position(turns) * circumference + width*2*pi/360*d;
  double rightTarget = right_front.position(turns) * circumference - width*2*pi/360*d;
  if(d >= 0) 
  {
    while(right_front.position(turns) * circumference > rightTarget) 
    {
      right_front.setVelocity(-s, percent);
      right_back.setVelocity(-s, percent);
    }
  }
  else
  {
    while(left_front.position(turns) * circumference > leftTarget) 
    {
      left_front.setVelocity(-s, percent);
      left_back.setVelocity(-s, percent);
    }
  }
  left_front.setVelocity(0, percent);
  left_back.setVelocity(0, percent);
  right_front.setVelocity(0, percent);
  right_back.setVelocity(0, percent);
}

//turn using inertial and PD loop
void turn::turn3(double degrees) 
{
  if(Inertial20.installed())
  {
    int dt = 20;
    double target = degrees;
    double error = target - Inertial20.rotation();
    double kP = .52;
    double kD = .05;
    double prevError = error;
    while (fabs(error) > 1)
    {
      error = target - Inertial20.rotation();
      double derivative = (error - prevError)/dt;
      double percent = kP * error + kD * derivative;
      left_back.spin(directionType::fwd, percent, pct);
      left_front.spin(directionType::fwd, percent, pct);
      right_back.spin(directionType::rev, percent, pct);
      right_front.spin(directionType::rev, percent, pct);
      vex::task::sleep(dt);
      prevError = error;
    }
    left_back.stop();
    left_front.stop();
    right_back.stop();
    right_front.stop();
    left_back.resetRotation();
    left_front.resetRotation();
    right_back.resetRotation();
    right_front.resetRotation();
  }
  else
  {
    Brain.Screen.clearScreen();
    Brain.Screen.print("Inertial Sensor Not Detected");
  }
}

//turning using inertial
void turn::turn4(double d) 
{
  Inertial20.calibrate();

  while (Inertial20.isCalibrating()) 
  {
    wait(100, msec);
  }

  if(d > 0) 
  {
    left_back.spin(forward);
    left_front.spin(forward);
    right_back.spin(reverse);
    right_front.spin(reverse);

    waitUntil((Inertial20.rotation() >= d));
    left_back.stop();
    left_front.stop();
    right_back.stop();
    right_front.stop();
  } 
  else 
  {
    left_back.spin(reverse);
    left_front.spin(reverse);
    right_back.spin(forward);
    right_front.spin(forward);

    waitUntil((Inertial20.rotation() <= d));
    left_back.stop();
    left_front.stop();
    right_back.stop();
    right_front.stop();
  }
}