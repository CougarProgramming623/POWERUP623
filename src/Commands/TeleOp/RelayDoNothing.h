/*
 * RelayDoNothing.h
 *
 *  Created on: Feb 28, 2018
 *      Author: frc623
 */

#ifndef SRC_COMMANDS_TELEOP_RELAYDONOTHING_H_
#define SRC_COMMANDS_TELEOP_RELAYDONOTHING_H_

#include "Commands/Subsystem.h"
#include "WPILib.h"

class RelayDoNothing : public frc::Command {
public:
	RelayDoNothing();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif /* SRC_COMMANDS_TELEOP_RELAYDONOTHING_H_ */
