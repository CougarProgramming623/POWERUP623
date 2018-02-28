/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ReleaseRamp.h"
#include "../../Robot.h"

#define RAMP_OFF_TIME 1 // This refers to how many seconds it takes for the gas spring to push the sloped part of the ramp off the robot before raising the top part
#define RAMP_RAISE_TIME 1// How long we need to run the motor backwards to make the gas springs raise the center part of the ramp
#define TOTAL_TIME RAMP_OFF_TIME + RAMP_RAISE_TIME
ReleaseRamp::ReleaseRamp() {
	Requires(Robot::release.get());
	SetTimeout(1.5);
	m_timer = new Timer();
}

// Called just before this Command runs the first time
void ReleaseRamp::Initialize() {
	RobotMap::shaftOrRampRelay->Set(Relay::Value::kReverse); //FIXME put in proper direction
}

// Called repeatedly when this Command is scheduled to run
void ReleaseRamp::Execute() {
	/*
	if (m_timer->Get() > RAMP_OFF_TIME) {
		if (!startedRampUp) { //We are done pushing the sloped part off, raise the ramp
			RobotMap::liftController->Set(-0.25);
			startedRampUp = true;
		} else {

		}
	} else { //We are waiting for the sloped part of the ramp to get pushed out by the horizontal gas spring

	}
	*/
}

// Make this return true when this Command no longer needs to run execute()
bool ReleaseRamp::IsFinished() {
	//return m_timer->Get() > TOTAL_TIME;
	return IsTimedOut();
}

// Called once after isFinished returns true
void ReleaseRamp::End() {
	//RobotMap::liftController->StopMotor();
	//RobotMap::shaftOrRampRelay->Set(Relay::Value::kOff);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReleaseRamp::Interrupted() {
	End();
}
