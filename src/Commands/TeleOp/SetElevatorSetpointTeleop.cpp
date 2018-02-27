/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetElevatorSetpointTeleop.h"
#include "../../Robot.h"

SetElevatorSetpointTeleop::SetElevatorSetpointTeleop() : frc::Command() {
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void SetElevatorSetpointTeleop::Initialize() {
	Robot::elevator->Enable();
}

// Called repeatedly when this Command is scheduled to run
void SetElevatorSetpointTeleop::Execute() {

}
// Make this return true when this Command no longer needs to run execute()
bool SetElevatorSetpointTeleop::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SetElevatorSetpointTeleop::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetElevatorSetpointTeleop::Interrupted() {

}
