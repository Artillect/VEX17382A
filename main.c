// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// Controls robot movement.
// Forward is how much forward, right is how much right, yawRate is how fast to turn, time is how long.
void move(int forward, int right, int yawRate, float time) {
	motor[port2] = - forward + right + yawRate * 0.75;
	motor[port3] = forward + right + yawRate * 0.75;
	motor[port4] = forward - right + yawRate * 0.75;
	motor[port5] = -forward - right + yawRate * 0.75;
	wait1Msec(time);
}
// Stops all of the robot's motors
void stopMove() {
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
}

// Stops the lift
void stopLift() {
	motor[port6] = 0;
	motor[port7] = 0;
}

// Controls the lift
// If direction is true -> move forklift up
// If direction is false -> move forklift down
// Time controls how long this happens
// TODO: Make this less hacky, there's got to be a better way of doing this
void lift(bool direction, int power, int time) {
	if (direction) {
		motor[port6] = power;
		motor[port7] = -power;
		wait1Msec(time);
	}
	else {
		motor[port6] = -power;
		motor[port7] = power;
		wait1Msec(time);
	}
}

// This does stuff before the autonomous or user control periods start, don't set motor powers during this period.
void pre_auton()
{
	// Don't do anything before this line.
  bStopTasksBetweenModes = true;
	// Start doing things if you have to.

}

// This code controls the robot during the autonomous period of the competition.
task autonomous()
{
		// Drop forklift
		move(0, -127, 0, 0);
		lift(true, 63, 250);
		lift(false, 127, 0);
		move(0, 127, 0, 250);
		lift(true, 127, 750);
		move(0, 127, 0, 1900);
		stopMove();
		stopLift();
		lift(true, 127, 250);
		stopLift();
}

// This controls the robot during the user control period of the competition.
task usercontrol()
{
  // Don't do anything in this section, unless you want the robot to do something before joystick control starts.
  while (true)
  {
		// Translates joystick control to movement
		move(vexRT[Ch1], vexRT[Ch2], vexRT[Ch4], 0);

		// Controls the lift
		// TODO: Make less hacky, works but I don't like it.
		if (vexRT[Btn6U]) {
			lift(true, 127, 0);
		}
		if (vexRT[Btn5U]) {
			lift(false, 127, 0);
		}
  }
}
