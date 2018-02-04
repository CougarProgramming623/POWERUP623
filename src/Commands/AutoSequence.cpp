#include "AutoSequence.h"
#include "DistanceDrive.h"
#include "Turn.h"
#include "../Robot.h"

#define DISTANCE 14.0 * 12
#define SPEED 0.75
#define TIMEOUT 10

AutoSequence::AutoSequence() : frc::CommandGroup() {
	AddSequential(new DistanceDrive(DISTANCE, SPEED, TIMEOUT));
	AddSequential(new Turn(90.0f));

	/*
	 if(Robot::impl->isCenterStart()) {
		AddSequential(new DistanceDrive(12, 1.0, 3));
		AddSequential(new Turn((Robot::impl->switchOnRight() ? -1 : +1) * 15.0));
		AddSequential(new DistanceDrive(12, 1.0, 3));
	 } else {

	 }
	 */
}

