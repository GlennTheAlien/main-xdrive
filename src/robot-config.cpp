#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Left = motor(PORT1, ratio18_1, false);
motor LeftSlave = motor(PORT2, ratio18_1, false);
motor Right = motor(PORT3, ratio18_1, false);
motor RightSlave = motor(PORT4, ratio18_1, false);
motor IntakeLeft = motor(PORT5, ratio18_1, false);
motor IntakeRight = motor(PORT6, ratio18_1, true);
motor Roller = motor(PORT7, ratio6_1, true);
motor Spitter = motor(PORT8, ratio18_1, false);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
optical EyeHigh = optical(PORT10);
optical EyeMid = optical(PORT9);
optical EyeLow = optical(PORT11);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}