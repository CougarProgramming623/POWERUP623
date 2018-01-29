#ifndef Turn_H
#define Turn_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../RobotMap.h"
#include "../Robot.h"

class Turn : public frc::Command, frc::PIDOutput {
public:
	Turn(double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void PIDWrite (double output);
private:
	PIDController *turnController;
	Timer *m_timer;
	double rotateToAngleRate;
	double m_angle = 0.0;
	double initialAngle;

};

#endif  // Turn_H
