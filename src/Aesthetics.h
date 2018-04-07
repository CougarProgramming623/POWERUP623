#pragma once
#include "Timer.h"

/*
 * A class that manager updating aesthetic things on the robot
 */
class Aesthetics {
public:
	void OnEndgame();
	bool hasClimbed = false;
	void Update();
	Aesthetics();
private:
	Timer* m_timer;
};
