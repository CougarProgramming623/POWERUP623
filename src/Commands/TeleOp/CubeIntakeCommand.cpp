/*
 * CubeIntakeCommand.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#include "CubeIntakeCommand.h"
#include "../../RobotMap.h"
#include "../../Robot.h"
using namespace std;

int CubeIntakeCommand::numSpikes;

CubeIntakeCommand::CubeIntakeCommand(bool intake, double timeout) {
	Requires(Robot::elevator.get());
	type = intake;
	numSpikes = 0;
	SetTimeout(timeout);
	this->timeout = timeout;
}

void CubeIntakeCommand::Initialize() {

}

void CubeIntakeCommand::Execute() {
	if (type) {
		if (numSpikes <= INTAKE_MAX_NUM_SPIKES) {
			Robot::cubeIntake->Intake();
		}
	} else {
		Robot::cubeIntake->Expunge();
	}
}

bool CubeIntakeCommand::IsFinished() {
	return timeout == 0.0 ? false : IsTimedOut();
}

void CubeIntakeCommand::End() {
	Robot::cubeIntake->Stop();
	DriverStation::ReportError("Done with cube intake");
}

void CubeIntakeCommand::Interrupted() {
	End();
}

void CubeIntakeCommand::ResetSpikes() {
	numSpikes = 0;
}
