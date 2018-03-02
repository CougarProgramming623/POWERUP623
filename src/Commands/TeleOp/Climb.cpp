/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Climb.h"
#include "../../Robot.h"

Climb::Climb() {
	Requires(Robot::endgameSystem.get());
}

// Called just before this Command runs the first time
void Climb::Initialize() {
	if(Robot::endgameSystem->getIsEndGame()) {
		RobotMap::endgameMotor->Set(CLIMB_SPEED);
	}
}

// Called repeatedly when this Command is scheduled to run
void Climb::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool Climb::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Climb::End() {
	RobotMap::endgameMotor->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Climb::Interrupted() {
	End();
}
