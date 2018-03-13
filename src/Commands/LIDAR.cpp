/*
 * LIDAR.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: frc623
 */

#include "LIDAR.h"
#include "ctre/Phoenix.h"
#include <iostream>
#include "WPILib.h"

LIDAR::LIDAR() {
	sp.reset(new frc::SerialPort(115200, frc::SerialPort::Port::kMXP, 8, SerialPort::Parity::kParity_None, SerialPort::StopBits::kStopBits_One));
}

int LIDAR::GetDistance() {
	char array [9 * LIDAR_ARR_SIZE];
	int amount = sp->Read(array, 9 * LIDAR_ARR_SIZE);
	int index = -1;
	for (int i = amount - 8; i >= 0; i--)
		if (array[i] == 0x59 && array[i + 1] == 0x59) {
			index = i;
			break;
		}
	if (index == -1)
		return -1;

	//calculate quality
	int quality = array[index + 5];
	quality <<= 8;
	quality += array[index + 4];
	//DriverStation::ReportError("Quality Read" + std::to_string(quality));

	//calculate distance
	int distance = array[index + 3];
	distance <<= 8;
	distance += array[index + 2];
	DriverStation::ReportError("Distance: " + std::to_string(distance * CM_TO_INCHES));
	return distance * CM_TO_INCHES;
}

