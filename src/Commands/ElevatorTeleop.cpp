/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ElevatorTeleop.h"
#include "../Robot.h"

ElevatorTeleop::ElevatorTeleop() {
	currentSpike.reset(new CurrentSpikeIndicator(30, RobotMap::shaftController));
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void ElevatorTeleop::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorTeleop::Execute() {
	currentSpike->Update();
	bool hitSpike = currentSpike->GetSpike();
	OI* oi = Robot::oi.get();
	if(oi->useSlider) {//Read from the joystick
		double slider = Robot::oi->GetButtonBoard()->GetRawAxis(0);
		if(oi->usePot) {//Use pid
			double m_setpoint = map(slider, -1, +1, ELEVATOR_BOTTOM, ELEVATOR_TOP);
			Robot::elevator->SetSetpoint(m_setpoint);
		} else {//Use maunal control
			RobotMap::shaftController->Set(slider);
		}
	} else {//Do nothing
		//DriverStation::ReportError("Doing nothing");
	}
	double slider = Robot::oi->GetButtonBoard()->GetRawAxis(0);
	double m_setpoint = map(slider, -1, +1, ELEVATOR_BOTTOM, ELEVATOR_TOP);
	Robot::elevator->SetSetpoint(m_setpoint);
	//DriverStation::ReportError(std::to_string(m_setpoint));
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorTeleop::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ElevatorTeleop::End() {
	DriverStation::ReportError("Ending ElevatorTeleop");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorTeleop::Interrupted() {
	End();
}
