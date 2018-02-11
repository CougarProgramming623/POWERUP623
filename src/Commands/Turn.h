#ifndef Turn_H
#define Turn_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "AHRS.h"
#include "../RobotConstants.h"

class Turn : public frc::Command, public frc::PIDOutput {
public:
	Turn(double, double, double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void PIDWrite(double);
private:
	PIDController *turnController;
	Timer *m_timer;
	double rotateToAngleRate;
	double m_angle = 0.0;
	double m_timeout;
	double m_speed;
};

#endif  // Turn_H
