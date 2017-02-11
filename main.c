#pragma config(Sensor, dgtl1,  solenoidRight,    sensorDigitalOut)
#pragma config(Sensor, dgtl2,  solenoidLeft,     sensorDigitalOut)

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// Controls robot movement.
// Forward is how much forward, right is how much right, yawPower is how much power to turn with
// Why the fk do you need do differnt powers and then add them, just use one lol -Ashish Shrestha
void move(int forward, int yawPower) {
	motor[port4] =   forward + yawPower;
	motor[port5] =   forward + yawPower;
	motor[port6] = - forward + yawPower;
	motor[port7] = - forward + yawPower;
}

// Controls the lift
void lift(int power) {
	motor[port1] = power; //Yes this is correct, don't touch it, it works just fine
	motor[port2] = -power;
	motor[port3] = -power;
	motor[port8] = power;
	motor[port9] = power;
	motor[port10] = power;
}

void pneumaticClaw(bool direction) {
	SensorValue[solenoidRight] = direction; // Goes in ports 1 and 2
	SensorValue[solenoidLeft] = direction;
}

// This does stuff before the autonomous or user control periods start, don't set motor powers during this period.
void pre_auton() {
  bStopTasksBetweenModes = true;
}

// This code controls the robot during the autonomous period of the competition.
task autonomous() {
	// robot is starting from the right, use bottom code when from the left
	// Drop forklift from locked position
	move(-127, 0);
	lift(63);
	wait1Msec(250);
	lift(-127);
	move(127, 0);
	wait1Msec(250);

	// Start movin
	pneumaticClaw(true);
	move(127, 0);
	lift(127);
	wait1Msec(1500);
	pneumaticClaw(false);
	wait1Msec(250);
	move(-127, 0);
	wait1Msec(250);
	lift(-127);
	wait1Msec(500);

	// Flip some stars (switch yaw signs around if starting on left)
	move(0, -127);
	wait1Msec(750);
	move(-127, 0);
	wait1Msec(250);
	move(0, -127);
	wait1Msec(250);
	lift(127);
	wait1Msec(1000);
	lift(-127);
	wait1Msec(500);
	move(0, 127);
	wait1Msec(2000);
	lift(127);
	wait1Msec(1000);
	lift(-127);
	wait1Msec(1000);

	// INCOMPLETE - Gets 3 farzone stars, either dump or get to favorable spot
	move(63, -63);
	wait1Msec(250);
	move(0, -127);
	wait1Msec(100);
	move(127, 0);
	wait1Msec(500);
	wait1Msec(250);
	move(63, 63);
	wait1Msec(500);
	pneumaticClaw(false);
	move(0,127);
	wait1Msec(500);




}
/*
task autonomous() {
	// robot is starting from the left, use bottom code when from the left

  // Drop forklift from locked position
	move(-127, 0);
	lift(63);
	wait1Msec(250);
	lift(-127);
	move(127, 0);
	wait1Msec(250);

	// Start move backwards
	pneumaticClaw(true);
	move(-127, 0);
	lift(63);
	wait1Msec(1500);
	lift(-127);
	wait1Msec(250);

	// Flip some stars (switch yaw to negative if starting on left)
	move(0, 127);
	wait1Msec(500);
	lift(127);
	wait1Msec(1000);
	lift(-127);
	wait1Msec(500);
	move(0, -127);
	wait1Msec(2000);
	lift(127);
	wait1Msec(1000);
	lift(-127);
	wait1Msec(1000);

	// INCOMPLETE - Gets 3 farzone stars, either dump or get to favorable spot
	move(63, 63);
	wait1Msec(250);
	move(0, 127);
	wait1Msec(100);
	move(127, 0);
	wait1Msec(500);
	wait1Msec(250);
	move(63, -63);
	wait1Msec(500);
	pneumaticClaw(false);
	move(0, 127);
	wait1Msec(500);




}
*/
// This controls the robot during the user control period of the competition.
task usercontrol() {

  while (true) {
		// Calls move with vertical movement controlled by Ch1, horizontal movement controlled by Ch2, and rotation controlled by Ch4 (scaled my 0.75 because it feels right)
		move(vexRT[Ch2], vexRT[Ch4] * 0.75);
		// Handles lift controls
		if (vexRT[Btn6U]) {
			lift(127);
		}
		else if (vexRT[Btn5U]) {
			lift(-127);
		}
		else {
			lift(0);
		}
		// Handles claw controls
		if (vexRT[Btn5D]) {
			pneumaticClaw(true);
		}
		if (vexRT[Btn6D]) {
			pneumaticClaw(false);
		}
  }
}
