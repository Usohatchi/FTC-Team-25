#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     irr_left,       sensorI2CCustom)
#pragma config(Sensor, S4,     irr_right,      sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C2_1,     driveRearRight, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     driveFrontRight, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     shoulder,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     driveFrontLeft, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     driveRearLeft, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    finger,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    brush,                tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_3,    arm,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    dockarm,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    centerDispenser,      tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    leftEye,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    rightEye,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define LSERVO_LEFT_SLANT 110
#define LSERVO_CENTER 145
#define RSERVO_CENTER 113
#define RSERVO_PERP   235

#include "../../lib/sensors/drivers/hitechnic-irseeker-v2.h"
#include "../../lib/drivetrain_andymark_defs.h"
#include "../../lib/drivetrain_square.h"
#include "../../lib/dead_reckon.h"
#include "../../lib/data_log.h"
#include "../../lib/ir_utils.h"

#define SWEEP_START 235
#define SWEEP_END   0
#define POS_1_START 0
#define POS_1_END   0
#define POS_2_START 0
#define POS_2_END   0


/*
 * Find the location on the servo that corresponds
 * to receiver segment 4, in both beacon position 1 and 2.
 */

task main()
{
    int val;
    int segment;

    initialize_receiver(irr_left, irr_right);

    servoChangeRate[leftEye] = 0;
    servo[leftEye] = SWEEP_START;
    servo[rightEye] = RSERVO_CENTER;
    wait1Msec(1000);

    playImmediateTone(60, 50);

    servoChangeRate[leftEye] = 1;
    val = ServoValue[leftEye];
    while (val > SWEEP_END) {
        segment = HTIRS2readACDir(irr_left);
        nxtDisplayTextLine(1, "Segment: %d", segment);
        val--;
        servo[leftEye] = val;
        wait1Msec(100);
    }

    while (true) {}
}
