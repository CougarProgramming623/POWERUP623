/*
 * ButtonBoard.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#include "ButtonBoard.h"
#include "../Commands/CubeIntakeCommand.h"

#define PORT_INTAKE 6
#define PORT_EXPUNGE 5

ButtonBoard::ButtonBoard(int port):Joystick(port) {

	cubeIntakeButton.reset(new frc::JoystickButton(this, PORT_INTAKE));
	cubeExpungeButton.reset(new frc::JoystickButton(this, PORT_EXPUNGE));

	cubeIntakeButton->WhileHeld(new CubeIntakeCommand(true));
	cubeExpungeButton->WhileHeld(new CubeIntakeCommand(false));
}

