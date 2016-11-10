// Main Loop
task main()
{
	// Control Loop
	while (1==1){
		// Translates joystick control to motor actuation
		motor[port2] =   vexRT[Ch1] - vexRT[Ch2] + vexRT[Ch4];
		motor[port3] = - vexRT[Ch1] - vexRT[Ch2] + vexRT[Ch4];
		motor[port4] = - vexRT[Ch1] + vexRT[Ch2] + vexRT[Ch4];
		motor[port5] =   vexRT[Ch1] + vexRT[Ch2] + vexRT[Ch4];
	}
}
