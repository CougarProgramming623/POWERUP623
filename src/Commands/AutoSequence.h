/*
 * AutoSequence.h
 *
 *  Created on: Jan 27, 2018
 *      Author: frc623
 */

#include "WPILib.h"
#include "Commands/CommandGroup.h"
#include "Commands/Command.h"
#include "../RobotImpl.h"

#ifndef SRC_COMMANDS_AUTOSEQUENCE_H_
#define SRC_COMMANDS_AUTOSEQUENCE_H_

class AutoSequence: public frc::CommandGroup, public RobotImpl {
public:
	AutoSequence();
private:
	void doSwitch();
	void doScale();
};

#endif /* SRC_COMMANDS_AUTOSEQUENCE_H_ */
