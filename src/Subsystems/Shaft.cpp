/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shaft.h"

#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>
#include "../Robot.h"
#include "../RobotMap.h"
#include "../Commands/ElevatorDoNothing.h"
#include "../Commands/ElevatorTeleop.h"
#include "../Robot.h"

Shaft::Shaft() : PIDSubsystem("Shaft", 9.0, 0.0, 0.0) {
	shaftDrive = RobotMap::shaftController;
	SetInputRange(Robot::GetElevatorBottom(), Robot::GetElevatorTop());
	SetOutputRange(-1.0, 1.0);
}

double Shaft::ReturnPIDInput() {
	return RobotMap::pot->Get();
}

void Shaft::UsePIDOutput(double output) {
	shaftDrive->Set(output);
}

void Shaft::InitDefaultCommand() {
	SetDefaultCommand(new ElevatorTeleop());
}

double Shaft::GetElevatorPosition() {
	return RobotMap::pot->Get();
}

