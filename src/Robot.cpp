#include "Robot.h"
#include "RobotConstants.h"
#include "Commands/Drive/AngledDistanceDrive.h"
#include "DriverStation.h"
#include "Commands/TeleOp/CubeIntakeCommand.h"


std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<CubeIntake> Robot::cubeIntake;
std::shared_ptr<Shaft> Robot::elevator;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<CougarOpticBoard> Robot::cob;
std::shared_ptr<Release> Robot::release;
std::shared_ptr<EndgameSystem> Robot::endgameSystem;

//Called when the driver presses enable. Usually called before the game start
void Robot::RobotInit() {
	RobotMap::init();
	driveTrain.reset(new DriveTrain());
	cubeIntake.reset(new CubeIntake());
	release.reset(new Release());
	endgameSystem.reset(new EndgameSystem());
	elevator.reset(new Shaft());
	//SmartDashboard::PutData(driveTrain.get());
	//CougarOpticBoard::InitBoard();
	oi.reset(new OI());
	//frc::DriverStation::GetInstance().GetGameSpecificMessage();

	//reset light
	oi->GetButtonBoard()->SetOutput(4, true);

	Robot::cob->InitBoard();
	Robot::cob->PushArmHeight(0);
	RobotMap::ahrs->ZeroYaw();


	//autonomousCommand.reset(new AngledDistanceDrive(10 * FEET_TO_INCHES, 0.5, 5, 55.0));

	//nt::NetworkTable::SetClientMode();
	//nt::NetworkTable::SetIPAddress("10.6.23.2");
	//nt::NetworkTable::Initialize();
	std::stringstream str;
	str << " Potientiometer " << RobotMap::pot->Get();
	DriverStation::ReportError(str.str());
}

void Robot::RobotPeriodic() {
	Robot::cob->PushEnabled(DriverStation::GetInstance().IsEnabled());
	Robot::cob->PushAutonomous(DriverStation::GetInstance().IsAutonomous());
	Robot::cob->PushTeleop(DriverStation::GetInstance().IsOperatorControl() && DriverStation::GetInstance().IsEnabled());

	Robot::cob->PushArmHeight((elevator->GetElevatorPosition() - ELEVATOR_BOTTOM) / ELEVATOR_DELTA);
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
}

void Robot::AutonomousPeriodic() {
	//push time to cob
	Robot::cob->PushFMSTime(DriverStation::GetInstance().GetMatchTime());
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	Robot::oi->GetButtonBoard()->SetOutput(4, true);
	Robot::elevator->enablePID(false);
	//Robot::elevator.get()->SetDefaultCommand(new SetElevatorSetpointTeleop());
	if (autonomousCommand)
		autonomousCommand->Cancel();
	CougarOpticBoard::PushArmRotation(0.0); //temporary fix
}

void Robot::TeleopPeriodic() {
	//push time to cob
	Robot::cob->PushFMSTime(DriverStation::GetInstance().GetMatchTime());
	if (frc::DriverStation::GetInstance().GetMatchTime() <= END_GAME_TIME || Robot::oi->GetButtonBoard()->GetRawButton(5)) {
		oi->GetButtonBoard()->SetOutput(1, true);
		oi->GetButtonBoard()->SetOutput(2, true);
		oi->GetButtonBoard()->SetOutput(3, true);
		endgameSystem->setIsEndGame(true);
	} else {
		oi->GetButtonBoard()->SetOutput(1, false);
		oi->GetButtonBoard()->SetOutput(2, false);
		oi->GetButtonBoard()->SetOutput(3, false);
		endgameSystem->setIsEndGame(false);
	}
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

