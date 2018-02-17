#include "Robot.h"
#include "RobotConstants.h"
#include "Commands/AngledDistanceDrive.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<CougarOpticBoard> Robot::cob;

void Robot::RobotInit() {
	RobotMap::init();
	driveTrain.reset(new DriveTrain());
	SmartDashboard::PutData(driveTrain.get());


	//CougarOpticBoard::InitBoard();
	oi.reset(new OI());
	frc::DriverStation::GetInstance().GetGameSpecificMessage();

	Robot::cob->InitBoard();

	//autonomousCommand.reset(new AngledDistanceDrive(10 * FEET_TO_INCHES, 0.5, 5, 55.0));

	//nt::NetworkTable::SetClientMode();
	//nt::NetworkTable::SetIPAddress("10.6.23.2");
	//nt::NetworkTable::Initialize();
}

void Robot::RobotPeriodic() {

}

void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand.reset(new AutoSequence());
	if (autonomousCommand)
		autonomousCommand->Start();
	//DriverStation::ReportError(((std::unique_ptr<RobotImpl>)autonomousCommand)->switchOnRight() ? "Right" : "Left");
}

void Robot::AutonomousPeriodic() {
	//push time to cob
	Robot::cob->PushFMSTime(DriverStation::GetInstance().GetMatchTime());
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	if (autonomousCommand)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	//push time to cob
	Robot::cob->PushFMSTime(DriverStation::GetInstance().GetMatchTime());
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

