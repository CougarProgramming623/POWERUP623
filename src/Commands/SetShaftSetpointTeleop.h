/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "../CurrentSpikeIndicator.h"

class SetShaftSetpointTeleop : public frc::Command {
public:
	SetShaftSetpointTeleop(double);
	void Initialize() override;
	void Execute() override;
	virtual bool IsFinished() override;
	void End() override;
	void Interrupted() override;
protected:
	double m_setpoint = 0.0;
	std::shared_ptr<CurrentSpikeIndicator> currentSpikeIndicator;

};

