/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetBottom.h"

#include "../../RobotMap.h"
#include "../../Robot.h"

SetBottom::SetBottom() {
}

// Called just before this Command runs the first time
void SetBottom::Initialize() {
	RobotMap::elevatorBottom = RobotMap::pot->Get();
	RobotMap::elevatorTop = RobotMap::elevatorBottom + ELEVATOR_DELTA;
	Robot::elevator->SetInputRange(RobotMap::elevatorBottom, RobotMap::elevatorTop);
	Robot::GetOI()->setBottom = true;
}

// Called repeatedly when this Command is scheduled to run
void SetBottom::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SetBottom::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SetBottom::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetBottom::Interrupted() {

}
