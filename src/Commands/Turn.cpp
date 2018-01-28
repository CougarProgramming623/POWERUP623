#include "Turn.h"
#include "AHRS.h"
#include "../RobotMap.h"

	const static double kP = 0.075;
	const static double kI = 0.04;
	const static double kD = 0.026;
	const static double kF = 0.0;
	const static double kToleranceDegrees = 2.0;

Turn::Turn(double setpoint) : frc::Command() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveTrain.get());
	m_angle = setpoint;
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void Turn::Initialize() {
	rotateToAngleRate = 0.0;
	try {
			/* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
			/* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
			/* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */

			RobotMap::ahrs->ZeroYaw();
			//initialAngle = RobotMap::ahrs->GetYaw();

			//DriverStation::ReportError("First time:"+std::to_string(initialAngle)+" "+std::to_string(m_angle));

		} catch (std::exception ex) {
			std::string err_string = "Error instantiating navX-MXP:  ";
			err_string += ex.what();
			//DriverStation::ReportError(err_string.c_str());
		}

		turnController = new PIDController(kP, kI, kD, kF, RobotMap::ahrs, this);
		turnController->SetInputRange(-180.0f, 180.0f);
		turnController->SetOutputRange(-1.0, 1.0);
		turnController->SetAbsoluteTolerance(kToleranceDegrees);
		turnController->SetContinuous(true);

		turnController->SetSetpoint(m_angle);
		m_timer->Start();
		frc::DriverStation::ReportError("Turn initialized");
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
	double angle = RobotMap::ahrs->GetYaw();
	double currentRotationRate = rotateToAngleRate;

	Robot::driveTrain->MecanumDrive(0, 0, currentRotationRate, RobotMap::ahrs->GetYaw());

	frc::SmartDashboard::PutNumber("Current Angle", angle);
	frc::SmartDashboard::PutNumber("Current Rotation Rate", currentRotationRate);
	frc::SmartDashboard::PutNumber("P", kP);
	frc::SmartDashboard::PutNumber("I", kI);
	frc::SmartDashboard::PutNumber("D", kD);

}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	if (turnController->OnTarget() == true) {
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void Turn::End() {
	m_timer->Stop();
	double time = m_timer->Get();
	frc::SmartDashboard::PutNumber("Time", time);
	m_timer->Reset();
	Robot::driveTrain->MecanumDrive(0,0,0,0);
	frc::DriverStation::ReportError("Turn Complete");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {

}

void Turn::PIDWrite(double output) {
	rotateToAngleRate = output;
}
