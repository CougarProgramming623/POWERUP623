/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetShaftSetpoint.h"

SetShaftSetpoint::SetShaftSetpoint(float setpoint, double timeout, bool up) :
		frc::Command() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
	goUp = up;
	m_setpoint = setpoint;
	SetTimeout(timeout);
	autonomous = false;	//Help Ronnie
}

// Called just before this Command runs the first time
void SetShaftSetpoint::Initialize() {
	Robot::elevator->SetSetpoint(m_setpoint);
	Robot::elevator->Enable();
}

// Called repeatedly when this Command is scheduled to run
void SetShaftSetpoint::Execute() {
/*
	std::stringstream str;
	str << " Elevator Displacement " << Robot::elevator->GetElevatorPosition() - m_setpoint;
	DriverStation::ReportError(str.str());
*/
}
// Make this return true when this Command no longer needs to run execute()
bool SetShaftSetpoint::IsFinished() {
	if (Robot::elevator->GetElevatorPosition() > ELEVATOR_DELTA) {
		return true;
	}
	return (fabs(Robot::elevator->GetElevatorPosition() - m_setpoint) < .08f);
}

// Called once after isFinished returns true
void SetShaftSetpoint::End() {
	DriverStation::ReportError("Finished with set shaft setoping");

	RobotMap::shaftController->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShaftSetpoint::Interrupted() {
	End();
}
