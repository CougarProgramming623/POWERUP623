/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetShaftSetpoint.h"


SetShaftSetpoint::SetShaftSetpoint(double setpoint) : frc::Command(){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
	m_setpoint = setpoint;

}

// Called just before this Command runs the first time
void SetShaftSetpoint::Initialize() {
	Robot::elevator->SetSetpoint(m_setpoint);
}

// Called repeatedly when this Command is scheduled to run
void SetShaftSetpoint::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool SetShaftSetpoint::IsFinished() {
	return (Robot::elevator->GetPosition() - m_setpoint < .08);
}

// Called once after isFinished returns true
void SetShaftSetpoint::End() {
	RobotMap::shaftController->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShaftSetpoint::Interrupted() {

}
