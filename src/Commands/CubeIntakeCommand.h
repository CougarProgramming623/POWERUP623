/*
 * CubeIntakeCommand.h
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#ifndef SRC_COMMANDS_CUBEINTAKECOMMAND_H_
#define SRC_COMMANDS_CUBEINTAKECOMMAND_H_
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"

class CubeIntakeCommand : public frc::Command {
private:
	bool type;
	static unsigned int numSpikes = 0;
public:
	CubeIntakeCommand(bool intake);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	static void ResetSpikes();
};

#endif /* SRC_COMMANDS_CUBEINTAKECOMMAND_H_ */
