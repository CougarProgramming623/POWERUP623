/*
 * CougarOpticBoard.h
 *
 *  Created on: Feb 7, 2018
 *      Author: Quintin Harter
 */

#ifndef SRC_COMMANDS_COUGAROPTICBOARD_H_
#define SRC_COMMANDS_COUGAROPTICBOARD_H_

#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTable.h"

#define OPTION_DO_EASY 0
#define OPTION_DO_SWITCH 1
#define OPTION_DO_SCALE 2
#define OPTION_DO_BASELINE 3
#define CROSSING_ENABLED true
#define CROSSING_DISABLED false

class CougarOpticBoard {
public:
	static std::shared_ptr<NetworkTable> table;
	//constructor
	CougarOpticBoard();
	static void InitBoard();
	//setters
	static void PushRotation(double angle);
	static void PushPositionX(double x);
	static void PushPositionY(double y);
	static void PushVelocityDirection(double angle);
	static void PushVelocityMagnitude(double size);
	static void PushArmHeight(double height);
	static void PushArmCubeGrabbed(bool cubeGrabbed); //maybe
	static void PushArmClimbStatus(double climbStatus); //maybe
	static void PushFMSTime(double time);
	static void PushFMSField(std::string data);
	static void PushFMSAlliance(bool isRed);
	//getters
	static int GetAutonomousStartPos();
	static bool GetAutonomousNoAuto();
	static int GetAutonomousInstructions();
	static bool GetAutonomousEnableCrossing();
	//insert others

	//static constants-- use these

	static nt::NetworkTableEntry entryRotation;
	static nt::NetworkTableEntry entryPositionX;
	static nt::NetworkTableEntry entryPositionY;
	static nt::NetworkTableEntry entryVelocityDirection;
	static nt::NetworkTableEntry entryVelocityMagnitude;
	static nt::NetworkTableEntry entryArmHeight;
	static nt::NetworkTableEntry entryArmCubeGrabbed; //maybe
	static nt::NetworkTableEntry entryArmClimbStatus; //maybe
	static nt::NetworkTableEntry entryAutonomousStartPos;
	static nt::NetworkTableEntry entryAutonomousNoAuto;
	static nt::NetworkTableEntry entryAutonomousInstructions;
	static nt::NetworkTableEntry entryAutonomousEnableCrossing;
	static nt::NetworkTableEntry entryFMSTime;
	static nt::NetworkTableEntry entryFMSField;
	static nt::NetworkTableEntry entryFMSAlliance;
};

#endif /* SRC_COMMANDS_COUGAROPTICBOARD_H_ */
