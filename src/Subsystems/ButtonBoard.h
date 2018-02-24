/*
 * ButtonBoard.h
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#ifndef SRC_SUBSYSTEMS_BUTTONBOARD_H_
#define SRC_SUBSYSTEMS_BUTTONBOARD_H_
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"

class ButtonBoard : public frc::Joystick{

private:
	std::shared_ptr<frc::JoystickButton> cubeIntakeButton;
	std::shared_ptr<frc::JoystickButton> cubeExpungeButton;

public:
	ButtonBoard(int);
};

#endif /* SRC_SUBSYSTEMS_BUTTONBOARD_H_ */
