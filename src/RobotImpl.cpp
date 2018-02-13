#include "RobotImpl.h"

RobotImpl::RobotImpl() {
}


// Returns a path of points to the side of the scale we own based on the robot's current location as identified by the parameter start
Path& RobotImpl::getScaleLocation(Location& start) {
	//TODO
	Location location { 1, 2 };
	Path path(location);
	return path;
}

bool RobotImpl::switchOnOurSide() {
	return (switchOnRight() && (startSide == SIDE_RIGHT)) || (!switchOnRight() && (startSide == SIDE_LEFT));
}

bool RobotImpl::scaleOnOurSide() {
	return (scaleOnRight() && (startSide == SIDE_RIGHT)) || (!scaleOnRight() && (startSide == SIDE_LEFT));
}

void RobotImpl::CheckFMS() {
	if (fmsData == nullptr) {
		//Get data
		fmsData = new std::string(DriverStation::GetInstance().GetGameSpecificMessage());
		DriverStation::ReportError("Geting data!");
		DriverStation::ReportError(*fmsData);
	}
}

bool RobotImpl::switchOnRight() {
	CheckFMS();
	return (*fmsData)[0] == 'R';
}

bool RobotImpl::scaleOnRight() {
	CheckFMS();
	return (*fmsData)[1] == 'R';
}

// Returns a path of points to the switch of the scale we own based on the robot's current location as identified by the parameter start
Path& RobotImpl::getSwitchLocation(Location& start) {
	//TODO
	Location location { 1, 2 };
	Path path(location);
	return path;
}

/*
 * Returns true if we are on the same side as the side of the scale we own.
 * This method will only return true when there is a straight shot to the scale.
 * Always returns false for center starts.
 */
bool RobotImpl::weOwnScale() {
	return (switchOnRight() && startSide == SIDE_RIGHT) || (!switchOnRight() && startSide == SIDE_LEFT);
}

/*
 * Returns true if we are on the same side as the side of the switch we own.
 * This method will only return true when there is a straight shot to the switch.
 * Always returns false for center starts.
 */
bool RobotImpl::weOwnSwitch() {
	return (scaleOnRight() && startSide == SIDE_RIGHT) || (!scaleOnRight() && startSide == SIDE_LEFT);
}

// Returns true if we are starting in the center.
bool RobotImpl::isCenterStart() {
	return startSide == SIDE_CENTER;
}

//Returns either 1, 2, or 3 depending on where we are starting.
int RobotImpl::getStart() {
	return startSide;
}

bool RobotImpl::canAllianceDoSwitch() {
	//TODO
	return false;
}

