/*
 * AutoSequence.h
 *
 *  Created on: Jan 27, 2018
 *      Author: frc623
 */

#pragma once

#include "../RobotImpl.h"
#include "WPILib.h"
#include "Commands/CommandGroup.h"
#include "Commands/Command.h"

#include "DistanceDrive.h"
#include "Turn.h"
#include "../Robot.h"
#include "../RobotConstants.h"
#include "AngledDistanceDrive.h"
#include "../AutoPlace.h"

class AutoSequence : public frc::CommandGroup , public RobotImpl {
public:
	AutoSequence();
	static void Init();
private:
	void doSwitchNear();
	void doSwitchFar();
	void doScaleNear();
	void doScaleFar();
	void doBaseline();
	void TestBumpDetection();
};

