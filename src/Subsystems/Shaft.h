/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/PIDSubsystem.h>
#include "../RobotConstants.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"



class Shaft : public frc::PIDSubsystem {
public:
	Shaft();
	double ReturnPIDInput() override;
	void UsePIDOutput(double output) override;
	void InitDefaultCommand() override;
	double GetElevatorPosition();
private:
	std::shared_ptr<WPI_TalonSRX> shaftDrive;
};

