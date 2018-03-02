/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ToggleSliderUsage.h"
#include "../../Robot.h"

ToggleSliderUsage::ToggleSliderUsage() {
}

// Called just before this Command runs the first time
void ToggleSliderUsage::Initialize() {
	OI* oi = Robot::oi.get();
	oi->useSlider = !oi->useSlider;
	if(!oi->useSlider) {
		oi->GetButtonBoard()->SetOutput(4, true);
		Robot::elevator->enablePID(false);
	} else {
		oi->GetButtonBoard()->SetOutput(4, false);
		Robot::elevator->enablePID(true);
	}
}

// Called repeatedly when this Command is scheduled to run
void ToggleSliderUsage::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ToggleSliderUsage::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ToggleSliderUsage::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleSliderUsage::Interrupted() {

}
