/*
 * CubeIntakeCommand.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#include "CubeIntakeCommand.h"
#include "../RobotMap.h"
#include "../Robot.h"

CubeIntakeCommand::CubeIntakeCommand(bool intake) {
	std::cout << "constructing CubeIntakeCommand\n";
	type = intake;
}

void CubeIntakeCommand::Initialize() {

}

void CubeIntakeCommand::Execute() {
	if (numSpikes >= INTAKE_MAX_NUM_SPIKES) {
		if (type) {
			//std::cout << "executing intake\n";
			Robot::cubeIntake->Intake();
		} else {
			//std::cout << "executing expunge\n";
			Robot::cubeIntake->Expunge();
		}
	}
	if (Robot::cubeIntake->GetCurrent() > INTAKE_MAX_CURRENT) {
		numSpikes++;
	}

}

bool CubeIntakeCommand::IsFinished() {
	return false;
}

void CubeIntakeCommand::End() {
	Robot::cubeIntake->Stop();
}

void CubeIntakeCommand::Interrupted() {
	End();
}

static void CubeIntakeCommand::ResetSpikes() {
	numSpikes = 0;
}
