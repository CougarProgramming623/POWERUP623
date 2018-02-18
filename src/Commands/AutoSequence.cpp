#include "AutoSequence.h"
#include <iostream>

#define invertIfRight(x) getStart() == SIDE_RIGHT ? -x : x
#define invertIfLeft(x) getStart() == SIDE_LEFT ? -x : x

AutoSequence::AutoSequence() :
		frc::CommandGroup(), RobotImpl() {

	//send to cob
	Robot::cob->PushFMSAlliance(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed);
	Robot::cob->PushFMSField(DriverStation::GetInstance().GetGameSpecificMessage());

	if(Robot::cob->GetAutonomousNoAuto()) {
		DriverStation::ReportError("Testing bump detection... ");
		TestBumpDetection(); //remove this before the match
		return;
	}
	RobotMap::ahrs->ZeroYaw();		//reset gyro degrees
	std::cout << "instructions " << Robot::cob->GetAutonomousInstructions() << std::endl;
	std::cout << "no cross map " << Robot::cob->GetAutonomousEnableCrossing() << std::endl;
	std::cout << "EMERGENCYDISABLE " << Robot::cob->GetAutonomousNoAuto() << std::endl;
	if (isCenterStart()) {
		double turnAngle = scaleOnRight() ? 55 : 135;
		DriverStation::ReportError("doing correct!");
		//AddSequential(new AngledDistanceDrive(10 * FEET_TO_INCHES, 0.5, 5, turnAngle));
		AddSequential(new AngledDistanceDrive(20, 0.5, 10, 45));
	} else {
		if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_EASY) {
			if (switchOnOurSide() && scaleOnOurSide())
				doSwitchNear();
			else if (switchOnOurSide() && !scaleOnOurSide())
				doSwitchNear();
			else if (!switchOnOurSide() && scaleOnOurSide())
				doScaleNear();
			else if (!switchOnOurSide() && !scaleOnOurSide())
				if (!Robot::cob->GetAutonomousEnableCrossing())
					doScaleFar();
				else {
					std::cout << "test spot 1" << std::endl;
					doBaseline();
				}
		} else {		// Everything except easy
			AutoPlace place;
			if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_SWITCH) {
				place = switchOnOurSide() ? AutoPlace::SWITCH_NEAR : AutoPlace::SWITCH_FAR;
			} else if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_SCALE) {
				place = scaleOnOurSide() ? AutoPlace::SCALE_NEAR : AutoPlace::SCALE_FAR;
			} else if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_BASELINE) {
				place = AutoPlace::BASELINE;
			} else {
				DriverStation::ReportError(
						"BADBADBAD CASE DOESNT EXIST FOR AUTO OPTIONS CHECK WITH PROGRAMMING AutoSequence.cpp");
			}
			if (Robot::cob->GetAutonomousEnableCrossing() && (place == AutoPlace::SCALE_FAR || place == AutoPlace::SWITCH_FAR)) {
				place = AutoPlace::BASELINE;
			}
			if (place == AutoPlace::SWITCH_NEAR)
				doSwitchNear();
			else if (place == AutoPlace::SWITCH_FAR)
				doScaleFar();
			else if (place == AutoPlace::SCALE_NEAR)
				doScaleNear();
			else if (place == AutoPlace::SCALE_FAR)
				doScaleFar();
			else if (place == AutoPlace::BASELINE) {
				std::cout << "test spot 2" << std::endl;
				doBaseline();
			}
			else
				DriverStation::ReportError("BADBADBAD UNKNOWN PLACE CASE AutoSequence.cpp");
		}

	}
}

void AutoSequence::TestBumpDetection() {
	AddSequential(new DistanceDrive(DISTANCE_TO_SCALE * 2, SPEED, TIMEOUT, false, true));
	WAIT
}

void AutoSequence::doSwitchNear() {
	AddSequential(new DistanceDrive(DISTANCE_TO_SWITCH - HALF_ROBOT_LENGTH, SPEED,
	TIMEOUT, false, false));
	WAIT
	AddSequential(new Turn(invertIfRight(90), TIMEOUT, SPEED));
	WAIT
	AddSequential(new DistanceDrive(1.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	DriverStation::ReportError("Dropping cube!");
	WAIT_SEC(1.0)
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	WAIT
	if (!Robot::cob->GetAutonomousEnableCrossing()) {
		AddSequential(new DistanceDrive(invertIfRight(-6 * FEET_TO_INCHES), SPEED,
				TIMEOUT, true));
		WAIT
		AddSequential(new Turn(invertIfRight(90), TIMEOUT, SPEED));
		WAIT
		AddSequential(new DistanceDrive(invertIfRight(-4 * FEET_TO_INCHES), SPEED,
				TIMEOUT, true));
	}

}

void AutoSequence::doSwitchFar() {
	AddSequential(new DistanceDrive(DISTANCE_TO_SWITCH + (3 * FEET_TO_INCHES) - HALF_ROBOT_WIDTH, FAST_SPEED,
	TIMEOUT));
	WAIT
	AddSequential(new Turn(invertIfRight(90), TIMEOUT, SPEED));
	WAIT
}

void AutoSequence::doScaleNear() {
	//drive to bump
	AddSequential(new DistanceDrive(DISTANCE_TO_SCALE - HALF_ROBOT_LENGTH, FAST_SPEED,
	TIMEOUT, false, true));
	WAIT
	//strafe
	AddSequential(new AngledDistanceDrive(10, SPEED, TIMEOUT, invertIfRight(90)));
	//turn
	AddSequential(new Turn(invertIfRight(90), TIMEOUT, SPEED));
	WAIT
	//drive forward
	AddSequential(new DistanceDrive(1 * FEET_TO_INCHES, SPEED, TIMEOUT));
	//dropping cube
	DriverStation::ReportError("Dropping cube!");
	WAIT_SEC(1.0)
	//move back
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	//drive back
	AddSequential(new DistanceDrive(invertIfRight(6 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
}

void AutoSequence::doScaleFar() {
	AddSequential(new DistanceDrive(20 * FEET_TO_INCHES - HALF_ROBOT_WIDTH, FAST_SPEED, TIMEOUT));
	WAIT
	AddSequential(new DistanceDrive(invertIfRight(14 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
	WAIT
	AddSequential(new DistanceDrive(0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
}

void AutoSequence::doBaseline() {
	if (isCenterStart()) {

	} else {
		AddSequential(new DistanceDrive(6 * FEET_TO_INCHES, SPEED, TIMEOUT));
	}
}

