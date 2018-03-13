/*
 * CurrentSpikeIndicator.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: frc623
 */

#include "CurrentSpikeIndicator.h"

#include "WPILib.h"
#include "ctre/Phoenix.h"

//constructor for current spike indicator
CurrentSpikeIndicator::CurrentSpikeIndicator(double currentThreshold, std::shared_ptr<WPI_TalonSRX> talonToMeasure) {
	threshold = currentThreshold;
	index = 0;
	counter = 0;
	talon = talonToMeasure;
}

//call this in the Execute() method of the command to update the current array
void CurrentSpikeIndicator::Update() {
	currentArray[index] = fabs(talon->GetOutputCurrent());
	//DriverStation::ReportError("Index: " + std::to_string(index) + " Counter: " + std::to_string(counter) + " currentArray[index]: " + std::to_string(currentArray[index]));
	index++;
	index %= ARRAY_SIZE;

	counter++;

}

//call this in the IsFinished() method of the command to detect the spike
bool CurrentSpikeIndicator::GetSpike() {
	//return the average of all current values is greater than the threshold
	if (counter > ARRAY_SIZE) {
		double average = 0.0;
		for (int i = 0; i < ARRAY_SIZE; i++) {
			double current = currentArray[i];
			average += current;
		}
		average /= ARRAY_SIZE;
		//DriverStation::ReportError("Average Current on " + talon->GetName() + ": " + std::to_string(average));
		//if(average>=threshold)
			//DriverStation::ReportError("ENDED: " + std::to_string(average));
		return average >= threshold;
	}
	//DriverStation::ReportError("Not Enough Data");
	return false; //not enough data
}

//if you want to reset the indicator, call this
void CurrentSpikeIndicator::Reset() {
	for (int i = 0; i < ARRAY_SIZE; i++)
		currentArray[i] = 0.0;
}

//if you want to change the threshold, call this
void CurrentSpikeIndicator::ChangeThreshold(double newThreshold) {
	threshold = newThreshold;
}
