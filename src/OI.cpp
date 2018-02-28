// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/Drive/DriveWithJoystick.h"
#include "Commands/TeleOp/CubeIntakeCommand.h"
#include "Commands/TeleOp/ToggleSliderUsage.h"
#include <iostream>
#include "Commands/SetShaftSetpointAuto.h"
#include "Commands/ReleaseRamp.h"
#include "Commands/ReleaseShaft.h"

OI::OI() {
	driverJoystick.reset(new frc::Joystick(0));
	buttonBoard.reset(new frc::Joystick(1));

	toggleSliderControl.reset(new frc::JoystickButton(buttonBoard.get(), 3));
	expungeButton.reset(new frc::JoystickButton(buttonBoard.get(), 5));
	intakeButton.reset(new frc::JoystickButton(buttonBoard.get(), 6));
	releaseShaftButton.reset(new frc::JoystickButton(buttonBoard.get(), 1));
	releaseRampButton.reset(new frc::JoystickButton(buttonBoard.get(), 2));


	toggleSliderControl->WhenPressed(new ToggleSliderUsage());

	expungeButton->WhileHeld(new CubeIntakeCommand(false, 0));
	intakeButton->WhileHeld(new CubeIntakeCommand(true, 0));

	releaseShaftButton->WhenPressed(new ReleaseShaft());
	releaseRampButton->WhenPressed(new ReleaseRamp());
}

std::shared_ptr<frc::Joystick> OI::GetDriverJoystick() {
	return driverJoystick;
}

std::shared_ptr<frc::Joystick> OI::GetButtonBoard() {
	return buttonBoard;
}

