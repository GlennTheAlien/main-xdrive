using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Left;
extern motor LeftSlave;
extern motor Right;
extern motor RightSlave;
extern motor IntakeLeft;
extern motor IntakeRight;
extern motor Roller;
extern motor Spitter;
extern controller Controller1;
extern controller Controller2;
extern encoder Encoder;
extern optical Low;
extern optical Mid;
extern optical High;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );