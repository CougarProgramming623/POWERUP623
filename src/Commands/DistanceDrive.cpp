#include "DistanceDrive.h"
#include "ahrs.h"
#include "ctre/Phoenix.h"
#include "../RobotMap.h"
#include "Math.h"

const double ROOT_2 = sqrt(2);

	const static double kP = 0.075;
	const static double kI = 0.04;
	const static double kD = 0.26;
	const static double kF = 0.0;

	const static double kToleranceDegrees = 2.0f;
	const static double WHEEL_DIAMETER = 8;
	const static double TICKS_PER_INCH = 1290 / 46;


DistanceDrive::DistanceDrive(double distance, double speed, int timeout) : frc::Command() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_distance = distance;
	m_speed = speed;
	m_timeout = timeout;
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void DistanceDrive::Initialize() {
	try {
		SetTimeout(m_timeout); //timeout for 10ms

		DriverStation::ReportError("DistanceDriveCommand init");
	            /* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
	            /* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
	            /* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */

	            RobotMap::ahrs->ZeroYaw();

	        } catch (std::exception ex ) {
	            std::string err_string = "Error instantiating navX-MXP:  ";
	            err_string += ex.what();
	            //DriverStation::ReportError(err_string.c_str());
	        }
	        DriverStation::ReportError("DistanceDrive2::Intialize() done.");

	 m_timer = new Timer();
	 m_timer->Start();

	 turnController = new PIDController(kP, kI, kD, kF, RobotMap::ahrs, this);
	 turnController->SetInputRange(-180.0f, 180.0f);
	 turnController->SetOutputRange(-1.0, 1.0);
	 turnController->SetAbsoluteTolerance(kToleranceDegrees);
	 turnController->SetContinuous(true);

	 turnController->SetSetpoint(0.0f);
	 //turnController->Enable();

	 initEncPosition = RobotMap::driveTrainrightFront->GetSelectedSensorPosition(0);
}

int DistanceDrive::getPosition() {
	return RobotMap::driveTrainrightFront->GetSelectedSensorPosition(0);
}

double DistanceDrive::getMaxTicks() {
	return ROOT_2 * TICKS_PER_INCH * m_distance;
}


// Called repeatedly when this Command is scheduled to run
void DistanceDrive::Execute() {
	double angle = RobotMap::ahrs->GetYaw();
	frc::SmartDashboard::PutNumber("/COB/rotation", angle);

	double coefficient;

	if (m_distance < 0)
		coefficient = -1.0;
	else
		coefficient = 1.0;

	double actualSpeed = coefficient * m_speed;
	Robot::driveTrain->MecanumDrive(0, actualSpeed, 0, RobotMap::ahrs->GetYaw());
	frc::SmartDashboard::PutNumber("Enc position", getPosition() - initEncPosition);
}

// Make this return true when this Command no longer needs to run execute()
bool DistanceDrive::IsFinished() {
	if (fabs(getPosition() - initEncPosition) >= getMaxTicks()) {
		return true;
	} else if(m_timer->Get() == 15) {
		return true;
	}else {
		return false;
	}

}

// Called once after isFinished returns true
void DistanceDrive::End() {
	initEncPosition = getPosition();

	Robot::driveTrain->MecanumDrive(0,0,0,0);

	if(turnController != nullptr) {
		turnController->Disable();
		delete turnController;
	}

	if(m_timer != nullptr) {
		m_timer->Reset();
		delete m_timer;
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DistanceDrive::Interrupted() {

}

void DistanceDrive::PIDWrite(double output) {
	rotateToAngleRate = output;
}
