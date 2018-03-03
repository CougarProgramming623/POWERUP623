/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "EnableEndGameButtons.h"
#include "../../Robot.h"


EnableEndGameButtons::EnableEndGameButtons() {
	Requires(Robot::endgameSystem.get());
}

// Called just before this Command runs the first time
void EnableEndGameButtons::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void EnableEndGameButtons::Execute() {
	Robot::endgameSystem->setIsEndGame(DriverStation::GetInstance().IsOperatorControl() &&
									  (Robot::oi->GetButtonBoard()->GetRawButton(5) ||
									   DriverStation::GetInstance().GetMatchTime() <= END_GAME_TIME));

	if(Robot::endgameSystem->getIsEndGame()) {
			Robot::oi->GetButtonBoard()->SetOutput(1, true);
			Robot::oi->GetButtonBoard()->SetOutput(2, true);
			Robot::oi->GetButtonBoard()->SetOutput(3, true);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool EnableEndGameButtons::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void EnableEndGameButtons::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EnableEndGameButtons::Interrupted() {

}
