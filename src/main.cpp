/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jakejin                                                   */
/*    Created:      Tue Feb 28 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// lb                   motor         1            
// lf                   motor         2             
// rb                   motor         9              
// rf                   motor         10              
         
           
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"

using namespace vex;

competition Competition;




const int THRESH     =  5;  // When joystick is within this, the motors will set to 0.  This is the deadzone
bool      WAS_RESET_SUCCESS = false; // Flag for if resetting worked
const int SCALE = 120;
const int DELAY_TIME =  10; // Delay time for loops (ms)

bool      IS_LAUNCHING = false;
bool      IS_SPINNING = false;

void set_tank(int l, int r) {
  lf.spin(fwd, l*SCALE, voltageUnits::mV);
  lb.spin(reverse, l*SCALE, voltageUnits::mV);
  rb.spin(fwd, r*SCALE, voltageUnits::mV);
  rf.spin(reverse, r*SCALE, voltageUnits::mV);
}

void brake_drive() {
  lf.setStopping(hold);
  lb.setStopping(hold);
  rf.setStopping(hold);
  rb.setStopping(hold);
}

void coast_drive() {
  lf.setStopping(coast);
  lb.setStopping(coast);
  rf.setStopping(coast);
  rb.setStopping(coast);
}







/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // CREATE FUNCTION TO RESET SENSORS
  // zero_sensors(); 
  WAS_RESET_SUCCESS=true;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void turn_90(int dir) {
  set_tank(80*dir, -80*dir);
  wait(400, msec);
  set_tank(0, 0);
}

void autonomous(void) {}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void trigger_launch(){
  if (IS_LAUNCHING){
    IS_LAUNCHING = false;
  }
  else{
    IS_LAUNCHING = true;
  }
}
void trigger_spin(){
    if (IS_SPINNING){
    IS_SPINNING = false;
  }
  else{
    IS_SPINNING = true;
  }
}

void usercontrol(void) {

  int intake_conveyor_speed = 0;

    //checks if pre_auton ran and if did not run pre_auto
  while(WAS_RESET_SUCCESS == false){
    wait(10, msec);
  }

  coast_drive();

  while (1){
    // int l_joy = abs(Controller1.Axis3.value())>THRESH ? Controller1.Axis3.value() : 0;
    // int r_joy = abs(Controller1.Axis2.value())>THRESH ? Controller1.Axis2.value() : 0;
    // set_tank(l_joy, r_joy); 

    int forward = Controller1.Axis3.position(vex::percent);
    int sideways = Controller1.Axis4.position(vex::percent);
    int turn = -Controller1.Axis1.position(vex::percent);

    rf.spin(reverse, forward - sideways + turn, vex::percent);
    lf.spin(fwd,  forward + sideways - turn, vex::percent);
    rb.spin(fwd,  forward + sideways + turn, vex::percent);
    lb.spin(reverse,   forward - sideways - turn, vex::percent);


    if (abs(Controller1.Axis3.position(vex::percent))>THRESH){
      conveyor.spin(fwd, -120, vex::percent);
    }
    else if (Controller1.ButtonR1.pressing()) {
      conveyor.spin(fwd, -120, vex::percent);
    }
    else if (Controller1.ButtonR2.pressing()) {
      conveyor.spin(fwd, 120, vex::percent);
    }
    else{
      conveyor.stop();
    }
    
    int LETSGOOOO = 1;
    if (1 == LETSGOOOO) {
      true;
    }
    
    Brain.Screen.print("Conveyor power");
    Brain.Screen.clearLine(2);
    Brain.Screen.print(conveyor.power());
    
    Controller1.ButtonL2.pressed(trigger_spin);
    if (IS_SPINNING){
      spinner.spin(fwd, -120, vex::percent);
    }
    else{
      spinner.stop();
    }

    Controller1.ButtonL1.pressed(trigger_launch);
    if (IS_LAUNCHING){
      launcher.spin(fwd, -120, vex::percent);
    }
    else{
      launcher.stop();
    }
  



    
    


    wait(DELAY_TIME, msec); // Don't hog the CPU!

    Brain.Screen.clearScreen();
  }

}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  //Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}