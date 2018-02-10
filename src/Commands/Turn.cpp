#include "Turn.h"

const static double kF = 0.0f;
const static double kToleranceDegrees = 0.5;

Turn::Turn(double setpoint) :
		frc::Command() {
	Requires(Robot::driveTrain.get());
	m_angle = setpoint;
	m_timer = new Timer();
	rotateToAngleRate = 0.0;
	turnController = new PIDController(RobotMap::turnP, RobotMap::turnI, RobotMap::turnD, kF, RobotMap::ahrs, this);
}

void Turn::Initialize() {
	rotateToAngleRate = 0.0;
	frc::DriverStation::ReportError("Speed done");
	try {
		SetTimeout(10);
		RobotMap::ahrs->ZeroYaw();

		DriverStation::ReportError("Zeroed");

	} catch (std::exception& ex) {
		std::string err_string = "Error instantiating navX-MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}

	DriverStation::ReportError("AHRS Initialized");
	turnController->SetInputRange(-180.0f, 180.0f);
	turnController->SetOutputRange(-1.0, 1.0);
	turnController->SetAbsoluteTolerance(kToleranceDegrees);
	turnController->SetContinuous(true);

	turnController->SetSetpoint(m_angle);
	turnController->Enable();
	DriverStation::ReportError("PID enabled.");
	m_timer->Start();
	frc::DriverStation::ReportError("Turn initialized");
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
	if (turnController->OnTarget()) {
		return true;
	} else {
		std::cout << m_timer->Get() << std::endl;
		return m_timer->Get() > 5;
	}
}

void Turn::End() {
	m_timer->Stop();
	double time = m_timer->Get();
	frc::SmartDashboard::PutNumber("Time", time);
	m_timer->Reset();
	Robot::driveTrain->Stop();
	frc::DriverStation::ReportError("Turn Complete");
}

void Turn::Interrupted() {

}

void Turn::PIDWrite(double output) {
	rotateToAngleRate = output;
	rotateToAngleRate = minFRC(rotateToAngleRate, map(m_angle, 0.0, 90, 0.2, 1.0));
}





