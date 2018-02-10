#include "AutoSequence.h"
#include "DistanceDrive.h"
#include "Turn.h"
#include "../Robot.h"

#define DISTANCE 14.0 * 12
#define SPEED 0.75
#define TIMEOUT 10
#define W(x) Wait(0.05);

AutoSequence::AutoSequence() :
		frc::CommandGroup(), RobotImpl(true, true, SIDE_LEFT, Location{1,2}){
	//AddSequential(new DistanceDrive(DISTANCE, SPEED, TIMEOUT));
	//AddSequential(new Turn(90.0f));

	//try catch block is copy-paste from DriveWithJoystick initialization
	RobotMap::ahrs->ZeroYaw();		//reset gyro degrees

	//note: I've basically hard coded everything for testing purposes here


	if (isCenterStart()) {
		//note: the robot can just move in direction with angle

		//angle is used for testing right now, angle will change after we calculate
		double turnAngle = 15;
		if (switchOnRight()) {
			turnAngle = -1 * turnAngle;
		}

		AddSequential(new Turn(turnAngle));
		//change to Cartesian drive with angle after
		AddSequential(new DistanceDrive(10 * 12, 0.5, 1.5));		//values just for testing
		AddSequential(new Turn(-1 * turnAngle));
		//drop block here
	} else {
		AddSequential(new DistanceDrive(10 * 12, 0.5, 1.3));		//values just for testing
		if (weOwnSwitch()) {
			AddSequential(new Turn(((getStart() == SIDE_RIGHT) ? +1 : -1) * 90));
			//drop block
		} else {

		}
	}

}

