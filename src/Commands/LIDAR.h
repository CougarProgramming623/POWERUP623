/*
 * LIDAR.h
 *
 *  Created on: Mar 11, 2018
 *      Author: frc623
 */

#ifndef LIDAR_H_
#define LIDAR_H_
#include "WPILib.h"
#include "../RobotConstants.h"

class LIDAR {

private:
	std::shared_ptr<frc::SerialPort> sp;

public:
	LIDAR();
	double GetDistance();
	void Update();
private:
	double stored;
};

#endif /* LIDAR_H_ */
