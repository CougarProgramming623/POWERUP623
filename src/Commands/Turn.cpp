#include "Turn.h"

const static double kF = 0.0f;
const static double kToleranceDegrees = 2.0;

Turn::Turn(double setpoint, double timeout) :
		frc::Command(), frc::PIDOutput() {
	Requires(Robot::driveTrain.get());
	m_angle = setpoint;
	m_timeout = timeout;
	m_timer = new Timer();
	rotateToAngleRate = 0.0;
	turnController = new PIDController(RobotMap::turnP, RobotMap::turnI, RobotMap::turnD, kF, RobotMap::ahrs, this);
}

void Turn::Initialize() {
	rotateToAngleRate = 0.0;
	turnController->SetInputRange(-180.0f, 180.0f);
	turnController->SetOutputRange(-1.0, 1.0);
	turnController->SetAbsoluteTolerance(kToleranceDegrees);
	turnController->SetContinuous(true);

	turnController->SetSetpoint(m_angle);
	turnController->Enable();
	m_timer->Start();
}

void Turn::Execute() {
	double angle = RobotMap::ahrs->GetYaw();
	Robot::driveTrain->MecanumDrive(0, 0, rotateToAngleRate, RobotMap::ahrs->GetYaw());

	frc::SmartDashboard::PutNumber("Current Angle", angle);
	frc::SmartDashboard::PutNumber("Current Rotation Rate", rotateToAngleRate);
	frc::SmartDashboard::PutNumber("P", RobotMap::turnP);
	frc::SmartDashboard::PutNumber("I", RobotMap::turnI);
	frc::SmartDashboard::PutNumber("D", RobotMap::turnD);

}

bool Turn::IsFinished() {
	return false;
}

void Turn::End() {
	m_timer->Stop();
	double time = m_timer->Get();
	frc::SmartDashboard::PutNumber("Time", time);
	m_timer->Reset();
	Robot::driveTrain->Stop();
	DriverStation::ReportError("Turn Done");
}

void Turn::Interrupted() {

}

void Turn::PIDWrite(double output) {
	rotateToAngleRate = output;
	rotateToAngleRate = minFRC(rotateToAngleRate, map(m_angle, 0.0, 90, 0.2, 1.0));
}

