/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "EndgameSystem.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Commands/TeleOp/EnableEndgameButtons.h"

EndgameSystem::EndgameSystem() : Subsystem("EndgameSubsystem") {
	climbAndRampMotor = RobotMap::endgameMotor;
	isEndGame = false;
}

void EndgameSystem::InitDefaultCommand() {
	SetDefaultCommand(new EnableEndGameButtons());
}

void EndgameSystem::setIsEndGame(bool b) {
	isEndGame = b;
}

bool EndgameSystem::getIsEndGame() {
	return isEndGame;
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
