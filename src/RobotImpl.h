#pragma once

#include "RobotConstants.h"
#include "WPILib.h"
#include "string"

class RobotImpl {
private:
	std::string* fmsData = nullptr;
	int startSide;
public:
	RobotImpl();

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

	//Returns either 0 1, or 2 depending on where we are starting.
	int getStart();
private:
	void CheckFMS();

};
