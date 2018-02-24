#include "Robot.h"
#include "RobotConstants.h"
#include "Commands/AngledDistanceDrive.h"
#include "DriverStation.h"
#include "Commands/CubeIntakeCommand.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<CubeIntake> Robot::cubeIntake;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<CougarOpticBoard> Robot::cob;
std::shared_ptr<ButtonBoard> Robot::buttonBoard;

//Called when the driver presses enable. Usually called before the game start
void Robot::RobotInit() {
	std::stringstream str;
	str << "sizeof double " << sizeof(double);
	DriverStation::ReportError(str.str());
	RobotMap::init();
	driveTrain.reset(new DriveTrain());
	cubeIntake.reset(new CubeIntake());
	//SmartDashboard::PutData(driveTrain.get());
	buttonBoard.reset(new ButtonBoard(1));
	//CougarOpticBoard::InitBoard();
	oi.reset(new OI());
	//frc::DriverStation::GetInstance().GetGameSpecificMessage();

	Robot::cob->InitBoard();
	RobotMap::ahrs->ZeroYaw();

	//autonomousCommand.reset(new AngledDistanceDrive(10 * FEET_TO_INCHES, 0.5, 5, 55.0));

	//nt::NetworkTable::SetClientMode();
	//nt::NetworkTable::SetIPAddress("10.6.23.2");
	//nt::NetworkTable::Initialize();
}

void Robot::RobotPeriodic() {
	Robot::cob->PushEnabled(DriverStation::GetInstance().IsEnabled());
	Robot::cob->PushAutonomous(DriverStation::GetInstance().IsAutonomous());
	Robot::cob->PushTeleop(DriverStation::GetInstance().IsOperatorControl());
}

void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	//Create auto sequence here so that we have access to game time only information.
	//Otherwise we would be trying to read FMS at robot init which happens before game time.
	RobotMap::ahrs->ZeroYaw();
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
	CubeIntakeCommand::ResetSpikes();
	if (autonomousCommand)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	//push time to cob
	Robot::cob->PushFMSTime(DriverStation::GetInstance().GetMatchTime());
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

