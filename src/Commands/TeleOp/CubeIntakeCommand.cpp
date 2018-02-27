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
	m_timer = new Timer();
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
	bool value = m_timer->Get() > timeout;
	DriverStation::ReportError(value ? "true " : "false");
	DriverStation::ReportError(std::to_string(m_timer->Get()));
	DriverStation::ReportError(std::to_string(timeout));
	return value;
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
