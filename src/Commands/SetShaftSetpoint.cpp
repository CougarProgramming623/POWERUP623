/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetShaftSetpoint.h"


SetShaftSetpoint::SetShaftSetpoint(bool up, bool useInAuto) : frc::Command(){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
	goUp = up;
	autonomous = useInAuto;
	m_timer = new Timer();
}

// Called just before this Command runs the first time
void SetShaftSetpoint::Initialize() {
	//Robot::elevator->SetSetpoint(m_setpoint);
	//Robot::elevator->Enable();
	SetTimeout(2);
	m_timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void SetShaftSetpoint::Execute() {
	std::cout << RobotMap::shaftController->GetOutputCurrent() << std::endl;
	if(goUp)
		RobotMap::shaftController->Set(0.7);
	else
		RobotMap::shaftController->Set(-0.7);
}

// Make this return true when this Command no longer needs to run execute()
bool SetShaftSetpoint::IsFinished() {
	//return (Robot::elevator->GetPosition() - m_setpoint < .08);
	if(autonomous && m_timer && m_timer->Get() > 2)
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void SetShaftSetpoint::End() {
	RobotMap::shaftController->StopMotor();

	m_timer->Stop();
	m_timer->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShaftSetpoint::Interrupted() {
	End();
}
