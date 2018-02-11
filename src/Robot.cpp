#include "Robot.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<CougarOpticBoard> Robot::cob;

void Robot::RobotInit() {

	bool leftSwitch = true, leftScale = true;
	int start = 1;
	Location startLoc {1, 2 };

	RobotMap::init();
	driveTrain.reset(new DriveTrain());
	SmartDashboard::PutData(driveTrain.get());


	//CougarOpticBoard::InitBoard();
	oi.reset(new OI());

	Robot::cob->InitBoard();

	//autonomousCommand.reset(new DistanceDrive(5*12, 0.4, 10, false));
	autonomousCommand.reset(new AutoSequence());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);

	//nt::NetworkTable::SetClientMode();
	//nt::NetworkTable::SetIPAddress("10.6.23.2");
	//nt::NetworkTable::Initialize();
}

void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	if (autonomousCommand)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

