/*
 * AutoSequence.h
 *
 *  Created on: Jan 27, 2018
 *      Author: frc623
 */

#pragma once

#include "WPILib.h"
#include "Commands/CommandGroup.h"
#include "Commands/Command.h"
#include "../RobotImpl.h"
#include "DistanceDrive.h"
#include "Turn.h"
#include "../Robot.h"
#include "../RobotConstants.h"
#include "AngledDistanceDrive.h"


class AutoSequence: public frc::CommandGroup, public RobotImpl {
public:
	AutoSequence();
	static void Init();
private:
	void doSwitch();
	void doScale();
};

