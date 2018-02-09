#ifndef DistanceDrive_H
#define DistanceDrive_H

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

class DistanceDrive : public frc::Command , public frc::PIDOutput {
public:
	DistanceDrive(double, double, int, bool = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void PIDWrite(double);

	double getMaxTicks();
	int getPosition();
private:
	Timer *m_timer;
	PIDController *turnController;
	double m_distance = 0.0;
	double m_speed = 0.0;
	int m_timeout;
	int initEncPosition = 0;
	bool m_strafe;
	double rotateToAngleRate;
};

#endif  // DistanceDrive_H
