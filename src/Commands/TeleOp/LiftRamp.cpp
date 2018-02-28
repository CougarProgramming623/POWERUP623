/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LiftRamp.h"
#include "../../Robot.h"

LiftRamp::LiftRamp() {
	Requires(Robot::endgameSystem.get());
	SetTimeout(RAMP_LIFT_TIMEOUT);
}

// Called just before this Command runs the first time
void LiftRamp::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void LiftRamp::Execute() {
	RobotMap::endgameMotor->Set(RAMP_LIFT_SPEED);
}

// Make this return true when this Command no longer needs to run execute()
bool LiftRamp::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void LiftRamp::End() {
	RobotMap::endgameMotor->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftRamp::Interrupted() {

}
