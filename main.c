// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// Controls robot movement.
// Forward is how much forward, right is how much right, yawPower is how much power to turn with
void move(int forward, int right, int yawPower) {
	motor[port4] = - forward + right + yawPower;
	motor[port5] = forward + right + yawPower;
	motor[port6] = forward - right + yawPower;
	motor[port7] = -forward - right + yawPower;
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

// This does stuff before the autonomous or user control periods start, don't set motor powers during this period.
void pre_auton()
{
  bStopTasksBetweenModes = true;

}

// This code controls the robot during the autonomous period of the competition.
task autonomous()
{
		// Drop forklift from locked position
		move(0, -127, 0);
		lift(63);
		wait1Msec(250);
		lift(-127);
		move(0, 127, 0);
		wait1Msec(250);

		// Move right for a bit
		move(127, 0, 0);
		wait1Msec(1900);

		// Stop Moving
		move(0, 0, 0);
		lift(0);
		wait1Msec(200);

		// Lift lift all the way
		lift(100);
		wait1Msec(1500);

		// Stop lift
		lift(0);
}

// This controls the robot during the user control period of the competition.
task usercontrol() {

  while (true) {
		//Calls move with vertical movement controlled by Ch1, horizontal movement controlled by Ch2, and rotation controlled by Ch4 (scaled my 0.75 because it feels right)
		move(vexRT[Ch1], vexRT[Ch2], vexRT[Ch4] * 0.75);

		// Controls the lift
		// Is a bit more streamlined than the next example, harder to read though
		// lift(127 * vexRT[Btn6U] - 127 * vexRT[Btn5U]);

		// I think this works alongside the rest of the code, it does have an unnecessary if check though...
		// This snippet of code is equivalent to the previous uncommented line.
		if (vexRT[Btn6U]) {
			lift(110);
		}
		else if (vexRT[Btn5U]) {
			lift(-110);
		}
		else {
			lift(0);
		}
		if (vexRT[Btn5D] && !(vexRT[Btn5U] || vexRT[Btn6U])) {
			lift(10);
		}
  }
}
