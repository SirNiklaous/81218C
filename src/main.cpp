/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\knsv_.KANDULA-3                                  */
/*    Created:      Sat Jul 31 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// left_front           motor         1               
// left_back            motor         2               
// right_front          motor         3               
// right_back           motor         4               
// Controller1          controller                    
// Inertial20           inertial      20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "move.h"
#include "turn.h"

using namespace vex;
//global competition instance
competition Competition;


void pre_auton(void) 
{
  vexcodeInit();
  Brain.Screen.drawImageFromFile("field1.png", 0, 0);
  Brain.Screen.print("yello");
  left_front.setStopping(hold);
  left_front.setVelocity(0, percent);
  left_front.setMaxTorque(100, percent);
  left_back.setStopping(hold);
  left_back.setVelocity(0, percent);
  left_back.setMaxTorque(100, percent);
  right_front.setStopping(hold);
  right_front.setVelocity(0, percent);
  right_front.setMaxTorque(100, percent);
  right_back.setStopping(hold);
  right_back.setVelocity(0, percent);
  right_back.setMaxTorque(100, percent);
  left_front.spin(forward);
  left_back.spin(forward);
  right_front.spin(forward);
  right_back.spin(forward);
}
 
void autonomous(void) 
{
  move::moveBot(20,99);
  turn::turn1(90,50);
  move::moveBot(30,50);
  turn::turn2(90,60);
}

void usercontrol(void) 
{
  while(true) 
  {
    left_back.setStopping(coast);
    left_front.setStopping(coast);
    right_back.setStopping(coast);
    right_front.setStopping(coast);

    //Program for setting axis postition relative to controller and wheel
    left_front.setVelocity(Controller1.Axis3.position(percent), percent);
    left_back.setVelocity(Controller1.Axis3.position(percent), percent);
    right_front.setVelocity(Controller1.Axis2.position(percent), percent);
    right_back.setVelocity(Controller1.Axis2.position(percent), percent);

    vex::task::sleep(10);
  }
}
 
int main() 
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}
