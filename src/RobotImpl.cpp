#include "RobotImpl.h"

RobotImpl::RobotImpl(bool rightSwitch, bool rightScale, int startSide, Location startLocation)
: rightSwitch(rightSwitch), rightScale(rightScale), startSide(startSide), startLocation(startLocation)
{}

// Returns the location that represents our starting position
Location& RobotImpl::getStartingLocation() {
	return startLocation;
}

// Returns a path of points to the side of the scale we own based on the robot's current location as identified by the parameter start
Path& RobotImpl::getScaleLocation(Location& start) {
	//TODO
	Location location{1,2};
	Path path(location);
	return path;
}

// Returns a path of points to the switch of the scale we own based on the robot's current location as identified by the parameter start
Path& RobotImpl::getSwitchLocation(Location& start) {
	//TODO
	Location location{1,2};
	Path path(location);
	return path;
}

/*
 * Returns true if we are on the same side as the side of the scale we own.
 * This method will only return true when there is a straight shot to the scale.
 * Always returns false for center starts.
 */
bool RobotImpl::weOwnScale() {
	return (rightScale && startSide == SIDE_RIGHT) || (!rightScale && startSide == SIDE_LEFT);
}

/*
 * Returns true if we are on the same side as the side of the switch we own.
 * This method will only return true when there is a straight shot to the switch.
 * Always returns false for center starts.
 */
bool RobotImpl::weOwnSwitch() {
	return (rightSwitch && startSide == SIDE_RIGHT) || (!rightSwitch && startSide == SIDE_LEFT);
}

// Returns true if we are starting in the center.
bool RobotImpl::isCenterStart() {
	return startSide == 2;
}

//Returns either 1, 2, or 3 depending on where we are starting.
int RobotImpl::getStart() {
	return startSide;
}

bool RobotImpl::canAllianceDoScale() {
	//TODO
}

