#include "AutoSequence.h"
#include "DistanceDrive.h"
#include "Turn.h"

AutoSequence::AutoSequence() : frc::CommandGroup() {
	AddSequential(new DistanceDrive(60, 1.0, 5));
	AddSequential(new Turn(90.0f));
	AddSequential(new DistanceDrive(60, 1.0, 5));
	AddSequential(new Turn(-180.0f));
	AddSequential(new DistanceDrive(60, 1.0, 5));
}


