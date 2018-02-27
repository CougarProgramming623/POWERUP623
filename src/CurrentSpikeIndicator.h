/*
 * CurrentSpikeIndicator.h
 *
 *  Created on: Feb 25, 2018
 *      Author: frc623
 */

#ifndef SRC_CURRENTSPIKEINDICATOR_H_
#define SRC_CURRENTSPIKEINDICATOR_H_

#include "WPILib.h"
#include "ctre/Phoenix.h"
#define ARRAY_SIZE 10
class CurrentSpikeIndicator {

private:
	double currentArray [ARRAY_SIZE];
	double threshold;
	int index = 0;
	int counter;
	std::shared_ptr<WPI_TalonSRX> talon;

public:
	CurrentSpikeIndicator(double, std::shared_ptr<WPI_TalonSRX>);
	void Update();
	bool GetSpike();
	void Reset();
	void ChangeThreshold(double);
};

#endif /* SRC_CURRENTSPIKEINDICATOR_H_ */
