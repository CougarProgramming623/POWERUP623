/*
 * CubeIntakeCommand.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#include "CubeIntakeCommand.h"
#include "../RobotMap.h"
#include "../Robot.h"
using namespace std;

int CubeIntakeCommand::numSpikes;

CubeIntakeCommand::CubeIntakeCommand(bool intake) {
	type = intake;
	numSpikes = 0;
}

void CubeIntakeCommand::Initialize() {

}

void CubeIntakeCommand::Execute() {
	if (type) {
		if (numSpikes <= INTAKE_MAX_NUM_SPIKES) {
			//std::cout << "executing intake\n";
			Robot::cubeIntake->Intake();
		}
	} else {
		//std::cout << "executing expunge\n";
		Robot::cubeIntake->Expunge();
	}
	//std::cout << Robot::cubeIntake->GetCurrent() << std::endl;
	//if (Robot::cubeIntake->GetCurrent() > INTAKE_MAX_CURRENT) {
	//	numSpikes++;
	//}

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

void CubeIntakeCommand::ResetSpikes() {
	numSpikes = 0;
}
