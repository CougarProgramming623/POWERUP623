/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetShaftSetpointAuto.h"
#include "../../Robot.h"
#include "../ElevatorDoNothing.h"

SetShaftSetpointAuto::SetShaftSetpointAuto(double setpoint, double timeout) :
		SetShaftSetpointTeleop(setpoint) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());

	SetTimeout(timeout);
}

void SetShaftSetpointAuto::Execute() {

	DriverStation::ReportError("Auto setpoint: " + std::to_string(m_setpoint));
	currentSpike->Update();
	bool hitSpike = currentSpike->GetSpike();
	Robot::elevator->SetSetpoint(m_setpoint);
	if (hitSpike) {
		Robot::elevator->SetCurrentCommand(new ElevatorDoNothing());
	}
}

bool SetShaftSetpointAuto::IsFinished() {
	bool value = (fabs(Robot::elevator->GetElevatorPosition() - m_setpoint) < .08f);
	if (value)
		DriverStation::ReportError("SetShaftSetpointAuto done");
	return value || IsTimedOut();
}
