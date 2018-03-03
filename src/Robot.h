#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

#include "networktables/NetworkTableInstance.h"
#include "Commands/Drive/DistanceDrive.h"
#include "Commands/Turn.h"
#include "Commands/AutoSequence.h"
#include "Commands/Drive/DriveWithJoystick.h"

#include "Commands/AutonomousCommand.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/CubeIntake.h"
#include "Subsystems/Shaft.h"
#include "Subsystems/Release.h"
#include "Subsystems/EndgameSystem.h"

#include "Commands/AutonomousCommand.h"
#include "ahrs.h"
#include "CougarOpticBoard.h"

#include "OI.h"
#include "RobotImpl.h"


class Robot : public frc::TimedRobot {
public:
	static std::shared_ptr<CougarOpticBoard> cob;
	std::unique_ptr<Command> autonomousCommand;
	std::unique_ptr<Command> teleOpCommand;
	static std::unique_ptr<OI> oi;
	static std::shared_ptr<Shaft> elevator;
	static std::shared_ptr<DriveTrain> driveTrain;
	static std::shared_ptr<CubeIntake> cubeIntake;
	static std::shared_ptr<Release> release;
	static std::shared_ptr<EndgameSystem> endgameSystem;

	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void RobotPeriodic() override;
private:
	Timer *m_timer;
};
