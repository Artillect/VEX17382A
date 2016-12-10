// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

int heading;
int angle;

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
	// Declare Variables


  //Completely clear out any previous sensor readings by setting the port to "sensorNone"
  SensorType[in8] = sensorNone;
  wait1Msec(1000);
  //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
  SensorType[in8] = sensorGyro;
  wait1Msec(2000);

  heading = SensorValue[in8];
  angle = SensorValue[in8];
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

task autonomous()
{
		angle = SensorValue[in8];
		// Drop forklift
		motor[port2] = -127;
		motor[port3] = -127;
		motor[port4] = 127;
		motor[port5] = 127;
				motor[port6] = 63;
		motor[port7] = -63;
		wait1Msec(250);

		motor[port6] = -127;
		motor[port7] = 127;
		motor[port2] = 127;
		motor[port3] = 127;
		motor[port4] = -127;
		motor[port5] = -127;

		wait1Msec(250);
		motor[port6] = -0;
		motor[port7] = 0;
		wait1Msec(250);
		//Move Back
		motor[port2] = -127;
		motor[port3] = -127;
		motor[port4] = 127;
		motor[port5] = 127;
		wait1Msec(500);
		motor[port6] = 31;
		motor[port7] = -31;
		motor[port2] = 127;
		motor[port3] = 127;
		motor[port4] = -127;
		motor[port5] = -127;
		wait1Msec(1000);
		motor[port6] = 50;
		motor[port7] = -50;
		motor[port2] = -127;
		motor[port3] = 127;
		motor[port4] = 127;
		motor[port5] = -127;
		wait1Msec(1900);

		motor[port6] = 0;
		motor[port7] = 0;
		motor[port2] = -127;
 		motor[port3] = -127;
		motor[port4] = -127;
		motor[port5] = -127;
		wait1Msec(450);
		motor[port2] = -127;
		motor[port3] = -127;
		motor[port4] = 127;
		motor[port5] = 127;
		motor[port6] = 127;
		motor[port7] = -127;
		wait1Msec(1000);

		motor[port6] = 0;
		motor[port7] = 0;
		motor[port2] = 0;
		motor[port3] = 0;
		motor[port4] = 0;
		motor[port5] = 0;
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

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // Remove this function call once you have "real" code.
    		// Checks heading and outputs desired angle and current heading to debug stream
		heading = SensorValue[in8];
		writeDebugStreamLine("Desired Angle is : %d\n", angle);
		writeDebugStreamLine("Current Heading is : %d\n", heading);

		//Rotation and angle-setting code
		while (abs(vexRT[Ch4]) > 0) {
			angle = SensorValue[in8];
			heading = SensorValue[in8];
			motor[port2] =   -vexRT[Ch1] + vexRT[Ch2] + vexRT[Ch4] * 0.75;
			motor[port3] =  vexRT[Ch1] + vexRT[Ch2] + vexRT[Ch4] * 0.75;
			motor[port4] =  vexRT[Ch1] - vexRT[Ch2] + vexRT[Ch4] * 0.75;
			motor[port5] =   -vexRT[Ch1] - vexRT[Ch2] + vexRT[Ch4] * 0.75;
		}
		// Translates joystick control to motor actuation
		// Currently the most basic implementation of course correction, works well, overcorrects after yawing
		motor[port2] =   -vexRT[Ch1] + vexRT[Ch2] + (angle - heading)/3;
    motor[port3] =  vexRT[Ch1] + vexRT[Ch2] + (angle - heading)/3;
		motor[port4] =  vexRT[Ch1] - vexRT[Ch2] + (angle - heading)/3;
		motor[port5] =   - vexRT[Ch1] - vexRT[Ch2] + (angle - heading)/3;

		motor[port6] = 127*vexRT[Btn6U] -127*vexRT[Btn5U];
		motor[port7] = -127*vexRT[Btn6U] +127*vexRT[Btn5U];
		motor[port8] = 127*vexRT[Btn6D];
		motor[port8] = 127*vexRT[Btn6D];
		motor[port9] = -127*vexRT[Btn6D];
		motor[port10] = -127*vexRT[Btn6D];

  }
}
