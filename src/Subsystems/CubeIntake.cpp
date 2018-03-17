/*
 * CubeIntake.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#include "CubeIntake.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"

CubeIntake::CubeIntake() : frc::Subsystem("CubeIntake") {
	cubeIntake = RobotMap::intake;
	cubeIntake2 = RobotMap::intake2;
}

void CubeIntake::InitDefaultCommand() {
	//do nothing
}

void CubeIntake::Periodic() {

}

void CubeIntake::Intake() {
	cubeIntake->Set(INTAKE_SPEED);
}

void CubeIntake::Expunge() {
	cubeIntake->Set(-EXPUNGE_SPEED);
}

void CubeIntake::Stop() {
	cubeIntake->StopMotor();
}

double CubeIntake::GetCurrent() {
	return cubeIntake->GetOutputCurrent();
}
