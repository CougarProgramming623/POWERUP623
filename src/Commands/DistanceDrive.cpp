#include "DistanceDrive.h"
#include <iostream>

#define ROOT_2 1.41421356237

const static double kP = RobotMap::turnP;
const static double kI = RobotMap::turnI;
const static double kD = RobotMap::turnD;
const static double kF = 0.0;

const static double kToleranceDegrees = 2.0f;

#define PI 3.141592
#define ROTATE_FIX_SPEED 0.05
//the pitch of the bump
#define BUMP_PITCH_LIMIT 2
//the delay before we begin reading for the bump
#define BUMP_DELAY 2

static double maxPitch = 0;

/**
 * This command uses the encoders to drive a certain distance at a set speed.
 * This command will also stop when it detects a bump if the last parameter is true
 */
DistanceDrive::DistanceDrive(double distance, double speed, int timeout, bool strafe, bool bumpDetection) :
		frc::Command("DistanceDrive"), frc::PIDOutput() {
	// Use Requires() here to declare subsystem dependenciesactualSpeed
	// eg. Requires(Robot::chassis.get());
	m_distance = distance;
	m_ticks = (int) (distance * TICKS_PER_INCH);
	m_speed = speed;
	m_timeout = timeout;
	m_strafe = strafe;
	m_timer = new Timer();
	m_doBumpDetection = bumpDetection;
	rotateToAngleRate = 0.0;
	turnController = new PIDController(kP, kI, kD, kF, RobotMap::ahrs, this);
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void DistanceDrive::Initialize() {
	try {
		SetTimeout(m_timeout); //timeout for 10ms

		/* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
		/* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
		/* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */

		//RobotMap::ahrs->ZeroYaw();
	} catch (std::exception& ex) {
		std::string err_string = "Error instantiating navX-MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}

	//m_timer = new Timer();
	m_timer->Reset();
	m_timer->Start();

	turnController->SetInputRange(-180.0f, 180.0f);
	turnController->SetOutputRange(-1.0, 1.0);
	turnController->SetAbsoluteTolerance(kToleranceDegrees);
	turnController->SetContinuous(true);

	turnController->SetSetpoint(0.0f);
	turnController->Enable();

	initEncPosition = RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0);
}

int DistanceDrive::getPosition() {
	return RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0);
}

double DistanceDrive::getMaxTicks() {
	return m_ticks;
}

//checks for the bump, returns true if we hit it and we are passed the detection delay.
bool DistanceDrive::checkForBump() {
	/*
	 double acrossAccel = sqrt(
	 RobotMap::ahrs->GetWorldLinearAccelX() * RobotMap::ahrs->GetWorldLinearAccelX()
	 + RobotMap::ahrs->GetWorldLinearAccelY() * RobotMap::ahrs->GetWorldLinearAccelY());
	 DriverStation::ReportError("vertical acceleration: " + std::to_string(RobotMap::ahrs->GetWorldLinearAccelZ()));
	 return m_timer->Get() >= 2 && RobotMap::ahrs->GetWorldLinearAccelZ() > 0.7; //these values may need to be changed
	 */
	//DriverStation::ReportError("barometric pressure: " + std::to_string(RobotMap::ahrs->GetBarometricPressure()));
	if (maxPitch < RobotMap::ahrs->GetPitch())
		maxPitch = RobotMap::ahrs->GetPitch();
	//DriverStation::ReportError("pitch: " + std::to_string(maxPitch));
	return RobotMap::ahrs->GetPitch() >= BUMP_PITCH_LIMIT && m_timer->HasPeriodPassed(BUMP_DELAY);
}

// Called repeatedly when this Command is scheduled to run
// Calling this function will set power to the motors, and cause the robot to turn back to the initial angle if the turn manager
// says that we need to turn to correct the robot's heading.
void DistanceDrive::Execute() {
	double angle = RobotMap::ahrs->GetYaw();
	//std::cout << "Encoder " << getPosition() << std::endl;

	double coefficient = 1.0;

	if (m_distance < 0)
		coefficient *= -1.0;

	double actualSpeed = coefficient * m_speed;
	std::stringstream str;
	str << "percent done % " << (((double) getPosition() - (double) initEncPosition) / ((double) getMaxTicks() - (double) initEncPosition) * 100.0);
	//DriverStation::ReportError(str.str());
	//actualSpeed *= sqrt(
	//		1 - (((double) getPosition() - (double) initEncPosition) / ((double) getMaxTicks() - (double) initEncPosition)));
	if (m_strafe) {
		Robot::driveTrain->MecanumDrive(actualSpeed, 0, rotateToAngleRate, 0);
	} else {
		Robot::driveTrain->MecanumDrive(0, actualSpeed, rotateToAngleRate, 0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DistanceDrive::IsFinished() {
	if (m_doBumpDetection && checkForBump()) {
		DriverStation::ReportError("Detected bump. Stopping DDC.");
		return true;
	}
	if (m_timer && m_timer->Get() > m_timeout) {
		return true;
	}
	if (fabs(getPosition() - initEncPosition) >= fabs(getMaxTicks())) {
		DriverStation::ReportError("Distance Drove.");
		std::cout << "Distance Driven " << std::endl;
		return true;
	}
	return false;

}

// Called once after isFinished returns true
void DistanceDrive::End() {
	initEncPosition = getPosition();
	Robot::driveTrain->Stop();

	if (turnController) {
		turnController->Disable();
		delete turnController;
	}

	if (m_timer) {
		m_timer->Reset();
		delete m_timer;
	}

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DistanceDrive::Interrupted() {

}

void DistanceDrive::PIDWrite(double output) {
	rotateToAngleRate = output;
}
