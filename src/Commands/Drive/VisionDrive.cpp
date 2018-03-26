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

VisionDrive::VisionDrive(double speed, int timeout) :
		frc::Command(), frc::PIDOutput() {
	// Use Requires() here to declare subsystem dependenciesactualSpeed
	// eg. Requires(Robot::chassis.get());
	m_distanceToTarget = -1.0;
	m_speed = speed;
	m_timeout = timeout;
	m_currentAngle = 0.0;
	rotateToAngleRate = 0.0;
	cantSeeTarget = false;
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

	turnController->SetInputRange(-180.0f, 180.0f);
	turnController->SetOutputRange(-1.0, 1.0);
	turnController->SetAbsoluteTolerance(kToleranceDegrees);
	turnController->SetContinuous(true);
	turnController->SetSetpoint(RobotMap::ahrs->GetAngle());
	turnController->Enable();
}

int VisionDrive::getPosition() {
	return RobotMap::driveTrainleftFront->GetSelectedSensorPosition(0);
}

int VisionDrive::getMaxTicks() {
	return (int) (TICKS_PER_INCH * m_distanceToTarget);
}

// Called repeatedly when this Command is scheduled to run
void VisionDrive::Execute() {
	nt::NetworkTableEntry centerX = visionTable->GetEntry("centerX");

	std::vector<double> arr = centerX.GetDoubleArray(llvm::ArrayRef<double>());
	if (arr.size() == 2) {
		m_currentAngle = GetVisionTargetDriveAngle(arr[0], arr[1]);
		m_distanceToTarget = GetVisionTargetDriveDistance(arr[0], arr[1]); //drawn from networktables

		DriverStation::ReportError("First CenterX is :" +std::to_string(arr[0])+ " Second CenterX is :"+std::to_string(arr[1]));
		DriverStation::ReportError("Vision angle is :" + std::to_string(m_currentAngle));
		DriverStation::ReportError("Distance is :" + std::to_string(m_distanceToTarget));

		double x = sin(m_currentAngle) * m_speed;
		double y = cos(m_currentAngle) * m_speed;

		DriverStation::ReportError("X is :" + std::to_string(x));
		DriverStation::ReportError("Y is :" + std::to_string(y));

		//Robot::driveTrain->PolarDrive(m_speed, PI / 2 - m_currentAngle, 0);
		DriverStation::ReportError("Driving...");
		Robot::driveTrain->MecanumDrive(x, fabs(y), 0, 0);
		DriverStation::ReportError("Driving...");
	}
	/*
	 * This allows the robot to continue moving in the correct direction in order to gain view of the target
	else if (arr.size() > 0 && arr.size() < 2) {
			if (DriverStation::GetInstance().GetGameSpecificMessage().find("L") == 0) {
				Robot::driveTrain->MecanumDrive(-m_speed * 0.3, 0, 0, 0);
				DriverStation::ReportError("Driving Left Vision");
			}

			else {
				Robot::driveTrain->MecanumDrive(m_speed * 0.3, 0, 0, 0);
				DriverStation::ReportError("Driving Right Vision");
			}
	}*/
	else {
		DriverStation::ReportError("Can't see targets");
		cantSeeTarget = true;
	}

}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() {
	nt::NetworkTableEntry entry = visionTable->GetEntry("height");
	std::vector<double> arr = entry.GetDoubleArray(llvm::ArrayRef<double>());

	if (cantSeeTarget) {
		DriverStation::ReportError("ENDAUTOVISION-CANTSEE");
		return true;
	}

	if (m_distanceToTarget != -1 && m_distanceToTarget <= 10) {
		DriverStation::ReportError("ENDAUTOVISION-DISTANCE");
		return true;
	} else if (IsTimedOut()) {
		return true;
	} else if (arr.size() >= 2) {

		double height1 = arr[arr.size()-1];//The last two contours, if there are more than 2, are the tape contours
		double height2 = arr[arr.size()-2];
		if ((height1 + height2) / 2 >= 550) {
			DriverStation::ReportError("ENDAUTOVISION-HEIGHT");
			return true;
		}
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

#define FOCAL_LENGTH 803.85
#define TAPE_WIDTH 6
#define TAPE_HEIGHT 15.75

double VisionDrive::GetVisionTargetDriveAngle(double y1, double y2) {

	double lengthPixels = (y1 + y2) / 2 - 480;

	if (y1 >= 480 && y2 >= 480)
		return atan(lengthPixels / FOCAL_LENGTH);
	else
		return -atan(lengthPixels / FOCAL_LENGTH);

}

double VisionDrive::GetVisionTargetDriveDistance(double y1, double y2) {
	double widthPxl = fabs(y2 - y1);
	double straightDistance = (TAPE_WIDTH * FOCAL_LENGTH) / widthPxl;
	double trueDistance = straightDistance / cos(m_currentAngle);
	//double value = (TAPE_HEIGHT * CAMERA_HEIGHT) / (2 * averageHeight * tan(VERTICAL_THETA * M_PI / 180));
	return fabs(trueDistance);
}
