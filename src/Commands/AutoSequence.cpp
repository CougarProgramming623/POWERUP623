#include "AutoSequence.h"
#include "Autonomous/SetShaftSetpointAuto.h"
#include "Math.h"
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
		//TestPIDTurn(); //remove this before the match
		return;
	}
	std::cout << "instructions " << Robot::cob->GetAutonomousInstructions() << std::endl;
	std::cout << "no cross map " << Robot::cob->GetAutonomousEnableCrossing() << std::endl;
	std::cout << "EMERGENCYDISABLE " << Robot::cob->GetAutonomousNoAuto() << std::endl;
	AddSequential(new DistanceDrive(2 * FEET_TO_INCHES, 0.5, 1.5));
	releaseShaft();
	WAIT
	//WAIT_SEC(1)
	//RaiseElevatorToSwitch();
	//DropCube();

	if (isCenterStart()) {
		DriverStation::ReportError("Doing Center");
		DoCenter();
	} else {		//We are on the sides
		if (Robot::cob->GetAutonomousInstructions() == OPTION_DO_EASY) {
			if (switchOnOurSide() && scaleOnOurSide()) {
				DriverStation::ReportError("Doing switch near");
				DoSwitchNear();
			} else if (switchOnOurSide() && !scaleOnOurSide()) {
				DriverStation::ReportError("Doing switch near");
				DoSwitchNear();
			} else if (!switchOnOurSide() && scaleOnOurSide()) {
				DriverStation::ReportError("Doing scale near");
				DoScaleNear();
			} else if (!switchOnOurSide() && !scaleOnOurSide()) {
				if (!Robot::cob->GetAutonomousEnableCrossing()) {
					DriverStation::ReportError("Doing baseline");
					DoScaleFar();
				} else {
					DriverStation::ReportError("Doing baseline");
					DoBaseline();
				}
			} else {
				DriverStation::ReportError("UNKNOWN PLACE CASE");
				DriverStation::ReportError("Doing baseline");
				DoBaseline();
			}
		} else {		// Cases except do easy (Only Switch, Only Scale, Baseline)
			AutoPlace place;
			int autoInstructions = Robot::cob->GetAutonomousInstructions();

			if (autoInstructions == OPTION_DO_SWITCH) {
				place = switchOnOurSide() ? AutoPlace::SWITCH_NEAR : AutoPlace::BASELINE;
			} else if (autoInstructions == OPTION_DO_SCALE) {
				place = scaleOnOurSide() ? AutoPlace::SCALE_NEAR : AutoPlace::BASELINE;
			} else if (autoInstructions == OPTION_DO_BASELINE) {
				place = AutoPlace::BASELINE;
			} else {
				place = AutoPlace::BASELINE;
				DriverStation::ReportError(
						"BADBADBAD CASE DOESNT EXIST FOR NON EASY AUTO OPTIONS CHECK WITH PROGRAMMING error:2 AutoSequence.cpp");
			}
			if (!Robot::cob->GetAutonomousEnableCrossing() && (place == AutoPlace::SCALE_FAR || place == AutoPlace::SWITCH_FAR)) {
				place = AutoPlace::BASELINE;
			}
			if (place == AutoPlace::SWITCH_NEAR) {
				DriverStation::ReportError("Doing switch near");
				DoSwitchNear();
			} else if (place == AutoPlace::SWITCH_FAR) {
				DriverStation::ReportError("Doing baseline");
				DoBaseline();
			} else if (place == AutoPlace::SCALE_NEAR) {
				DriverStation::ReportError("Doing scale near");
				DoScaleNear();
			} else if (place == AutoPlace::SCALE_FAR) {
				DriverStation::ReportError("Doing baseline");
				DoBaseline();
			} else if (place == AutoPlace::BASELINE) {
				DriverStation::ReportError("Doing baseline");
				DoBaseline();
			} else {
				DriverStation::ReportError("Doing baseline");
				DoBaseline();
				DriverStation::ReportError("BADBADBAD UNKNOWN PLACE CASE FOR NOT DO EASY error:3 AutoSequence.cpp");
			}
		}
	}
}

void AutoSequence::releaseShaft() {
	AddParallel(new ReleaseShaft());
}

void AutoSequence::RaiseElevatorToSwitch() {
	AddParallel(new SetShaftSetpointAuto(ELEVATOR_SWITCH, 3));
}

void AutoSequence::RaiseElevatorToScale() {
	AddParallel(new SetShaftSetpointAuto(ELEVATOR_SCALE, 3));
}

void AutoSequence::DropCube() {
	AddSequential(new CubeIntakeCommand(false, 0.5));
	WAIT_SEC(CUBE_EJECT_WAIT_TIME);
}

void AutoSequence::TestBumpDetection() {
	DriverStation::ReportError("Testing Bump Detection...");
	AddSequential(new DistanceDrive(20, FAST_SPEED, TIMEOUT, false, true));
	WAIT
}

void AutoSequence::TestPIDTurn() {
	DriverStation::ReportError("Testing PID Turning...");
	AddSequential(new Turn(90, TIMEOUT));
	WAIT_SEC(2.0);
	AddSequential(new Turn(-90, TIMEOUT));
}

/**
 * Called when we want to deposit a cube on the same side of the switch that we are starting on.
 * This function is only to be used when we are starting on the outside.
 */
void AutoSequence::DoSwitchNear() {
	DriverStation::ReportError("Doing Switch Near...");
	//Go forward to the switch, then turn toward the inside of the field, then move in, drop cube, move back,\a
	//strafe toward the center, rotate and setup for teleop
	AddSequential(
			new DistanceDrive(DISTANCE_TO_SWITCH - HALF_ROBOT_LENGTH - 12 - 6 - 24 - 24/*For forward drive in init*/, SPEED,
					TIMEOUT, false, false)); //SUBTRACTED ONE FOOT
	WAIT
	RaiseElevatorToSwitch();
	WAIT
	AddSequential(new Turn(invertIfRight(90), TURN_TIMEOUT));
	WAIT

	//WAIT
	AddSequential(new DistanceDrive(1.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	DropCube();
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	if (Robot::cob->GetAutonomousEnableCrossing()) {
		AddSequential(new DistanceDrive(invertIfRight(-6 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
		AddSequential(new Turn(invertIfRight(180), TURN_TIMEOUT));
		WAIT
		AddSequential(new DistanceDrive(invertIfRight(-4 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
	}
}

/**
 * Called when we want to deposit a cube on the opposite side of the switch than we are starting on.
 * This function is only to be used when we are starting on the outside.
 */
void AutoSequence::DoSwitchFar() {
	DriverStation::ReportError("Doing Switch Far (Baseline)");
	DoBaseline();
	//AddSequential(new DistanceDrive(DISTANCE_TO_SWITCH + (3 * FEET_TO_INCHES) - HALF_ROBOT_WIDTH, FAST_SPEED, TIMEOUT));
	//WAIT
	//AddSequential(new DistanceDrive(invertIfRight(20 * FEET_TO_INCHES - HALF_ROBOT_WIDTH), FAST_SPEED, TIMEOUT, true));
	//WAIT
	//RaiseElevatorToSwitch();
	//WAIT
	//AddSequential(new Turn(180, TIMEOUT));
	//WAIT
	//DropCube();
}

/**
 * Called when we want to deposit a cube on the same side of the scale that we are starting on.
 * This function is only to be used when we are starting on the outside.
 */
void AutoSequence::DoScaleNear() {
	DriverStation::ReportError("Doing Scale Near...");
	AddSequential(new DistanceDrive(18 * FEET_TO_INCHES, 0.7 * 0.5, TIMEOUT, false, false));
	RaiseElevatorToSwitch();
	//Can we raise here? Or after we detect the bump on the next line
	AddSequential(
			new DistanceDrive(10 * FEET_TO_INCHES/*For forward drive in init*/, SPEED * 0.5, TIMEOUT, false, true,
					27 * FEET_TO_INCHES - HALF_ROBOT_LENGTH));
	//strafe
	AddSequential(new DistanceDrive(invertIfRight(-10), SPEED * 0.5, TIMEOUT, true, false));
	WAIT
	//turn
	RaiseElevatorToScale();
	AddSequential(new Turn(invertIfRight(90), 1));
	//drive forward
	AddSequential(new DistanceDrive(1 * FEET_TO_INCHES, FAST_SPEED, TIMEOUT));
	//dropping cube
	WAIT_SEC(1.0)
	DropCube();
	AddSequential(new DistanceDrive(-3.0 * FEET_TO_INCHES, FAST_SPEED, TIMEOUT));
	WAIT
	RaiseElevatorToSwitch();
	WAIT
	/*
	 //move back
	 //WAIT
	 //turn
	 AddSequential(new Turn(invertIfRight(180), TIMEOUT));
	 WAIT
	 //drive back
	 AddSequential(new DistanceDrive(6 * FEET_TO_INCHES, FAST_SPEED, TIMEOUT, false, false));
	 //WAIT
	 if (Robot::cob->GetAutonomousEnableCrossing()) {
	 //AddSequential(new DistanceDrive(invertIfRight(-6 * FEET_TO_INCHES), SPEED, TIMEOUT, false));
	 //WAIT
	 //AddSequential(new Turn(invertIfRight(180), TIMEOUT, SPEED));
	 //WAIT
	 AddSequential(new DistanceDrive(invertIfRight(-4 * FEET_TO_INCHES), FAST_SPEED, TIMEOUT, true));
	 }
	 */

}

/**
 * Called when we want to deposit a cube on the opposite side of the scale than we are starting on.
 * This function is only to be used when we are starting on the outside.
 */
void AutoSequence::DoScaleFar() {
	/*
	 DriverStation::ReportError("Doing Scale Far...");
	 AddSequential(new DistanceDrive(20 * FEET_TO_INCHES - HALF_ROBOT_WIDTH, FAST_SPEED, TIMEOUT));
	 WAIT
	 AddSequential(new DistanceDrive(invertIfRight(14 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
	 WAIT
	 AddSequential(new DistanceDrive(0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	 WAIT
	 RaiseElevatorToScale();
	 WAIT
	 DropCube(); //to be implemented later
	 */
	DoBaseline();
}

/**
 * This function drives the robot across the autoline, and sets it up for picking up cubes if we are in the center
 */
void AutoSequence::DoBaseline() {
	DriverStation::ReportError("Doing Baseline...");
	releaseShaft();
	if (isCenterStart()) {
		AddSequential(new DistanceDrive(2 * FEET_TO_INCHES, SPEED, TIMEOUT, true));	//Go right 2 feet
		//WAIT
		AddSequential(new DistanceDrive(10 * FEET_TO_INCHES, SPEED, TIMEOUT));	//drive forward to break the auto line
		//WAIT
		AddSequential(new DistanceDrive(-6 * FEET_TO_INCHES, SPEED, TIMEOUT));//drive back towards the start but stop 4 feet out from the wall
		//WAIT
		AddSequential(new DistanceDrive(2 * FEET_TO_INCHES, SPEED, TIMEOUT, true));	//Go right 2 feet
		//We should be in front of the cubes
	} else {	//If we are on the outside
		//Just drive across since there are no blocks to pervent our passage
		AddSequential(new DistanceDrive(10 * FEET_TO_INCHES, SPEED, TIMEOUT));
	}
}

void AutoSequence::DoCenter() {
	DriverStation::ReportError("Doing Center...");
	double turnAngle = switchOnRight() ? DRIVE_ANGLE_RIGHT + 10 : -(DRIVE_ANGLE_LEFT + 15);
	double driveTime = switchOnRight() ? 2.3 : 2.5;
	DriverStation::ReportError(std::to_string(turnAngle));
	WAIT_SEC(Robot::cob->GetAutonomousInstructions());//In this case, because we are in the center, the auto instructions contain the timeout
	//AddSequential(new AngledDistanceDrive(4, SPEED, turnAngle));
	if (true) {	//Use ticks
		AddSequential(new AngledDistanceDrive(driveTime, 0.5, turnAngle));
		//AddSequential(new DistanceDrive(5 * FEET_TO_INCHES, SPEED, TIMEOUT));
		/*double distance = (switchOnRight())? ((HALF_SWITCH_LENGTH - 25) - (HALF_ROBOT_WIDTH - 12)) : -((HALF_SWITCH_LENGTH - 25) - (HALF_ROBOT_WIDTH + 12));
		 WAIT
		 DriverStation::ReportError("Distance : " + std::to_string(distance));
		 AddSequential(new VisionDrive(0.3, TIMEOUT));
		 //AddSequential(new DistanceDrive(distance * FEET_TO_INCHES * STRAFE_SCALAR, SPEED, TIMEOUT, true));
		 WAIT
		 AddSequential(new DistanceDrive(5 * FEET_TO_INCHES, SPEED, TIMEOUT));
		 //DriverStation::ReportError("Starting Vision Drive");
		 */
		//WAIT
		AddSequential(new Turn(0.0, 1.0));
		//WAIT
		AddSequential(new VisionDrive(0.3, 2.5));
		AddSequential(new VisionDrive(0.3, 2.5));
		WAIT_SEC(0.15);
		AddSequential(new VisionDrive(0.3, 2.5));
		WAIT_SEC(0.15);
		AddSequential(new VisionDrive(0.3, 2.5));
		AddSequential(new VisionDrive(0.3, 2.5));
		AddSequential(new VisionDrive(0.3, 2.5));
		AddSequential(new VisionDrive(0.3, 2.5));
		//AddSequential(new DistanceDrive(2.0 * FEET_TO_INCHES, SPEED, 2.0));
		//RaiseElevatorToSwitch();

		DropCube();
	} else {		//Use vision
		AddSequential(new AngledDistanceDrive(4, 0.5, turnAngle));
		RaiseElevatorToSwitch();
		WAIT_SEC(1);
		DropCube();
		//AddSequential(new VisionDrive(SPEED, TIMEOUT, 100, 98));
		//Vision stuff
	}

	//Go back but more sharply so that we arrive not at the wall, but in front of the cubes
	AddSequential(new DistanceDrive(-4.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	WAIT
	if (switchOnRight()) {
		AddSequential(new DistanceDrive(-4.5 * FEET_TO_INCHES, SPEED, TIMEOUT, true, false));
	} else {
		AddSequential(new DistanceDrive(6 * FEET_TO_INCHES, SPEED, TIMEOUT, true, false));
	}

}
