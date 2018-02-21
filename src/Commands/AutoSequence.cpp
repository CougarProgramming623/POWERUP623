#include "AutoSequence.h"
#include <iostream>

#define invertIfRight(x) getStart() == SIDE_RIGHT ? -x : x
#define invertIfLeft(x) getStart() == SIDE_LEFT ? -x : x
#define CUBE_EJECT_WAIT_TIME 2.0

/*
 * Our autonomous works by getting the selected options from the COB, and getting the scale / switch possession data from FMS. After that,
 * we check if do easy is selected. If so we use the FMS data to pick the easiest route. Otherwise we determine where the robot will go depending
 * on FMS and the disabled options. After that we switch to just crossing the auto line if we are going to cross the field, and the driver
 * disabled field crossing.
 *
 * Calling this constructor will add all of the commands to do autonomous based on FMS and data from the COB.
 * Just be sure to run the FRC scheduler so that the commands are actually executed.
 */
AutoSequence::AutoSequence() :
		frc::CommandGroup(), RobotImpl() {

	//send to cob
	Robot::cob->PushFMSAlliance(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed);
	Robot::cob->PushFMSField(DriverStation::GetInstance().GetGameSpecificMessage());

	if (Robot::cob->GetAutonomousNoAuto()) {
		DriverStation::ReportError("Testing tick count... ");
		TestPIDTurn(); //remove this before the match
		return;
	}
	std::cout << "instructions " << Robot::cob->GetAutonomousInstructions() << std::endl;
	std::cout << "no cross map " << Robot::cob->GetAutonomousEnableCrossing() << std::endl;
	std::cout << "EMERGENCYDISABLE " << Robot::cob->GetAutonomousNoAuto() << std::endl;
	if (isCenterStart()) {
		DoCenter();
	} else {		//We are on the sides
		if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_EASY) {
			if (switchOnOurSide() && scaleOnOurSide())
				DoSwitchNear();
			else if (switchOnOurSide() && !scaleOnOurSide())
				DoSwitchNear();
			else if (!switchOnOurSide() && scaleOnOurSide())
				DoScaleNear();
			else if (!switchOnOurSide() && !scaleOnOurSide()) {
				if (!Robot::cob->GetAutonomousEnableCrossing())
					DoScaleFar();
				else {
					std::cout << "test spot 1" << std::endl;
					DoBaseline();
				}
			} else {
				DriverStation::ReportError("BADBADBAD UNKNOWN PLACE CASE FOR DO EASY!!! line 61AutoSequence.cpp");
				DoBaseline();
			}
		} else {		// Cases except do easy (Only Switch, Only Scale, Baseline)
			AutoPlace place;
			if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_SWITCH) {
				place = switchOnOurSide() ? AutoPlace::SWITCH_NEAR : AutoPlace::SWITCH_FAR;
			} else if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_SCALE) {
				place = scaleOnOurSide() ? AutoPlace::SCALE_NEAR : AutoPlace::SCALE_FAR;
			} else if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_BASELINE) {
				place = AutoPlace::BASELINE;
			} else {
				place = AutoPlace::BASELINE;
				DriverStation::ReportError(
						"BADBADBAD CASE DOESNT EXIST FOR NON EASY AUTO OPTIONS CHECK WITH PROGRAMMING line 74 AutoSequence.cpp");
			}
			if (!Robot::cob->GetAutonomousEnableCrossing() && (place == AutoPlace::SCALE_FAR || place == AutoPlace::SWITCH_FAR)) {
				place = AutoPlace::BASELINE;
			}
			if (place == AutoPlace::SWITCH_NEAR)
				DoSwitchNear();
			else if (place == AutoPlace::SWITCH_FAR)
				DoScaleFar();
			else if (place == AutoPlace::SCALE_NEAR)
				DoScaleNear();
			else if (place == AutoPlace::SCALE_FAR)
				DoScaleFar();
			else if (place == AutoPlace::BASELINE) {
				std::cout << "test spot 2" << std::endl;
				DoBaseline();
			} else {
				DoBaseline();
				DriverStation::ReportError("BADBADBAD UNKNOWN PLACE CASE FOR NOT DO EASY line 92 AutoSequence.cpp");
			}
		}
	}
}

void AutoSequence::TestBumpDetection() {
	AddSequential(new DistanceDrive(20, FAST_SPEED, TIMEOUT, false, true));
	WAIT
}

void AutoSequence::TestTickCount() {
	//AddSequential(new DistanceDrive(100000000000000000000000000000000.0 * FEET_TO_INCHES, 0.5, TIMEOUT));
}

void AutoSequence::TestPIDTurn() {
	AddSequential(new Turn(90, TIMEOUT));
}

/**
 * Called when we want to deposit a cube on the same side of the switch that we are starting on.
 * This function is only to be used when we are starting on the outside.
 */
void AutoSequence::DoSwitchNear() {
	//Go forward to the switch, then turn toward the inside of the field, then move in, drop cube, move back,
	//strafe toward the center, rotate and setup for teleop
	AddSequential(new DistanceDrive(DISTANCE_TO_SWITCH + WIDTH_OF_SWITCH / 2 - ROBOT_LENGTH / 2, SPEED, TIMEOUT, false, false));
	WAIT
	AddSequential(new Turn(invertIfRight(90), TIMEOUT));
	WAIT
	AddSequential(new DistanceDrive(1.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	DropCube();
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	WAIT
	if (Robot::cob->GetAutonomousEnableCrossing()) {
		AddSequential(new DistanceDrive(invertIfRight(-6 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
		WAIT
		AddSequential(new Turn(invertIfRight(180), TIMEOUT));
		WAIT
		AddSequential(new DistanceDrive(invertIfRight(-4 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
	}

}

/**
 * Called when we want to deposit a cube on the opposite side of the switch than we are starting on.
 * This function is only to be used when we are starting on the outside.
 */
void AutoSequence::DoSwitchFar() {
	AddSequential(new DistanceDrive(DISTANCE_TO_SWITCH + (3 * FEET_TO_INCHES) - HALF_ROBOT_WIDTH, FAST_SPEED, TIMEOUT));
	WAIT
	AddSequential(new DistanceDrive(invertIfRight(20 * FEET_TO_INCHES - HALF_ROBOT_WIDTH), FAST_SPEED, TIMEOUT, true));
	WAIT
	AddSequential(new Turn(180, TIMEOUT));
	WAIT
	DropCube();
}

/**
 * Called when we want to deposit a cube on the same side of the scale that we are starting on.
 * This function is only to be used when we are starting on the outside.
 */
void AutoSequence::DoScaleNear() {
	//drive to bump
	AddSequential(new DistanceDrive(18 * FEET_TO_INCHES, FAST_SPEED, TIMEOUT, false));
	//Can we raise here? Or after we detect the bump on the next line
	AddSequential(new DistanceDrive(20 * FEET_TO_INCHES, FAST_SPEED, TIMEOUT, false, true));
	WAIT
	//strafe
	AddSequential(new DistanceDrive(invertIfRight(-10), SPEED, TIMEOUT, true, false));
	//turn
	AddSequential(new Turn(invertIfRight(90), TIMEOUT));
	WAIT
	//drive forward
	AddSequential(new DistanceDrive(1 * FEET_TO_INCHES, FAST_SPEED, TIMEOUT));
	//dropping cube
	DropCube();
	//move back
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, FAST_SPEED, TIMEOUT));
	WAIT
	//turn
	AddSequential(new Turn(invertIfRight(180), TIMEOUT));
	WAIT
	//drive back
	AddSequential(new DistanceDrive(6 * FEET_TO_INCHES, FAST_SPEED, TIMEOUT, false, false));
	WAIT
	if (Robot::cob->GetAutonomousEnableCrossing()) {
		//AddSequential(new DistanceDrive(invertIfRight(-6 * FEET_TO_INCHES), SPEED, TIMEOUT, false));
		//WAIT
		//AddSequential(new Turn(invertIfRight(180), TIMEOUT, SPEED));
		//WAIT
		AddSequential(new DistanceDrive(invertIfRight(-4 * FEET_TO_INCHES), FAST_SPEED, TIMEOUT, true));
	}

}

/**
 * Called when we want to deposit a cube on the opposite side of the scale than we are starting on.
 * This function is only to be used when we are starting on the outside.
 */
void AutoSequence::DoScaleFar() {
	AddSequential(new DistanceDrive(20 * FEET_TO_INCHES - HALF_ROBOT_WIDTH, FAST_SPEED, TIMEOUT));
	WAIT
	AddSequential(new DistanceDrive(invertIfRight(14 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
	WAIT
	AddSequential(new DistanceDrive(0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	WAIT
	DropCube();
}

/**
 * This function drives the robot across the autoline, and sets it up for picking up cubes if we are in the center
 */
void AutoSequence::DoBaseline() {
	if (isCenterStart()) {
		AddSequential(new DistanceDrive(2 * FEET_TO_INCHES, SPEED, TIMEOUT, true));	//Go right 2 feet
		AddSequential(new DistanceDrive(10 * FEET_TO_INCHES, SPEED, TIMEOUT));	//drive forward to break the auto line
		AddSequential(new DistanceDrive(-6 * FEET_TO_INCHES, SPEED, TIMEOUT));//drive back towards the start but stop 4 feet out from the wall
		AddSequential(new DistanceDrive(2 * FEET_TO_INCHES, SPEED, TIMEOUT, true));	//Go right 2 feet
		//We should be in front of the cubes
	} else {	//If we are on the outside
		//Just drive across since there are no blocks to pervent our passage
		AddSequential(new DistanceDrive(10 * FEET_TO_INCHES, SPEED, TIMEOUT));
	}
}

void AutoSequence::DropCube() {
	//Drops the cube by setting power to the holding motors
	//Robot::motor1->setPower...

	WAIT_SEC(CUBE_EJECT_WAIT_TIME)
	//Wait for the motors to spin and the cube to fly out...
}

void AutoSequence::DoCenter() {
	double angleFromCenter = 40;
	double turnAngle = switchOnRight() ? 90 - (angleFromCenter + 20) : 90 + angleFromCenter;
	DriverStation::ReportError("doing correct!");
	WAIT_SEC(Robot::cob->GetAutonomousInstructions());//In this case, because we are in the center, the auto instructions contain the timeout
	AddSequential(new AngledDistanceDrive(4, SPEED, turnAngle));
	if (true) {	//Use ticks
		WAIT
	} else {		//Use vision
		AddSequential(new VisionDrive(SPEED, TIMEOUT, 100, turnAngle));
		//Vision stuff
		WAIT
	}
	DropCube();
	//Go back but more sharply so that we arrive not at the wall, but in front of the cubes
	AddSequential(new DistanceDrive(-4 * FEET_TO_INCHES, SPEED, TIMEOUT));
	WAIT
	if(switchOnRight()) {
		AddSequential(new DistanceDrive(-4.5 * FEET_TO_INCHES, SPEED, TIMEOUT, true, false));
	} else {
		AddSequential(new DistanceDrive(6 * FEET_TO_INCHES, SPEED, TIMEOUT, true, false));
	}
}
