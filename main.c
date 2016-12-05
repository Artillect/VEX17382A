void liftForklift() {
	motor[port6] = 127;
	motor[port7] = 127;
	motor[port8] = -127;
	motor[port9] = -127;
}

void dropForklift() {
	motor[port6] = -127;
	motor[port7] = -127;
	motor[port8] = 127;
	motor[port9] = 127;
}

void shootCatapult() {
	motor[port10] = 127;
	motor[port10] = 127;
	motor[port1] = 127;
	motor[port1] = 127;
	wait1Msec(500);
}

task main(){
	// Declare Variables
	int start = 1;
	int heading;
	int angle;

  //Completely clear out any previous sensor readings by setting the port to "sensorNone"
  SensorType[in8] = sensorNone;
  wait1Msec(1000);
  //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
  SensorType[in8] = sensorGyro;
  wait1Msec(2000);

  heading = SensorValue[in8];
  angle = SensorValue[in8];
	// Makes the robot not do anything until 8D button is pressed
	while (start==0) {
		// Checks heading and outputs desired angle and current heading to debug stream
		heading = SensorValue[in8];
		writeDebugStreamLine("Desired Angle is : %d\n", angle);
		writeDebugStreamLine("Current Heading is is : %d\n", heading);
		if (vexRT[Btn8D] == 1) {
			start = 1;
		}
		if (vexRT[Btn8U] == 1) {
			start = 2;
		}
	}
	// Control Loop
	while (start == 1){
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


		while (vexRT[Btn6U] == 1) {
			liftForklift();
		}

		while (vexRT[Btn5U] == 1) {
			dropForklift();
		}
	}
	// Autonomous Choreo for Left Start ALL TIMINGS ARE VERY ARBITRARY, THEY REALLY NEED TO BE CHANGED ONCE TESTING BEGINS
	while (start == 2) {
		// Move forward a bit
		motor[port2] = -127;
		motor[port3] = 127;
		motor[port4] = 127;
		motor[port5] = -127;
		wait1Msec(1000);

		//Lift Forklift
		liftForklift();
		wait1Msec(1000);
		dropForklift();
		wait1Msec(1000);

		angle = 90; //Change for correct rotation later
		motor[port2] = (angle - SensorValue[in8])/3;
    motor[port3] = (angle - SensorValue[in8])/3;
		motor[port4] = (angle - SensorValue[in8])/3;
		motor[port5] = (angle - SensorValue[in8])/3;
		wait1Msec(2000);
		//Activate Catapult, remember to use splitters to output to catapult
		shootCatapult();

		// At end of this loop, set start = 1
	}
}
