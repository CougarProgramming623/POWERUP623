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

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveWithJoystick::DriveWithJoystick(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	XAxis = 0;
	YAxis = 0;
	RotAxis = 0;

}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {
	try {
		             //Communicate w/navX-MXP via the MXP SPI Bus.
		            // Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB
		            // See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.

		            RobotMap::ahrs->ZeroYaw();

		        } catch (std::exception ex ) {
		            std::string err_string = "Error instantiating navX-MXP:  ";
		            err_string += ex.what();
		            DriverStation::ReportError(err_string.c_str());
		        }
	XAxis = 0;
	YAxis = 0;
	RotAxis = 0;
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	XAxis = Robot::oi->getdriverJoystick()->GetRawAxis(0);
	YAxis = -Robot::oi->getdriverJoystick()->GetRawAxis(1);
	RotAxis = Robot::oi->getdriverJoystick()->GetRawAxis(2);
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

	//Test Code:1/24
	Robot::driveTrain->MecanumDrive(XAxis, YAxis, RotAxis, RobotMap::ahrs->GetYaw());

	//Test for COB
	Robot::table.get()->PutNumber("/SmartDashboard/drive/navx/yaw", RotAxis);

	double angle = RobotMap::ahrs->GetYaw();
	frc::SmartDashboard::PutNumber("Angle", angle);
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
