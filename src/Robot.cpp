#include "Robot.h"
#include "RobotConstants.h"
#include "Commands/Drive/AngledDistanceDrive.h"
#include "DriverStation.h"
#include "Commands/TeleOp/CubeIntakeCommand.h"
#include "Commands/ElevatorDoNothing.h"
#include "Commands/ElevatorTeleop.h"
#include "networktables/NetworkTableType.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<CubeIntake> Robot::cubeIntake;
std::shared_ptr<Shaft> Robot::elevator;
std::shared_ptr<CougarOpticBoard> Robot::cob;
std::shared_ptr<BeagleBone> Robot::bb;
std::shared_ptr<Release> Robot::release;
std::shared_ptr<EndgameSystem> Robot::endgameSystem;
std::shared_ptr<Aesthetics> Robot::aesthetics;
std::unique_ptr<OI> Robot::oi;

//Called when the driver presses enable. Usually called before the game start
void Robot::RobotInit() {
	isTeleop = false;
	SmartDashboard::SetDefaultNumber("et", -0.0);

	SmartDashboard::GetNumber("eb", -0.0);

	RobotMap::init();
	driveTrain.reset(new DriveTrain());
	cubeIntake.reset(new CubeIntake());
	release.reset(new Release());
	endgameSystem.reset(new EndgameSystem());
	elevator.reset(new Shaft());
	elevator->SetDefaultCommand(new ElevatorTeleop());
	aesthetics.reset(new Aesthetics());
	//SmartDashboard::PutData(driveTrain.get());
	//CougarOpticBoard::InitBoard();
	oi.reset(new OI());
	//frc::DriverStation::GetInstance().GetGameSpecificMessage();

	//reset light
	oi->GetButtonBoard()->SetOutput(TOGGLE_SLIDER_LED, true);

	bb.reset(new BeagleBone());
	//Robot::bb->InitBeagleBoneTable();
	Robot::cob->InitBoard();
	Robot::cob->PushArmHeight(0);
	RobotMap::ahrs->ZeroYaw();

	//autonomousCommand.reset(new AngledDistanceDrive(10 * FEET_TO_INCHES, 0.5, 5, 55.0));

	//nt::NetworkTable::SetClientMode();
	//nt::NetworkTable::SetIPAddress("10.6.23.2");
	//nt::NetworkTable::Initialize();
	std::stringstream str;
	str << " Potentiometer " << RobotMap::pot->Get();
	DriverStation::ReportError(str.str());
	m_timer = new Timer();
}

void Robot::RobotPeriodic() {
	Robot::cob->PushEnabled(DriverStation::GetInstance().IsEnabled());
	Robot::cob->PushAutonomous(DriverStation::GetInstance().IsAutonomous());
	Robot::cob->PushTeleop(DriverStation::GetInstance().IsOperatorControl() && DriverStation::GetInstance().IsEnabled());
	Robot::cob->PushLidar(RobotMap::elevatorBottom);
	//DriverStation::ReportError(DriverStation::GetInstance().IsAutonomous() ? "Auto" : "Not Auto");
	/*Robot::cob->PushLidar(RobotMap::lidar->GetDistance());
	 Robot::cob->PushArmHeight((elevator->GetElevatorPosition() - ELEVATOR_BOTTOM) / ELEVATOR_DELTA);
	 double XAxis = Robot::oi->GetDriverJoystick()->GetRawAxis(0);
	 double YAxis = -Robot::oi->GetDriverJoystick()->GetRawAxis(1);
	 double velAngle = -atan(YAxis / XAxis) * 180 / M_PI - 90;
	 if (XAxis > 0)
	 velAngle += 180;
	 Robot::cob->PushVelocityDirection(velAngle);
	 double angle = RobotMap::ahrs->GetYaw();
	 Robot::cob->PushRotation(angle);
	 Robot::cob->PushVelocityMagnitude(sqrt(XAxis * XAxis + YAxis * YAxis));
	 */
	//DriverStation::ReportError("Setpoint: " + std::to_string(elevator->GetPosition()) + " current position " + std::to_string(RobotMap::pot->Get()));
}

void Robot::DisabledInit() {
	//m_timer = new Timer();
	//m_timer->Start();
	oi->sliderEnabled = false;
	oi->usePID = true;
	oi->ResetElevatorLogic();

	if(isTeleop)
	{
		bb->PushShutdown(true);
		isTeleop = false;
	} else {
		bb->PushShutdown(false);
	}

}

void Robot::DisabledPeriodic() {
	//std::cout << "Elevator Position: " << Robot::elevator->GetElevatorPosition() << std::endl;

	/*
	 if((int)time % 3 == 0) {
	 oi->GetButtonBoard()->SetOutput(3, true);
	 oi->GetButtonBoard()->SetOutput(1, false);
	 oi->GetButtonBoard()->SetOutput(2, false);
	 } else if((int)time % 3 == 1) {
	 oi->GetButtonBoard()->SetOutput(2, true);
	 oi->GetButtonBoard()->SetOutput(1, false);
	 oi->GetButtonBoard()->SetOutput(3, false);
	 } else if((int)time % 3 == 2) {
	 oi->GetButtonBoard()->SetOutput(1, true);
	 oi->GetButtonBoard()->SetOutput(2, false);
	 oi->GetButtonBoard()->SetOutput(3, false);
	 }
	 */
	if (counter > (1000 / 20)) {
		Robot::cob->Update();
//#ifndef TEST_BOT
		PrintEntry(cob->entryAutonomousStartPos);
		PrintEntry(cob->entryAutonomousNoAuto);
		PrintEntry(cob->entryAutonomousEnableCrossing);
		PrintEntry(cob->entryAutonomousInstructions);
//#endif
		counter = 0;

	}
	counter++;
	bb->PushColorEntry(DriverStation::GetInstance().GetAlliance());
	frc::Scheduler::GetInstance()->Run();
}

void Robot::InitLights() {
	oi->GetButtonBoard()->SetOutput(1, false);
	oi->GetButtonBoard()->SetOutput(2, false);
	oi->GetButtonBoard()->SetOutput(3, false);
}

void Robot::PrintEntry(nt::NetworkTableEntry& entry) {
	std::stringstream str;
	std::string name = entry.GetName();

	unsigned int slash = name.find_last_of('/');	//Only show the part after the last /
	if (slash == std::string::npos)
		slash = 0;
	else
		slash++;	//skip th the next index so we dont include the / that was found
	int length = name.length() - slash;
	str << name.substr(slash, length) << " = ";

	if (name.find("instructions") != std::string::npos) {
		str << "[Instructions]" << (int) entry.GetDouble(-623);
	} else {

		switch (entry.GetType()) {
		case nt::NetworkTableType::kBoolean:
			str << "[bool] " << (entry.GetBoolean(false) ? "true" : "false");
			break;
		case nt::NetworkTableType::kDouble:
			str << "[double] " << entry.GetDouble(-623);
			break;
		case nt::NetworkTableType::kUnassigned:
			str << "UNASSIGNED!!!";
			break;
		case nt::NetworkTableType::kString:
			str << "[string] " << entry.GetString("Default String");
			break;
		default:
			str << "UNHANDLED CASE IN PrintEntry " << (int) (entry.GetType());
		}
	}
	DriverStation::ReportError(str.str());
}

void Robot::AutonomousInit() {
	InitLights();
	//Create auto sequence here so that we have access to game time only information.
	//Otherwise we would be trying to read FMS at robot init which happens before game time.
	RobotMap::ahrs->ZeroYaw();

	autonomousCommand.reset(new AutoSequence());
	RobotMap::lidar->ResetPort();
	if (autonomousCommand)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	//push time to cob
	Robot::cob->PushFMSTime(DriverStation::GetInstance().GetMatchTime());
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	oi->ResetElevatorLogic();
	//Robot::elevator.get()->SetDefaultCommand(new SetElevatorSetpointTeleop());
	if (autonomousCommand)
		autonomousCommand->Cancel();
	CougarOpticBoard::PushArmRotation(0.0);	//temporary fix
	isTeleop = true;
}

bool Robot::IsEndGame() {
	bool override = Robot::oi->GetButtonBoard()->GetRawButton(ENDGAME_OVERRIDE_BUTTON);
	if (frc::DriverStation::GetInstance().GetMatchTime() < 0 && !override)
		return false;
	return frc::DriverStation::GetInstance().GetMatchTime() <= END_GAME_TIME;
}

void Robot::TeleopPeriodic() {
	//DriverStation::ReportError(std::to_string(RobotMap::pot->Get()));
	//push time to cob
	Robot::cob->PushFMSTime(DriverStation::GetInstance().GetMatchTime());
	frc::Scheduler::GetInstance()->Run();
	Robot::aesthetics->Update();
	if (!lastEndgame && Robot::IsEndGame()) {
		lastEndgame = true;
		aesthetics->OnEndgame();
	}
}

void Robot::TestPeriodic() {
	DriverStation::ReportError(
		"LIDAR: " + std::to_string(RobotMap::lidar->GetDistance()) + "/ Pot Reading: " + std::to_string(RobotMap::pot->Get()) + " / Setpoint:" + std::to_string(Robot::elevator->GetPosition()));
}

double Robot::GetElevatorTop() {
	return RobotMap::elevatorTop;
}
double Robot::GetElevatorBottom() {
	return RobotMap::elevatorBottom;
}

OI* Robot::GetOI() {
	return oi.get();
}

START_ROBOT_CLASS(Robot);

