/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TogglePot.h"
#include "ManualShaftControl.h"
#include "../Robot.h"

TogglePot::TogglePot() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void TogglePot::Initialize() {
	OI* oi = Robot::oi.get();
	oi->usePID = !oi->usePID;
	oi->ResetElevatorLogic();
}

// Called repeatedly when this Command is scheduled to run
void TogglePot::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool TogglePot::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void TogglePot::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TogglePot::Interrupted() {

}
