/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ReleaseRamp.h"
#include "../../Robot.h"

ReleaseRamp::ReleaseRamp() {
	Requires(Robot::release.get());
	SetTimeout(1.5);
}

// Called just before this Command runs the first time
void ReleaseRamp::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ReleaseRamp::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ReleaseRamp::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ReleaseRamp::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReleaseRamp::Interrupted() {
	End();
}
