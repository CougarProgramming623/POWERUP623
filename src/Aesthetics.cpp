#include "Aesthetics.h"
#include "DriverStation.h"
#include "Robot.h"
#include "OI.h"
#include "math.h"

Aesthetics::Aesthetics() {
	m_timer = new Timer();
}
void Aesthetics::OnEndgame() {
	m_timer->Start();
}

void Aesthetics::Update() {
	DriverStation::ReportError("Updating aes");
	if (Robot::IsEndGame() || hasClimbed) {
		if (hasClimbed) {
			Robot::oi->GetButtonBoard()->SetOutput(CLIMB_LED, true);
		} else {
			Robot::oi->GetButtonBoard()->SetOutput(CLIMB_LED, fmod(m_timer->Get(), 1.0) < 0.5);
		}
	} else {
		Robot::oi->GetButtonBoard()->SetOutput(CLIMB_LED, false);
	}
}

