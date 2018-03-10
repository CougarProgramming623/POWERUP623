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
	SetTimeout(m_time);
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
	double x = cos((m_angle + 45) * (M_PI / 180)) * m_speed;
	double y = sin((m_angle + 45) * (M_PI / 180)) * m_speed;

	//RobotMap::driveTrainleftFront->Set(y);
	//RobotMap::driveTrainrightBack->Set(y);

	//RobotMap::driveTrainleftBack->Set(x);
	//RobotMap::driveTrainrightFront->Set(x);
	Robot::driveTrain->PolarDrive(m_speed, m_angle, 0);
	DriverStation::ReportError("Doing Angled Distance:  (" + std::to_string(m_speed) + " , " + std::to_string(m_angle) + ")");
	//DriverStation::ReportError(std::to_string(rotateToAngleRate));
}

// Make this return true when this Command no longer needs to run execute()
bool AngledDistanceDrive::IsFinished() {
	return IsTimedOut();
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
	DriverStation::ReportError("ADD Interrupted");
}

void AngledDistanceDrive::PIDWrite(double output) {
	rotateToAngleRate = output;
}
