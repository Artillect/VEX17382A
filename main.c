// Main Loop
task main()
{
	int start = 0;
	// Makes the robot not do anything until button is pressed
	while (start==0) {
		if (vexRT[Btn8D] == 1) {
			start = start + 1;
		}
	}
	// Control Loop
	while (start == 1){
		// Translates joystick control to motor actuation
		motor[port2] =   vexRT[Ch1] - vexRT[Ch2] + vexRT[Ch4] * 0.75;
		motor[port3] = - vexRT[Ch1] - vexRT[Ch2] + vexRT[Ch4] * 0.75;
		motor[port4] = - vexRT[Ch1] + vexRT[Ch2] + vexRT[Ch4] * 0.75;
		motor[port5] =   vexRT[Ch1] + vexRT[Ch2] + vexRT[Ch4] * 0.75;
	}
}
