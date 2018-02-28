/*
 * RelayDoNothing.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: frc623
 */

#include "RelayDoNothing.h"

RelayDoNothing::RelayDoNothing() {
	// TODO Auto-generated constructor stub

}

void RelayDoNothing::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RelayDoNothing::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RelayDoNothing::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RelayDoNothing::End() {
	//RobotMap::shaftOrRampRelay->Set(Relay::Value::kOff);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RelayDoNothing::Interrupted() {
	End();
}


