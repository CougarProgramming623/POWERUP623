#include "AngledDistanceDrive.h"
#include <cmath>
#include "Math.h"

#define ROOT_2 1.41421356237

const static double kP = RobotMap::turnP;
const static double kI = RobotMap::turnI;
const static double kD = RobotMap::turnD;
const static double kF = 0.0;

const static double kToleranceDegrees = 0.1f;

#define PI 3.141592
#define ROTATE_FIX_SPEED 0.05

AngledDistanceDrive::AngledDistanceDrive(double time, double speed, double angle) :
		frc::Command() {
	// Use Requires() here to declare subsystem dependenciesactualSpeed
	// eg. Requires(Robot::chassis.get());
	m_speed = speed;
	m_time = time;
	m_angle = angle;
	m_timer = new Timer();
	rotateToAngleRate = 0.0;
	turnController = new PIDController(kP, kI, kD, kF, RobotMap::ahrs, this);
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void AngledDistanceDrive::Initialize() {
	SetTimeout(m_time + 0.5);
	m_timer = new Timer();
	m_timer->Start();

	turnController->SetInputRange(-180.0f, 180.0f);
	turnController->SetOutputRange(-1.0, 1.0);
	turnController->SetAbsoluteTolerance(kToleranceDegrees);
	turnController->SetContinuous(true);

	turnController->SetSetpoint(RobotMap::ahrs->GetAngle());
	turnController->Enable();
}

int AngledDistanceDrive::getPosition() {
	return RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0);
}

// Called repeatedly when this Command is scheduled to run
void AngledDistanceDrive::Execute() {
	double x = cos(m_angle * M_PI / 180) * m_speed;
	double y = sin(m_angle * M_PI / 180) * m_speed;
	Robot::driveTrain->MecanumDrive(x, y, 0, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool AngledDistanceDrive::IsFinished() {
	if (m_timer && m_timer->Get() > m_time) {
		return true;
	}
	return false;

}

// Called once after isFinished returns true
void AngledDistanceDrive::End() {
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
void AngledDistanceDrive::Interrupted() {

}

void AngledDistanceDrive::PIDWrite(double output) {
	rotateToAngleRate = output;
}
