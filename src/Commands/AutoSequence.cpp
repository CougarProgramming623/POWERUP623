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

#define inveretIfRight(x) getStart() == SIDE_RIGHT ? -x : x

#define WAIT_SEC(x) AddSequential(new WaitCommand(x));
#define WAIT WAIT_SEC(0.35)

AutoSequence::AutoSequence() :
		frc::CommandGroup(), RobotImpl() {

	RobotMap::ahrs->ZeroYaw();		//reset gyro degrees
	DriverStation::GetInstance();
	if (isCenterStart()) {
		double turnAngle = scaleOnRight() ? 55 : 135;
		DriverStation::ReportError("doing correct!");
		AddSequential(new AngledDistanceDrive(10 * FEET_TO_INCHES, 0.5, 5, turnAngle));
		//drop block
	} else {		//On left or right
		DriverStation::ReportError("WRONGWRONGWRONGWRONG");
		if (!canAllianceDoSwitch()) {		//Do switch
			doSwitch();
		} else {
			if (scaleOnOurSide()) {
				doScale();
			} else {
				//Were screwed
			}
		}
	}

}

void AutoSequence::doScale() {
	AddSequential(new DistanceDrive(DISTANCE_TO_SCALE - HALF_ROBOT_WIDTH, FAST_SPEED, TIMEOUT));
	WAIT
	AddSequential(new Turn(inveretIfRight(90), TIMEOUT, SPEED));
	WAIT
	AddSequential(new DistanceDrive(1 * FEET_TO_INCHES, SPEED, TIMEOUT));
	DriverStation::ReportError("Dropping cube!");
	WAIT_SEC(1.0)
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	AddSequential(new DistanceDrive(inveretIfRight(6 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
}

void AutoSequence::doSwitch() {
	AddSequential(new DistanceDrive(DISTANCE_TO_SWITCH - HALF_ROBOT_WIDTH, SPEED, TIMEOUT));
	WAIT

	AddSequential(new Turn(inveretIfRight(90), TIMEOUT, SPEED));
	WAIT
	AddSequential(new DistanceDrive(1.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	DriverStation::ReportError("Dropping cube!");
	WAIT_SEC(1.0)
	AddSequential(new DistanceDrive(-0.5 * FEET_TO_INCHES, SPEED, TIMEOUT));
	WAIT

	AddSequential(new DistanceDrive(inveretIfRight(-6 * FEET_TO_INCHES), SPEED, TIMEOUT, true));
	WAIT
	AddSequential(new Turn(inveretIfRight(90), TIMEOUT, SPEED));
	WAIT

	AddSequential(new DistanceDrive(inveretIfRight(-4 * FEET_TO_INCHES), SPEED, TIMEOUT, true));

}

