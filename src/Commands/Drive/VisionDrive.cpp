#include "VisionDrive.h"
#include <cmath>
#include "Math.h"
#include "networktables/NetworkTableInstance.h"
#include <thread>
#include <chrono>

#define ROOT_2 1.41421356237

const static double kP = RobotMap::turnP;
const static double kI = RobotMap::turnI;
const static double kD = RobotMap::turnD;
const static double kF = 0.0;


const static double kToleranceDegrees = 2.0f;

#define PI 3.141592
#define ROTATE_FIX_SPEED 0.05

VisionDrive::VisionDrive(double speed, int timeout)
		: frc::Command(), frc::PIDOutput() {
	// Use Requires() here to declare subsystem dependenciesactualSpeed
	// eg. Requires(Robot::chassis.get());
	m_distanceToTarget = 0.0;
	m_speed = speed;
	m_timeout = timeout;
	m_currentAngle = 0.0;
	rotateToAngleRate = 0.0;
	initEncPosition = RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0);
	m_timer = new Timer();
	turnController = new PIDController(kP, kI, kD, kF, RobotMap::ahrs, this);

	visionTable = NetworkTable::GetTable("vision");

	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void VisionDrive::Initialize() {
	SetTimeout(m_timeout); //timeout for 10ms

	m_timer = new Timer();
	m_timer->Start();

}

int VisionDrive::getPosition() {
	return RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0);
}

int VisionDrive::getMaxTicks() {
	return (int)(TICKS_PER_INCH * m_distanceToTarget);
}

// Called repeatedly when this Command is scheduled to run
void VisionDrive::Execute() {
	nt::NetworkTableEntry vision = visionTable->GetEntry("centerX");

	std::vector<double> arr = vision.GetDoubleArray(llvm::ArrayRef<double>());
	if(arr.size() == 2)
	{
		m_currentAngle = GetVisionTargetDriveAngle(arr[0], arr[1]); //Put in real values later
		m_distanceToTarget = GetVisionTargetDriveDistance(arr[0], arr[1]); //drawn from networktables

		//SmartDashboard::PutString(llvm::StringRef("DB/String 0"), llvm::StringRef("Vision angle is :" + std::to_string(m_currentAngle)));
		//SmartDashboard::PutString(llvm::StringRef("DB/String 1"), llvm::StringRef("Distance is :" + std::to_string(m_distanceToTarget)));
		DriverStation::ReportError("Vision angle is :" + std::to_string(m_currentAngle));
		DriverStation::ReportError("Distance is :" + std::to_string(m_distanceToTarget));
		double x = cos(m_currentAngle * M_PI / 180) * m_speed;
		double y = sin(m_currentAngle * M_PI / 180) * m_speed;


		Robot::driveTrain->MecanumDrive(x, y, 0, RobotMap::ahrs->GetYaw());
	}
	else{
		DriverStation::ReportError("Can't see targets");
	}

}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() {
	if (m_timer && m_timer->Get() > m_timeout) {
		return true;
	}
	if (fabs(getPosition() - initEncPosition) >= fabs(getMaxTicks())) {
		return true;
	}
	return false;

}

// Called once after isFinished returns true
void VisionDrive::End() {
	initEncPosition = getPosition();
	Robot::driveTrain->Stop();

	if (turnController) {
		turnController->Disable();
		delete turnController;
	}

	if (m_timer) {
		m_timer->Reset();
		delete m_timer;
	}

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionDrive::Interrupted() {

}

void VisionDrive::PIDWrite(double output) {
	rotateToAngleRate = output;
}

#define HORIZONTAL_THETA 1558.32
#define VERTICAL_THETA 1558.32
#define CAMERA_HEIGHT 544

#define FOCAL_LENGTH 814.88
#define TAPE_WIDTH 6
#define TAPE_HEIGHT 15.75

double VisionDrive::GetVisionTargetDriveAngle(double y1, double y2) {

	/*if(DriverStation::GetInstance().GetGameSpecificMessage().find("L") ==0)
		return acos(-1 * VisionDrive::GetVisionTargetDriveDistance(y1, y2)/TAPE_WIDTH);
	else*/
		return atan(fabs(y2-y1)/FOCAL_LENGTH);


	/*double averageX = (x1 + x2) / 2.0;
	double distanceFromTapeCenterToImageCenter = HALF_CAMERA_WIDTH - averageX;
	double phi = atan(distanceFromTapeCenterToImageCenter / HORIZONTAL_THETA) * 180 / M_PI;
	return 90.0 - phi;*/
}

double VisionDrive::GetVisionTargetDriveDistance(double y1, double y2) {
	double widthPxl = fabs(y2-y1);
	double straightDistance = (TAPE_WIDTH * FOCAL_LENGTH)/widthPxl;
	double trueDistance = straightDistance/ cos(m_currentAngle);
	//double value = (TAPE_HEIGHT * CAMERA_HEIGHT) / (2 * averageHeight * tan(VERTICAL_THETA * M_PI / 180));
	return trueDistance;
}
