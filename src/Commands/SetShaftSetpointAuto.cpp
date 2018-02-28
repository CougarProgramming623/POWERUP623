/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetShaftSetpointAuto.h"

#include "../CurrentSpikeIndicator.h"

SetShaftSetpointAuto::SetShaftSetpointAuto(float setpoint, double timeout) : SetShaftSetpointTeleop(setpoint){
	SetTimeout(timeout);
	Requires(Robot::elevator.get());
}

// Make this return true when this Command no longer needs to run execute()
bool SetShaftSetpointAuto::IsFinished() {
	return fabs(Robot::elevator->GetElevatorPosition() - m_setpoint) < .08f;
}

