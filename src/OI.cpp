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
#include "Commands/DriveWithJoystick.h"
#include "Commands/SetShaftSetpoint.h"
#include "Commands/CubeIntakeCommand.h"
#include <iostream>

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driverJoystick.reset(new frc::Joystick(0));
    buttonBoard.reset(new frc::Joystick(1));
    elevatorUp.reset(new frc::JoystickButton(buttonBoard.get(), 1));
    elevatorDown.reset(new frc::JoystickButton(buttonBoard.get(), 2));
    expungeButton.reset(new frc::JoystickButton(buttonBoard.get(), 5));
    intakeButton.reset(new frc::JoystickButton(buttonBoard.get(), 6));

    elevatorUp->WhileHeld(new SetShaftSetpoint(true));
    elevatorDown->WhileHeld(new SetShaftSetpoint(false));

    expungeButton->WhileHeld(new CubeIntakeCommand(false));
    intakeButton->WhileHeld(new CubeIntakeCommand(true));

    // SmartDashboard Buttons
    //frc::SmartDashboard::PutData("DriveWithJoystick", new DriveWithJoystick());
    //frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getdriverJoystick() {
   return driverJoystick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
