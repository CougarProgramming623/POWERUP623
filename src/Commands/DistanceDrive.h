#ifndef DistanceDrive_H
#define DistanceDrive_H

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "WPILib.h"

class DistanceDrive : public frc::Command {
public:
	DistanceDrive(double, double, int);
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
	double rotateToAngleRate;
};

#endif  // DistanceDrive_H
