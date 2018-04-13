// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "DriveWithJoystick.h"
#include "ahrs.h"
#include "../../RobotMap.h"
#include "networktables/NetworkTable.h"
#include "../../CougarOpticBoard.h"
#include "../../Robot.h"
#include "Math.h"

const static double kF = 0.0f;
const static double kToleranceDegrees = 0.5;

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveWithJoystick::DriveWithJoystick() :
		frc::Command("DriveWithJoystick"), frc::PIDOutput() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(Robot::chassis.get());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	XAxis = 0;
	YAxis = 0;
	RotAxis = 0;
	rotateToAngleRate = 0.0;
	turnController = new PIDController(RobotMap::turnP, RobotMap::turnI, RobotMap::turnD, kF, RobotMap::ahrs, this);
	maxSpeed = 0; //change this

}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {
	XAxis = 0;
	YAxis = 0;
	RotAxis = 0;
	initEncPosition = RobotMap::driveTrainrightFront->GetSelectedSensorPosition(0);
	rotateToAngleRate = 0;
	turnController->SetInputRange(-180.0f, 180.0f);
	turnController->SetOutputRange(-1.0, 1.0);
	turnController->SetAbsoluteTolerance(kToleranceDegrees);
	turnController->SetContinuous(true);
	turnController->SetSetpoint(RobotMap::ahrs->GetYaw());
	turnController->Enable();
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	XAxis = Robot::GetOI()->GetDriverJoystick()->GetRawAxis(0);
	YAxis = -Robot::GetOI()->GetDriverJoystick()->GetRawAxis(1);
	RotAxis = Robot::GetOI()->GetDriverJoystick()->GetRawAxis(2);

	turnController->Disable();
	Robot::driveTrain->MecanumDrive(XAxis, YAxis, RotAxis, -RobotMap::ahrs->GetYaw());
	//set the maximum speed if necessary

	SmartDashboard::PutNumber("Encoder", RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0));
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {

}

void DriveWithJoystick::PIDWrite(double output) {
	rotateToAngleRate = output;
}
