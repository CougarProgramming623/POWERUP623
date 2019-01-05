/*
 * BeagleBone.h
 *
 *  Created on: Oct 22, 2018
 *      Author: frc623
 */

#ifndef SRC_BEAGLEBONE_H_
#define SRC_BEAGLEBONE_H_

#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTable.h"
#include "DriverStation.h"


class BeagleBone {
public:
	BeagleBone();

	static std::shared_ptr<NetworkTable> bbTable;

	static void PushColorEntry(frc::DriverStation::Alliance color);
	static void PushShutdown(bool isShutdown);

	static nt::NetworkTableEntry entryColor;
	static nt::NetworkTableEntry entryShutdown;

	static int GetColorEntry();
	static bool isShutdown();

	static void InitBeagleBoneTable();
};


#endif /* SRC_BEAGLEBONE_H_ */
