/*
 * CubeIntake.h
 *
 *  Created on: Feb 23, 2018
 *      Author: frc623
 */

#ifndef CUBEINTAKE_H_
#define CUBEINTAKE_H_
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"

class CubeIntake: public frc::Subsystem {

private:
	std::shared_ptr<WPI_TalonSRX> cubeIntake;
	std::shared_ptr<WPI_TalonSRX> cubeIntake2;
public:
	CubeIntake();
	void InitDefaultCommand() override;
	void Periodic() override;
	void Intake();
	void Expunge();
	void Stop();
	double GetCurrent();
};

#endif /* SRC_SUBSYSTEMS_CUBEINTAKE_H_ */
