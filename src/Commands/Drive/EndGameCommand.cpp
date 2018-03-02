/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "EndGameCommand.h"

EndGameCommand::EndGameCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void EndGameCommand::Initialize() {
	Robot::oi->GetButtonBoard()->SetOutput(1,  true);
	Robot::oi->GetButtonBoard()->SetOutput(2, true);
	Robot::oi->GetButtonBoard()->SetOutput(3, true);

	RobotMap::shaftOrRampRelay->Set(frc::Relay::Value::kReverse);
}

// Called repeatedly when this Command is scheduled to run
void EndGameCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool EndGameCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void EndGameCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EndGameCommand::Interrupted() {

}
