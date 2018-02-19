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
#include "VisionDrive.h"
#include "../AutoPlace.h"
#include <cmath>

class AutoSequence : public frc::CommandGroup , public RobotImpl {
public:
	AutoSequence();
	static void Init();
private:
	void DoCenter();
	void DoSwitchNear();
	void DoSwitchFar();
	void DoScaleNear();
	void DoScaleFar();
	void DoBaseline();
	void TestBumpDetection();
	void TestTickCount();
	void TestPIDTurn();
	void DropCube();
};

