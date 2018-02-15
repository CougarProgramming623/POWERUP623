#include "AutoSequence.h"

#define FEET_TO_INCHES 12

//12 feet to the front plus half of its width for the center
#define DISTANCE_TO_SWITCH (12.0 * FEET_TO_INCHES + (2.0 * FEET_TO_INCHES) / 2.0)
#define DISTANCE_TO_SCALE (27.0 * FEET_TO_INCHES)
#define HALF_ROBOT_WIDTH (ROBOT_WIDTH / 2.0)

#define TURN_SPEED 1.0
#define SPEED 0.45
#define FAST_SPEED 0.6
#define TIMEOUT 10

#define invertIfRight(x) getStart() == SIDE_RIGHT ? -x : x

#define WAIT_SEC(x) AddSequential(new WaitCommand(x));
#define WAIT WAIT_SEC(0.35)

AutoSequence::AutoSequence() :
		frc::CommandGroup(), RobotImpl() {

	RobotMap::ahrs->ZeroYaw();		//reset gyro degrees
	DriverStation::GetInstance();
	if (isCenterStart()) {
		double turnAngle = scaleOnRight() ? 55 : 135;
		DriverStation::ReportError("doing correct!");
		AddSequential(
				new AngledDistanceDrive(10 * FEET_TO_INCHES, 0.5, 5,
						turnAngle));
	} else {

		if (Robot::cob->GetAutonomousInstructions()
				== CougarOpticBoard::OPTION_DO_EASY) {
			if (switchOnOurSide() && scaleOnOurSide())
				doSwitchNear();
			else if (switchOnOurSide() && !scaleOnOurSide())
				doSwitchNear();
			else if (!switchOnOurSide() && scaleOnOurSide())
				doScaleNear();
			else if (!switchOnOurSide() && !scaleOnOurSide())
				if (!Robot::cob->GetAutonomousDisableCrossing())
					doSwitchFar();
				else
					doBaseline();
		} else {		// Everything except easy
			AutoPlace place;
			if (Robot::cob->GetAutonomousInstructions()
					== CougarOpticBoard::OPTION_DO_SWITCH) {
				place = switchOnOurSide() ?
						AutoPlace::SWITCH_NEAR : AutoPlace::SWITCH_FAR;
			} else if (Robot::cob->GetAutonomousInstructions()
					== CougarOpticBoard::OPTION_DO_SCALE) {
				place = scaleOnOurSide() ?
						AutoPlace::SCALE_NEAR : AutoPlace::SCALE_FAR;
			} else if (Robot::cob->GetAutonomousInstructions()
					== CougarOpticBoard::OPTION_DO_BASELINE) {
				place = AutoPlace::BASELINE;
			} else {
				DriverStation::ReportError(
						"BADBADBAD CASE DOESNT EXIST FOR AUTO OPTIONS CHECK WITH PROGRAMMING AutoSequence.cpp");
			}
			if (Robot::cob->GetAutonomousDisableCrossing()
					&& (place == AutoPlace::SCALE_FAR
							|| place == AutoPlace::SWITCH_FAR)) {
				place = AutoPlace::BASELINE;
			}
			if (place == AutoPlace::SWITCH_NEAR)
				doSwitchNear();
			else if (place == AutoPlace::SWITCH_FAR)
				doSwitchFar();
			else if (place == AutoPlace::SCALE_NEAR)
				doScaleNear();
			else if (place == AutoPlace::SCALE_FAR)
				doScaleFar();
			else if (place == AutoPlace::BASELINE)
				doBaseline();
			else
				DriverStation::ReportError(
						"BADBADBAD UNKNOWN PLACE CASE AutoSequence.cpp");

		}

	}
}

void AutoSequence::doSwitchNear() {
	AddSequential(
			new DistanceDrive(DISTANCE_TO_SWITCH - HALF_ROBOT_WIDTH, SPEED,
			TIMEOUT));
	WAIT
	AddSequential(new Turn(invertIfRight(90), TIMEOUT, SPEED));
	WAIT
	AddSequential(new DistanceDrive(1.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	DriverStation::ReportError("Dropping cube!");
	WAIT_SEC(1.0)
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	WAIT

	AddSequential(new DistanceDrive(invertIfRight(-6 * FEET_TO_INCHES), SPEED,
	TIMEOUT, true));
	WAIT
	AddSequential(new Turn(invertIfRight(90), TIMEOUT, SPEED));
	WAIT
	AddSequential(new DistanceDrive(invertIfRight(-4 * FEET_TO_INCHES), SPEED,
	TIMEOUT, true));

}

void AutoSequence::doSwitchFar() {

}

void AutoSequence::doScaleNear() {
	AddSequential(
			new DistanceDrive(DISTANCE_TO_SCALE - HALF_ROBOT_WIDTH, FAST_SPEED,
			TIMEOUT));
	WAIT
	AddSequential(new Turn(invertIfRight(90), TIMEOUT, SPEED));
	WAIT
	AddSequential(new DistanceDrive(1 * FEET_TO_INCHES, SPEED, TIMEOUT));
	DriverStation::ReportError("Dropping cube!");
	WAIT_SEC(1.0)
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	AddSequential(
			new DistanceDrive(invertIfRight(6 * FEET_TO_INCHES), SPEED, TIMEOUT,
					true));
}

void AutoSequence::doScaleFar() {

}

void AutoSequence::doBaseline() {
	if (isCenterStart()) {

	} else {
		AddSequential(new DistanceDrive(6 * FEET_TO_INCHES, SPEED, TIMEOUT));
	}
}

