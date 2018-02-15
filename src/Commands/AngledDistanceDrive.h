#ifndef AngledDistanceDrive_H
#define AngledDistanceDrive_H

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

class AngledDistanceDrive : public frc::Command , public frc::PIDOutput {
public:
	AngledDistanceDrive(double, double, int, double = 0);
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
	double m_angle = 0.0;
	int m_timeout;
	int initEncPosition = 0, m_ticks;
	bool m_strafe;
	double rotateToAngleRate;
};

#endif  // DistanceDrive_H
