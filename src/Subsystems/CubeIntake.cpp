/*
 * CubeIntake.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#include "CubeIntake.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "ctre/Phoenix.h"

CubeIntake::CubeIntake() :
	frc::Subsystem("CubeIntake") {
	cubeIntake = RobotMap::intake;
#ifdef TEST_BOT
	testBotIntake2 = RobotMap::testBotIntake2;
#else
	cubeIntake2 = RobotMap::intake2;
#endif
}

void CubeIntake::InitDefaultCommand() {
	//do nothing
}

void CubeIntake::Periodic() {

}

void CubeIntake::Intake() {
	if (Robot::oi->GetButtonBoard()->GetRawButton(9))
		RobotMap::intake->SetInverted(true);
	else
		RobotMap::intake->SetInverted(false);
	cubeIntake->Set(INTAKE_SPEED);
#ifdef TEST_BOT
	testBotIntake2->Set(INTAKE_SPEED);
#endif
}

void CubeIntake::Expunge() {
	if (Robot::oi->GetButtonBoard()->GetRawButton(9))
		RobotMap::intake->SetInverted(true);
	else
		RobotMap::intake->SetInverted(false);

	cubeIntake->Set(-TELEOP_EXPUNGE_SPEED);
#ifdef TEST_BOT
	testBotIntake2->Set(-TELEOP_EXPUNGE_SPEED);
#endif
	/*
	 double speed = DriverStation::GetInstance().IsAutonomous() ? AUTO_EXPUNGE_SPEED : TELEOP_EXPUNGE_SPEED;
	 cubeIntake->Set(speed);
	 */
}

void CubeIntake::Stop() {
	cubeIntake->StopMotor();
#ifdef TEST_BOT
	testBotIntake2->StopMotor();
#endif
}

double CubeIntake::GetCurrent() {
	return cubeIntake->GetOutputCurrent();
}
