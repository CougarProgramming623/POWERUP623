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
#include "../RobotMap.h"
#include "networktables/NetworkTable.h"
#include "../CougarOpticBoard.h"
#include "../Robot.h"

const static double kF = 0.0f;
const static double kToleranceDegrees = 0.1;

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveWithJoystick::DriveWithJoystick() :
		frc::Command(), frc::PIDOutput() {
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

}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {
	try {
		//Communicate w/navX-MXP via the MXP SPI Bus.
		// Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB
		// See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.

		RobotMap::ahrs->ZeroYaw();

	} catch (std::exception& ex) {
		std::string err_string = "Error instantiating navX-MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}
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
	//DriverStation::ReportError("PID enabled.");
}
double maxZAcel = 0.0;
double maxAcel = 0.0;
// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	XAxis = Robot::oi->getdriverJoystick()->GetRawAxis(0);
	YAxis = -Robot::oi->getdriverJoystick()->GetRawAxis(1);
	RotAxis = Robot::oi->getdriverJoystick()->GetRawAxis(2);

	double acrossAccel = sqrt(
			RobotMap::ahrs->GetWorldLinearAccelX() * RobotMap::ahrs->GetWorldLinearAccelX()
					+ RobotMap::ahrs->GetWorldLinearAccelY() * RobotMap::ahrs->GetWorldLinearAccelY());
	if (maxZAcel < RobotMap::ahrs->GetWorldLinearAccelZ())
		maxZAcel = RobotMap::ahrs->GetWorldLinearAccelZ();
	if (maxAcel < acrossAccel)
		maxAcel = acrossAccel;

	//if (RobotMap::ahrs->GetWorldLinearAccelZ() > 0.7 && acrossAccel < 0.15)
	//	DriverStation::ReportError("Bump!");
	std::stringstream str;
	str << "max across " << maxAcel;
	//DriverStation::ReportError(str.str());
	str.clear();
	str << "max up and down acel " << maxZAcel;
	//DriverStation::ReportError(str.str());
	/*
	 if(XAxis > 0.20 && XAxis < -0.20) {
	 XAxis = 0;
	 }

	 if(YAxis > 0.20 && YAxis < -0.20) {
	 YAxis = 0;
	 }

	 if(RotAxis > 0.20 && RotAxis < -0.20) {
	 RotAxis = 0;
	 }



	 if (RobotMap::ahrs->GetYaw() < 0) {
	 Robot::driveTrain->MecanumDrive(-XAxis, YAxis, RotAxis, RobotMap::ahrs->GetYaw());
	 } else {
	 Robot::driveTrain->MecanumDrive(XAxis, -YAxis, RotAxis, RobotMap::ahrs->GetYaw());
	 } */
	double push = sqrt(XAxis * XAxis + YAxis * YAxis);
	//Test Code:1/24
	if (abs(RotAxis) < 0.00125f && push > 0.1f) {
		turnController->Enable();
		Robot::driveTrain->MecanumDrive(XAxis, YAxis, rotateToAngleRate, -RobotMap::ahrs->GetYaw());
		//DriverStation::ReportError("not turning");
	} else {
		turnController->Disable();
		Robot::driveTrain->MecanumDrive(XAxis, YAxis, RotAxis, -RobotMap::ahrs->GetYaw());
		turnController->SetSetpoint(RobotMap::ahrs->GetYaw());
		//DriverStation::ReportError("turning");
	}
	//std::stringstream str;
	//str <<"Ticks " << RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0) - initEncPosition;
	//DriverStation::ReportError(str.str());
	double angle = RobotMap::ahrs->GetYaw();
	//frc::SmartDashboard::PutNumber("Angle", angle);
	//frc::SmartDashboard::PutNumber("EncPosition", RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0) - initEncPosition);

	Robot::cob->PushRotation(angle);
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
