/*
 * CougarOpticBoard.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: Quintin Harter
 */

#include "CougarOpticBoard.h"
#include "networktables/NetworkTableInstance.h"
#include "Robot.h"
using namespace nt;

std::shared_ptr<NetworkTable> CougarOpticBoard::table;
nt::NetworkTableEntry CougarOpticBoard::entryRotation;
nt::NetworkTableEntry CougarOpticBoard::entryPositionX;
nt::NetworkTableEntry CougarOpticBoard::entryPositionY;
nt::NetworkTableEntry CougarOpticBoard::entryVelocityDirection;
nt::NetworkTableEntry CougarOpticBoard::entryVelocityMagnitude;
nt::NetworkTableEntry CougarOpticBoard::entryArmHeight;
nt::NetworkTableEntry CougarOpticBoard::entryArmRotation;
nt::NetworkTableEntry CougarOpticBoard::entryArmCubeGrabbed;
nt::NetworkTableEntry CougarOpticBoard::entryArmClimbStatus;
nt::NetworkTableEntry CougarOpticBoard::entryAutonomousStartPos;
nt::NetworkTableEntry CougarOpticBoard::entryAutonomousNoAuto;
nt::NetworkTableEntry CougarOpticBoard::entryAutonomousInstructions;
nt::NetworkTableEntry CougarOpticBoard::entryAutonomousEnableCrossing;
nt::NetworkTableEntry CougarOpticBoard::entryFMSAlliance;
nt::NetworkTableEntry CougarOpticBoard::entryFMSTime;
nt::NetworkTableEntry CougarOpticBoard::entryFMSField;
nt::NetworkTableEntry CougarOpticBoard::entryIsAutonomous;
nt::NetworkTableEntry CougarOpticBoard::entryIsTeleop;
nt::NetworkTableEntry CougarOpticBoard::entryIsEnabled;
nt::NetworkTableEntry CougarOpticBoard::entryLidar;
nt::NetworkTableEntry CougarOpticBoard::entryUpdate;


/**
 *  The constructor method for the COB.
 *  When called, it instantiates the table and
 *  all (private) network table entries.
 *
 *  @author Quintin Harter
 */
CougarOpticBoard::CougarOpticBoard() {

	CougarOpticBoard::table = NetworkTable::GetTable("cob");

	//place the code to initialize the network table entries here
	CougarOpticBoard::entryRotation = table->GetEntry("rotation");
	CougarOpticBoard::entryPositionX = table->GetEntry("position/x");
	CougarOpticBoard::entryPositionY = table->GetEntry("position/y");
	CougarOpticBoard::entryVelocityDirection = table->GetEntry("velocity/direction");
	CougarOpticBoard::entryVelocityMagnitude = table->GetEntry("velocity/magnitude");
	CougarOpticBoard::entryArmHeight = table->GetEntry("arm/height");
	CougarOpticBoard::entryArmCubeGrabbed = table->GetEntry("arm/cube-grabbed");
	CougarOpticBoard::entryArmClimbStatus = table->GetEntry("arm/climb-status");
	CougarOpticBoard::entryAutonomousStartPos = table->GetEntry("autonomous/side");
	CougarOpticBoard::entryAutonomousNoAuto = table->GetEntry("autonomous/emergency-no-auto");
	CougarOpticBoard::entryAutonomousInstructions = table->GetEntry("autonomous/instructions");
	CougarOpticBoard::entryAutonomousEnableCrossing = table->GetEntry("autonomous/enable-crossing");
	CougarOpticBoard::entryFMSTime = table->GetEntry("fms/time");
	CougarOpticBoard::entryFMSAlliance = table->GetEntry("fms/alliance");
	CougarOpticBoard::entryFMSField = table->GetEntry("fms/field");
	CougarOpticBoard::entryIsAutonomous = table->GetEntry("gamedata/is-autonomous");
	CougarOpticBoard::entryIsTeleop = table->GetEntry("gamedata/is-teleop");
	CougarOpticBoard::entryIsEnabled = table->GetEntry("gamedata/is-enabled");
	CougarOpticBoard::entryLidar = table->GetEntry("lidar");
	CougarOpticBoard::entryUpdate = table->GetEntry("update");

}

void CougarOpticBoard::InitBoard() {
	table = NetworkTable::GetTable("cob");
	//place the code to initialize the network table entries here
	CougarOpticBoard::entryRotation = table->GetEntry("rotation");
	CougarOpticBoard::entryPositionX = table->GetEntry("position/x");
	CougarOpticBoard::entryPositionY = table->GetEntry("position/y");
	CougarOpticBoard::entryVelocityDirection = table->GetEntry("velocity/direction");
	CougarOpticBoard::entryVelocityMagnitude = table->GetEntry("velocity/magnitude");
	CougarOpticBoard::entryArmHeight = table->GetEntry("arm/height");
	CougarOpticBoard::entryArmRotation = table->GetEntry("arm/rotation");
	CougarOpticBoard::entryArmCubeGrabbed = table->GetEntry("arm/cube-grabbed");
	CougarOpticBoard::entryArmClimbStatus = table->GetEntry("arm/climb-status");
	CougarOpticBoard::entryAutonomousStartPos = table->GetEntry("autonomous/side");
	CougarOpticBoard::entryAutonomousNoAuto = table->GetEntry("autonomous/emergency-no-auto");
	CougarOpticBoard::entryAutonomousInstructions = table->GetEntry("autonomous/instructions");
	CougarOpticBoard::entryAutonomousEnableCrossing = table->GetEntry("autonomous/enable-crossing");
	CougarOpticBoard::entryFMSTime = table->GetEntry("fms/time");
	CougarOpticBoard::entryFMSAlliance = table->GetEntry("fms/alliance");
	CougarOpticBoard::entryFMSField = table->GetEntry("fms/field");
	CougarOpticBoard::entryIsAutonomous = table->GetEntry("gamedata/is-autonomous");
	CougarOpticBoard::entryIsTeleop = table->GetEntry("gamedata/is-teleop");
	CougarOpticBoard::entryIsEnabled = table->GetEntry("gamedata/is-enabled");
	CougarOpticBoard::entryLidar = table->GetEntry("lidar");
	CougarOpticBoard::entryUpdate = table->GetEntry("update");
}

//~~~~~~~~~~~~~~~~~~~~~ SET METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 *  Pushes the value for the rotation of the robot to the network tables.
 *  This is then pulled by the COB.
 *
 *	Preferably, call this in the teleop & autonomous execute method.
 *
 *  Domain: (-360 to 360)
 *
 *  @author Quintin Harter
 */
void CougarOpticBoard::PushRotation(double angle) {
	entryRotation.SetDouble(angle);
}

/**
 *  Pushes the value for the x coordinate of the robot to the network tables.
 *  This is then pulled by the COB.
 *
 *  Preferably, call this in the teleop & autonomous execute method.
 *
 *  Domain: (??? to ???)
 *
 *  @author Quintin Harter
 */
void CougarOpticBoard::PushPositionX(double x) {
	entryPositionX.SetDouble(x);
}

/**
 *  Pushes the value for the y coordinate of the robot to the network tables.
 *  This is then pulled by the COB.
 *
 *  Preferably, call this in the teleop & autonomous execute method.
 *
 *  Domain: (??? to ???)
 *
 *  @author Quintin Harter
 */
void CougarOpticBoard::PushPositionY(double y) {
	entryPositionY.SetDouble(y);
}

/**
 *  Pushes the value for the direction of movement to the network tables.
 *  This is then pulled by the COB.
 *
 *  Preferably, call this in the teleop & autonomous execute methods.
 *
 *  Domain: (-360 to 360)
 *
 *  @author Quintin Harter
 */
void CougarOpticBoard::PushVelocityDirection(double angle) {
	entryVelocityDirection.SetDouble(angle);
}

/**
 *  Pushes the value for the relative speed of the robot to the network tables.
 *  This is then pulled by the COB.
 *
 *  Preferably, call this in the teleop & autonomous execute methods.
 *
 *  Domain: (0 to 1)
 *
 *  @author Quintin Harter
 */
void CougarOpticBoard::PushVelocityMagnitude(double size) {
	entryVelocityMagnitude.SetDouble(size);
}

/**
 *  Pushes the value for the arm height of the robot to the network tables.
 *  This is then pulled by the COB.
 *
 *  Preferably, call this in teleop's execute method.
 *
 *  Domain: (??? to ???)
 *
 *  @author Quintin Harter
 */
void CougarOpticBoard::PushArmHeight(double height) {
	entryArmHeight.SetDouble(height);
}

/*
void CougarOpticBoard::TriggerArmRotation(bool up) {
	if (up) {
		double rotation = entryArmRotation.GetValue().get()->GetDouble();
		while (rotation > 0) {
			entryArmRotation.SetDouble(--rotation);
		}
	} else {
		entryArmRotation.SetDouble(135);
	}
}
*/

void CougarOpticBoard::PushArmRotation(double rotation) {
}

/**
 *  Pushes the value of whether or not the cube is grabbed to the network tables.
 *  This is then pulled by the COB.
 *
 *  Preferably, call this in teleop's execute method.
 *
 *  Domain: (true or false)
 *
 *  NOTE: Depending on the functionality of the robot, this may be removed.
 *
 *  @author Quintin Harter
 */
void CougarOpticBoard::PushArmCubeGrabbed(bool cubeGrabbed) {
	entryArmHeight.SetBoolean(cubeGrabbed);
}

/**
 *  Pushes the value of the status of the climb to the network tables.
 *  This is then pulled by the COB.
 *
 *  Preferably, call this in teleop's execute method.
 *
 *  Domain: (??? to ???)
 *
 *  NOTE: Depending on the functionality of the robot, this may be removed.
 *
 *  @author Quintin Harter
 */
void CougarOpticBoard::PushArmClimbStatus(double climbStatus) {
	entryArmClimbStatus.SetDouble(climbStatus);
}

void CougarOpticBoard::Update() {
	if (entryUpdate.Exists())
		entryUpdate.SetBoolean(!entryUpdate.GetValue().get()->GetBoolean());
	else
		entryUpdate.SetBoolean(false);
}

//~~~~~~~~~~~~~~~~~~~~~ GET METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 *  Pulls the value of the autonomous starting position from the COB.
 *
 *  Preferably, call this method in autonomous initialization.
 *
 *  @returns "" (for nothing), "left", "center", or "right".
 *
 *  @author Quintin Harter
 */
int CougarOpticBoard::GetAutonomousStartPos() {
	if (entryAutonomousStartPos.Exists())
		return ((int) entryAutonomousStartPos.GetValue().get()->GetDouble()) - 1;
	return 0;
}

/**
 *  Pulls the value of the autonomous starting position from the COB.
 *
 *  Preferably, call this method in autonomous initialization.
 *
 *  @returns whether or not the drivers have chosen the robot to move.
 *
 *  @author Quintin Harter
 */
bool CougarOpticBoard::GetAutonomousNoAuto() {
	if (entryAutonomousNoAuto.Exists()) {
		return entryAutonomousNoAuto.GetValue().get()->GetBoolean();
	}
	return false;
}

/**
 *  Pulls the value of the autonomous information from the COB.
 *
 *  Preferably, call this method in autonomous initialization.
 *
 *  @returns the information based on the starting position of the robot:
 *  	~ If we are on the side, returns the instructions for the robot:
 *  		- 0: Do the switch first (if possible), else the scale (if possible), else drive straight.
 *  		- 1: Do the scale first (if possible), else drive straight
 *  		- 2: Drive straight
 *  	~ If we are in the middle, returns the delay time
 *
 *  @author Quintin Harter
 */
int CougarOpticBoard::GetAutonomousInstructions() {
	if (entryAutonomousInstructions.Exists())
		return (int) (entryAutonomousInstructions.GetValue().get()->GetDouble());
	return -1;
}

bool CougarOpticBoard::GetAutonomousEnableCrossing() {
	if (entryAutonomousEnableCrossing.Exists())
		return entryAutonomousEnableCrossing.GetValue().get()->GetBoolean();
	return false;

}

void CougarOpticBoard::PushFMSAlliance(bool isRed) {
	entryFMSAlliance.SetBoolean(isRed);
}

void CougarOpticBoard::PushFMSTime(double time) {
	entryFMSTime.SetDouble(time);
}

void CougarOpticBoard::PushFMSField(std::string data) {
	entryFMSField.SetString(data);
}

void CougarOpticBoard::PushAutonomous(bool isAutonomous) {
	entryIsAutonomous.SetBoolean(isAutonomous);
}

void CougarOpticBoard::PushTeleop(bool isTeleop) {
	entryIsTeleop.SetBoolean(isTeleop);
}

void CougarOpticBoard::PushEnabled(bool isEnabled) {
	entryIsEnabled.SetBoolean(isEnabled);
}

void CougarOpticBoard::PushLidar(double lidar) {
	entryLidar.SetString(std::to_string(lidar));
}
