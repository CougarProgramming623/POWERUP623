/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ElevatorDoNothing.h"

#include "../Robot.h"

ElevatorDoNothing::ElevatorDoNothing() : frc::Command("Do Nothing") {
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void ElevatorDoNothing::Initialize() {
	DriverStation::ReportError("Starting doig nothing");
}

// Called repeatedly when this Command is scheduled to run
void ElevatorDoNothing::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorDoNothing::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ElevatorDoNothing::End() {
	DriverStation::ReportError("Done with do nothing");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorDoNothing::Interrupted() {

}
