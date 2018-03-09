/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ManualShaftControl.h"
#include "../Robot.h"

ManualShaftControl::ManualShaftControl() {
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void ManualShaftControl::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ManualShaftControl::Execute() {
	RobotMap::shaftController->Set(Robot::oi.get()->GetButtonBoard()->GetRawAxis(0));
}

// Make this return true when this Command no longer needs to run execute()
bool ManualShaftControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ManualShaftControl::End() {
	RobotMap::shaftController->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualShaftControl::Interrupted() {
	End();
}
