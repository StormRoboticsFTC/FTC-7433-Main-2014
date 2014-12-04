#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontRightMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backLeftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     backRightMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     frontLiftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     backLiftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     intakeMotor,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    clawServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    gateServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define COMPETITION

#include "JoystickDriver.c"
#include "claw.h"
#include "claw.c"
#include "drive.h"
#include "drive.c"
#include "lift.h" //Import other files called in this one
#include "lift.c"
#include "intake.h"
#include "intake.c"
#include "gate.h"
#include "gate.c"
#include "gyro.h"
GyroSys gyr;
#include "gyro.c"

DriveSys drive;
LiftSys lift;
IntakeSys intake; //Control variable declaration
GateSys gate;
ClawSys claw;

void initializeRobot(){ //Robot initiliazation code
	drive.backLeft = backLeftMotor;
	drive.backRight = backRightMotor;
	drive.frontRight = frontRightMotor; //Control variable declaration
	drive.frontLeft = frontLeftMotor; //Declare motor control variables
	gate.gate = gateServo;
	lift.frontLift = frontLiftMotor;
	lift.backLift = backLiftMotor;
	intake.intake = intakeMotor;
	gyr.gyroscope = gyroSensor;
	claw.claw = clawServo;

	return;
}

task updateGyroSys(){

	updateDriveSys(drive, 100, 100);

	while(true) {
		wait1Msec(50);
		gyr.gyroscopeValue = SensorValue[S4]/20.;

		if (gyr.gyroscopeValue > 1) {
			while (gyr.gyroscopeValue > 1) {
				updateDriveSys(drive, -50, 50);
			}
		}
		else if (gyr.gyroscope < -1) {
			while (gyr.gyroscope < -1) {
				updateDriveSys(drive, 50, -50);
			}
		}

		updateDriveSys(drive, 100, 100);
	}
}

task turnLeft(){
	while(true) {
		wait1Msec(50);
		gyr.gyroscopeValue = SensorValue[S4]/20.;

		if (gyr.gyroscopeValue > 25 && gyr.gyroscopeValue < 50) {
			wait1Msec(1000);
			updateDriveSys(drive, 0, 70);
		}
	}
}

task turnRight(){
	while(true) {
		wait1Msec(50);
		gyr.gyroscopeValue = SensorValue[S4]/20.;

		if (gyr.gyroscopeValue > 25 && gyr.gyroscopeValue < 50) {
			wait1Msec(1000);
			updateDriveSys(drive, 70, 0);
		}
	}
}

task main() {

	initializeRobot(); //Inits robot

	#ifdef COMPETITION
	waitForStart(); //Waits for start
	#endif

	updateDriveSys (drive, -100, -100);
	wait1Msec(6000);
	updateDriveSys (drive, -100, 0);
	wait1Msec(3000);
	updateDriveSys (drive, -100, -100);
	wait1Msec(8000);
	updateDriveSys (drive, 0, 0);

//	startTask(updateGyroSys);

}
