#pragma once

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "WPILib.h"
#include "ahrs.h"
#include "ctre/Phoenix.h"
#include "../RobotMap.h"
#include "Math.h"
#include <iostream>
#include "cmath"
#include "../RobotConstants.h"

class VisionDrive : public frc::Command , public frc::PIDOutput {
public:
	VisionDrive(int timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void PIDWrite(double);

	double getMaxTicks();
	int getPosition();

private:
	double GetVisionTargetDriveAngle(double x1, double x2);
	double GetVisionTargetDriveDistance(double y1, double y2);

private:
	Timer *m_timer;
	double m_distanceToTarget = 0.0;
	double m_speed = 0.0;
	double m_currentAngle = 0.0;
	int m_timeout;
};
