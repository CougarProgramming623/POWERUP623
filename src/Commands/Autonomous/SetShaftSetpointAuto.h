/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Commands/Subsystem.h"
#include "../../RobotMap.h"
#include "WPILib.h"
#include "../TeleOp/SetShaftSetpointTeleop.h"

class SetShaftSetpointAuto : public SetShaftSetpointTeleop {
public:
	SetShaftSetpointAuto(double, double);
	bool IsFinished() override;
};
