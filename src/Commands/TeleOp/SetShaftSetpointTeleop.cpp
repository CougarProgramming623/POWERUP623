/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetShaftSetpointTeleop.h"
#include "../../CurrentSpikeIndicator.h"
#include "../../Robot.h"

SetShaftSetpointTeleop::SetShaftSetpointTeleop(double setpoint) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
	m_setpoint = setpoint;
}

// Called just before this Command runs the first time
void SetShaftSetpointTeleop::Initialize() {
	Robot::elevator->SetSetpoint(m_setpoint);
	Robot::elevator->Enable();
//s	currentSpike.reset(new CurrentSpikeIndicator(20, RobotMap::shaftController));
}

// Called repeatedly when this Command is scheduled to run
void SetShaftSetpointTeleop::Execute() {
	//currentSpike->Update();
	//bool hitSpike = currentSpike->GetSpike();
	//if(hitSpike) {
		//Robot::elevator->enablePID(false);
	//}
}

// Make this return true when this Command no longer needs to run execute()
bool SetShaftSetpointTeleop::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SetShaftSetpointTeleop::End() {
	RobotMap::shaftController->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShaftSetpointTeleop::Interrupted() {
	End();
}
