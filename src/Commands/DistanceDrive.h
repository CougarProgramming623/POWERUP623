#ifndef DistanceDrive_H
#define DistanceDrive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class DistanceDrive : public frc::Command {
public:
	DistanceDrive(double, double, int);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double getDriveDistance();
private:
	Timer *resetTimer;
	PIDController *turnController;
	int initEncPosition = 0.0;
	double m_speed;
	double m_distance = 0.0;
	int timeout;
};

#endif  // DistanceDrive_H
