/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetShaftSetpointTeleop.h"

SetShaftSetpointTeleop::SetShaftSetpointTeleop(double setpoint) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_setpoint = setpoint;
}

// Called just before this Command runs the first time
void SetShaftSetpointTeleop::Initialize() {
	Robot::elevator->SetSetpoint(m_setpoint);
	Robot::elevator->Enable();
	currentSpikeIndicator.reset(new CurrentSpikeIndicator(0, RobotMap::shaftController));
}

// Called repeatedly when this Command is scheduled to run
void SetShaftSetpointTeleop::Execute() {
	std::stringstream str;
	bool currentSpike = currentSpikeIndicator->GetSpike();
	str << "Current Spike? " << (currentSpike ? "true" : "false");
	DriverStation::ReportError(str.str());
	if (currentSpike) {
		Robot::elevator->enablePID(false);
		DriverStation::ReportError("Disabled PID");
	}
	str << " Elevator Displacement " << Robot::elevator->GetElevatorPosition() - m_setpoint;
	DriverStation::ReportError(str.str());
	//current value
	currentSpikeIndicator->Update();
}

// Make this return true when this Command no longer needs to run execute()
bool SetShaftSetpointTeleop::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SetShaftSetpointTeleop::End() {
	//DriverStation::ReportError("done");
	RobotMap::shaftController->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShaftSetpointTeleop::Interrupted() {
	End();
}
