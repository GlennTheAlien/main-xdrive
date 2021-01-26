/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left                 motor         1
// LeftSlave            motor         2
// Right                motor         3
// RightSlave           motor         4
// IntakeLeft           motor         5
// IntakeRight          motor         6
// Roller               motor         7
// Spitter              motor         8
// Controller1          controller
// Controller2          controller
// EyeHigh              optical       10
// EyeMid               optical       9
// EyeLow               optical       11
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

/*---------------------------------------------------------------------------*/
/*                          Functions for Autonomous/Shortcuts               */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void clearEncoders(void) {
  Brain.Screen.clearScreen();
  Left.resetRotation();
  LeftSlave.resetRotation();
  Right.resetRotation();
  RightSlave.resetRotation();
  IntakeLeft.resetRotation();
  IntakeRight.resetRotation();
  Roller.resetRotation();
  Spitter.resetRotation();
}

class Base {
  double list[4];
  double a3pos;
  double a4pos;
  double a2pos;

public:
  Base() {
    for (int i = 0; i < 4; i++)
      list[i] = 0;
    a3pos = 0;
    a4pos = 0;
    a2pos = 0;
  }
  void setTranslation(double degrees, double scale) {
    double radians = degrees * M_PI / 180;

    a3pos = sin(radians) * scale;
    a4pos = cos(radians) * scale;

    list[0] = (a3pos + a4pos);
    list[1] = (a3pos - a4pos);
    list[2] = (-a3pos + a4pos);
    list[3] = (-a3pos - a4pos);

    _setVelocity();
  }
  void setTurns(double scale) {
    a2pos = scale;

    list[0] = (a2pos);
    list[1] = (a2pos);
    list[2] = (a2pos);
    list[3] = (a2pos);

    _setVelocity();
  }
  void rotate(double rotations) {}
  void _setVelocity() {
    Left.setVelocity(list[0], percent);
    LeftSlave.setVelocity(list[1], percent);
    Right.setVelocity(list[2], percent);
    RightSlave.setVelocity(list[3], percent);
  }
  void runBase(bool run) {
    if (run) {
      Left.spin(forward);
      LeftSlave.spin(forward);
      Right.spin(forward);
      RightSlave.spin(forward);
    } else {
      Left.stop(brake);
      LeftSlave.stop(brake);
      Right.stop(brake);
      RightSlave.stop(brake);
    }
  }
};

void Intake(bool b) {
  if (b) {
    IntakeLeft.spin(reverse);
    IntakeRight.spin(reverse);
  } else {
    IntakeLeft.spin(forward);
    IntakeRight.spin(forward);
  }
}
void IntakeStop() {
  IntakeLeft.stop();
  IntakeRight.stop();
}

// define your global instances of motors and other devices here

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

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

int highConstant = 0;
int lowConstant = 0;

void callback1(void) {
  highConstant--;
  wait(50, msec);
}

void callback2(void) {
  lowConstant--;
  wait(50, msec);
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

void autonomous(void) {
  clearEncoders();
  Base b;
  EyeHigh.objectLost(callback1);
  EyeLow.objectDetected(callback2);

  Roller.setVelocity(100, percent);
  Spitter.setVelocity(100, percent);
  IntakeLeft.setVelocity(100, percent);
  IntakeRight.setVelocity(100, percent);

  
  b.setTranslation(0, 20);
  b.runBase(true);
  wait(1150, msec);
  b.runBase(false);

  lowConstant = 2;
  Intake(true);
  Spitter.spin(forward);
  wait(1300, msec);

  b.setTranslation(90, 50);
  b.runBase(true);
  wait(500, msec);
  b.runBase(false);

  Roller.spin(forward);

  highConstant = 2;
  while (highConstant > 0) {
    wait(20, msec);
  }

  wait(150, msec);
  Spitter.stop();

  while (lowConstant > 0) {
    wait(20, msec);
  }

  Roller.stop();
  IntakeStop();

  b.setTranslation(-90, 50);
  b.runBase(true);
  wait(750, msec);
  b.runBase(false);
  wait(100, msec);

  Intake(false);
  Roller.spin(reverse);
  wait(100, msec);
  Roller.stop();
  wait(600, msec);
  IntakeStop();

  b.setTurns(-50);
  b.runBase(true);
  wait(230, msec);
  b.runBase(false);

  b.setTranslation(180, 30);
  b.runBase(true);
  wait(2500, msec);
  b.runBase(false);
  wait(100, msec);

  b.setTranslation(90, 40);
  b.runBase(true);
  wait(750, msec);
  b.runBase(false);

  Roller.spin(forward);
  Spitter.spin(forward);

  highConstant=1;
  while (highConstant > 0) {
    wait(20, msec);
  }
  
  wait(150, msec);
  Roller.stop();
  Spitter.stop();

  b.setTranslation(-75, 60);
  b.runBase(true);
  wait(1500, msec);
  b.runBase(false);
  
  b.setTurns(50);
  b.runBase(true);
  wait(1200,msec);
  b.runBase(false);

  b.setTranslation(0,50);
  b.runBase(true);
  wait(1000,msec);
  b.runBase(false);
  
  b.setTranslation(190,50);
  b.runBase(true);
  wait(1300,msec);
  b.runBase(false);

  /*
  b.setTranslation(0, 20);
  b.runBase(true);
  wait(1150, msec);
  b.runBase(false);

  lowConstant = 2;
  Intake(true);
  Spitter.spin(forward);
  wait(1500, msec);

  b.setTranslation(90, 50);
  b.runBase(true);
  wait(500, msec);
  b.runBase(false);

  Roller.spin(forward);

  highConstant = 3;
  while (highConstant > 0) {
    wait(20, msec);
  }

  wait(150, msec);
  Spitter.stop();

  while (lowConstant > 0) {
    wait(20, msec);
  }

  Roller.stop();
  IntakeStop();

  b.setTranslation(-90, 50);
  b.runBase(true);
  wait(1200, msec);
  b.runBase(false);
  wait(100, msec);

  Intake(false);
  Roller.spin(reverse);
  wait(800, msec);
  IntakeStop();
  Roller.stop();

  b.setTurns(50);
  b.runBase(true);
  wait(850, msec);
  b.runBase(false);

  wait(100, msec);

  lowConstant = 1;
  Intake(true);

  b.setTranslation(90, 30);
  b.runBase(true);
  wait(1450, msec);
  b.runBase(false);

  Roller.spin(forward);

  while (lowConstant > 0) {
    wait(20, msec);
  }

  IntakeStop();
  Roller.stop();

  b.setTranslation(0, 50);
  b.runBase(true);
  wait(1350, msec);
  b.runBase(false);

  wait(50, msec);

  b.setTranslation(225, 50);
  b.runBase(true);
  wait(800, msec);
  b.runBase(false);
  */
  /*
  Roller.spin(reverse);
  Intake(false);
  wait(2000, msec);
  Roller.stop();
  IntakeStop();

  b.setTranslation(-90, 50);
  b.runBase(true);
  wait(500, msec);
  b.runBase(false);
  */
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  bool SpitterStop = true;
  bool RollerStop = true;
  bool IntakeStop = true;

  double list[4];

  double a3pos;
  double a4pos;
  double a1pos;

  int max;
  double maxvalue;
  double ratio;

  Spitter.setVelocity(100, percent);
  Roller.setVelocity(100, percent);
  IntakeLeft.setVelocity(100, percent);
  IntakeRight.setVelocity(100, percent);

  // User control code here, inside the loop
  while (true) {
    for (int i = 0; i < 4; i++)
      list[i] = 0;

    a3pos = Controller1.Axis3.position();
    a4pos = Controller1.Axis4.position();
    // a2pos = Controller1.Axis2.position();
    a1pos = Controller1.Axis1.position();

    list[0] += (a3pos + a4pos + a1pos);
    list[1] += (a3pos - a4pos + a1pos);
    list[2] += (-a3pos + a4pos + a1pos);
    list[3] += (-a3pos - a4pos + a1pos);

    // finds the max value (absolute) of the wheels
    max = 0;
    maxvalue = fabs(list[0]);
    for (int i = 1; i < 4; i++) {
      if (fabs(list[i]) > maxvalue)
        max = i;
    }

    // scales down the values so the ratios of the values stay the same
    if (maxvalue > 100) {
      ratio = 100 / maxvalue;
      for (int i = 0; i < 4; i++)
        list[i] *= ratio;
    }

    // scale the speed
    for (int i = 0; i < 4; i++)
      list[i] *= 0.8;

    if (list[0] != 0)
      Left.spin(vex::directionType::fwd, list[0], vex::velocityUnits::pct);
    else
      Left.stop();
    if (list[1] != 0)
      LeftSlave.spin(vex::directionType::fwd, list[1], vex::velocityUnits::pct);
    else
      LeftSlave.stop();
    if (list[2] != 0)
      Right.spin(vex::directionType::fwd, list[2], vex::velocityUnits::pct);
    else
      Right.stop();
    if (list[3] != 0)
      RightSlave.spin(vex::directionType::fwd, list[3],
                      vex::velocityUnits::pct);
    else
      RightSlave.stop();

    // Spitter
    if (Controller1.ButtonL1.pressing()) {
      Spitter.spin(forward);
      SpitterStop = false;
    } else if (Controller1.ButtonL2.pressing()) {
      Spitter.spin(reverse);
      SpitterStop = false;
    } else if (!SpitterStop) {
      Spitter.stop();
      SpitterStop = true;
    }

    // Roller
    if (Controller1.ButtonR1.pressing()) {
      Roller.spin(forward);
      RollerStop = false;
    } else if (Controller1.ButtonR2.pressing()) {
      Roller.spin(reverse);
      RollerStop = false;
    } else if (!RollerStop) {
      Roller.stop();
      RollerStop = true;
    }

    // Intake
    if (Controller2.ButtonR1.pressing()) {
      IntakeLeft.spin(forward);
      IntakeRight.spin(forward);
      IntakeStop = false;
    } else if (Controller2.ButtonR2.pressing()) {
      IntakeLeft.spin(reverse);
      IntakeRight.spin(reverse);
      IntakeStop = false;
    } else if (!IntakeStop) {
      IntakeLeft.stop();
      IntakeRight.stop();
      IntakeStop = true;
    }

    // Run Autonomous
    if (Controller1.ButtonB.pressing()) {
      autonomous();
      task::sleep(300);
    }

    wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}