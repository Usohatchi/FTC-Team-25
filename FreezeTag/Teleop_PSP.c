#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S3,     touchStop,      sensorTouch)
#pragma config(Sensor, S4,     touchGo,        sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     driveLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     driveRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

const ubyte PSPAddr = 0x02;
const tSensors PSPSensorPort = S2;        // Connect PSPNX sensor to this port!!
int Frozen;
#include "PSP-Nx-lib-ref.c"  //Include file for PSP controller command library


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{

  //
  // nNxtExitClicks = 3;                // Triple clicking EXIT button will terminate program
  //
  nI2CBytesReady[PSPSensorPort] = 0;

  //SensorType[SensorPort] = sensorI2CCustom9V;        // or perhaps use 'Lowspeed_9V_Custom0'??
  SensorType[PSPSensorPort] = sensorI2CMuxController;

  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


void allStop()
{
	motor[driveLeft] = 0;
	motor[driveRight] = 0;
}


task main()
{
  initializeRobot();

	psp currState;
  //waitForStart();   // wait for start of tele-op phase
	PSP_ReadButtonState(PSPSensorPort, PSPAddr, currState);

	while(true)
	{
		if (Frozen){
			nxtDisplayTextLine(4, "Frozen");
		} else if (!Frozen) {
			nxtDisplayTextLine(4, "Not Frozen");
		}

		if (SensorValue(touchGo)){
				Frozen = false;
		}	 else if (SensorValue(touchStop)){
				Frozen = true;
				allStop();
		}

		if (!Frozen){
			if (abs((int)currState.l_j_y)<10)
		   	{
		     	motor[driveLeft]=0;
		   	}
		   	else
		   	{
		     	motor[driveLeft]=(int)currState.l_j_y;
		   	}

		   	if (abs((int)currState.l_j_x)<10)
		  	{
		  		motor[driveRight] = 0;
		  	}
		  	else
		  	{
		  		motor[driveRight] = (int)currState.l_j_x;
		  	}
		}
	}
}
