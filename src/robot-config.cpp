#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor lf = motor(PORT1, ratio18_1, true);
motor lb = motor(PORT2, ratio18_1, true);
motor rf = motor(PORT9, ratio18_1, true);
motor rb = motor(PORT10, ratio18_1, true);

motor conveyor = motor(PORT18, ratio18_1, true);
motor spinner = motor(PORT17, ratio18_1, true);
motor launcher = motor(PORT20, ratio18_1, true);

controller Controller1 = controller(primary);

bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
 
void vexcodeInit( void ) {
  // nothing
}