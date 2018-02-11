#pragma once

#include "Location.h"
#include "Path.h"
#include "RobotConstants.h"

class RobotImpl {
private:
	bool rightSwitch, rightScale;
	int startSide;
	Location startLocation;
public:
	RobotImpl(bool rightSwitch, bool rightScale, int startSide, Location startLocation);

	// Returns the location that represents our starting position
	Location& getStartingLocation();

	// Returns a path of points to the side of the scale we own based on the robot's current location as identified by the parameter start
	Path& getScaleLocation(Location& start);

	// Returns a path of points to the switch of the scale we own based on the robot's current location as identified by the parameter start
	Path& getSwitchLocation(Location& start);

	/*
	 * Returns true if we are on the same side as the side of the scale we own.
	 * This method will only return true when there is a straight shot to the scale.
	 * Always returns false for center starts.
	 */
	bool weOwnScale();

	/*
	 * Returns true if we are on the same side as the side of the switch we own.
	 * This method will only return true when there is a straight shot to the switch.
	 * Always returns false for center starts.
	 */
	bool weOwnSwitch();

	bool switchOnOurSide();
	bool scaleOnOurSide();

	bool switchOnRight();

	bool scaleOnRight();

	// Returns true if we are starting in the center.
	bool isCenterStart();

	//Returns either 1, 2, or 3 depending on where we are starting.
	int getStart();

	bool canAllianceDoSwitch();


};
