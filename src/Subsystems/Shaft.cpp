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

Shaft::Shaft() : PIDSubsystem("Shaft", 1.0, 0.0, 0.0) {
	SetSetpoint(ELEVATOR_TOP - ELEVATOR_DELTA);
	Enable();
}

double Shaft::ReturnPIDInput() {
	return RobotMap::analogInput->GetVoltage();
}

void Shaft::UsePIDOutput(double output) {
	RobotMap::shaftController->Set(output);

}

void Shaft::InitDefaultCommand() {
}


