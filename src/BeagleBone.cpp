/*
 * BeagleBone.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: frc623
 */

#include "BeagleBone.h"
#include "networktables/NetworkTableInstance.h"
#include "Robot.h"
using namespace nt;

std::shared_ptr<NetworkTable> BeagleBone::bbTable;
nt::NetworkTableEntry BeagleBone::entryColor;
nt::NetworkTableEntry BeagleBone::entryShutdown;

BeagleBone::BeagleBone() {
	// TODO Auto-generated constructor stub
	auto inst = NetworkTableInstance::GetDefault();
	BeagleBone::bbTable = inst.GetTable("beaglebone");
	BeagleBone::entryColor = bbTable->GetEntry("color entry");
	BeagleBone::entryShutdown = bbTable->GetEntry("shutdown");

}

void BeagleBone::InitBeagleBoneTable() {
	auto inst = NetworkTableInstance::GetDefault();
	BeagleBone::bbTable = inst.GetTable("beaglebone");
	BeagleBone::entryColor = bbTable->GetEntry("color entry");
	BeagleBone::entryShutdown = bbTable->GetEntry("shutdown");
}

void BeagleBone::PushColorEntry(frc::DriverStation::Alliance color) {
	if(color == frc::DriverStation::Alliance::kRed)
		entryColor.SetString("red");
	else if(color == frc::DriverStation::Alliance::kBlue)
		entryColor.SetString("blue");
	else
		entryColor.SetString("NO COLOR ASSIGNED WHERE ARE WE?");
}

void BeagleBone::PushShutdown(bool isShutdown) {
	entryShutdown.SetBoolean(isShutdown);
}

/*
int BeagleBone::GetColorEntry() {
	if(entryColor.Exists())
		return (int)entryColor.GetValue().get()->GetDouble();

	return -1;
}
*/

bool BeagleBone::isShutdown() {
	if(entryShutdown.Exists())
		return (bool)entryShutdown.GetValue().get()->GetBoolean();

	return false;
}





