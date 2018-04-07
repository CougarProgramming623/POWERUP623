// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
//#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"
#include "DriverStation.h"

//#define USE_PREFS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLlUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainleftFront;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainleftBack;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainrightFront;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainrightBack;
std::shared_ptr<WPI_TalonSRX> RobotMap::intake;
std::shared_ptr<WPI_TalonSRX> RobotMap::intake2;
std::shared_ptr<WPI_TalonSRX> RobotMap::endgameMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::shaftController;
std::shared_ptr<WPI_VictorSPX> RobotMap::testBotIntake2;
std::shared_ptr<frc::MecanumDrive> RobotMap::driveTrainMecanumDrive1;
std::shared_ptr<AnalogPotentiometer> RobotMap::pot;
std::shared_ptr<AnalogInput> RobotMap::analogInput;
std::shared_ptr<Relay> RobotMap::shaftOrRampRelay;
std::shared_ptr<LIDAR> RobotMap::lidar;


AHRS *RobotMap::ahrs;
#ifdef USE_PREFS
frc::Preferences *prefs;
#endif
double RobotMap::turnP;
double RobotMap::turnI;
double RobotMap::turnD;
double RobotMap::driveP;
double RobotMap::driveI;
double RobotMap::driveD;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	//frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	lidar.reset(new LIDAR());

	analogInput.reset(new AnalogInput(0));
#ifdef TEST_BOT

	driveTrainleftFront.reset(new WPI_TalonSRX(12));

	driveTrainleftBack.reset(new WPI_TalonSRX(11));

	driveTrainrightFront.reset(new WPI_TalonSRX(13));

	driveTrainrightBack.reset(new WPI_TalonSRX(14));

	intake.reset(new WPI_TalonSRX(18));

	testBotIntake2.reset(new WPI_VictorSPX(1));
	testBotIntake2->SetInverted(true);
	testBotIntake2->Follow(*intake.get());

	shaftController.reset(new WPI_TalonSRX(16)); //FIXME this should be 16


#else//Real bot
	DriverStation::ReportError("Real BOT!");

	driveTrainleftFront.reset(new WPI_TalonSRX(15));
	//driveTrainleftFront->SetInverted(true);

	driveTrainleftBack.reset(new WPI_TalonSRX(3));
	//driveTrainleftBack->SetInverted(true);

	driveTrainrightFront.reset(new WPI_TalonSRX(4));
	//driveTrainrightFront->SetInverted(true);

	driveTrainrightBack.reset(new WPI_TalonSRX(7));
	//driveTrainrightBack->SetInverted(true);
	shaftController.reset(new WPI_TalonSRX(16)); //FIXME this should be 16

	intake.reset(new WPI_TalonSRX(18));

	intake2.reset(new WPI_TalonSRX(14));

	intake2->SetInverted(true);

	intake2->Set(ControlMode::Follower, 18);
#endif

	shaftOrRampRelay.reset(new Relay(0));
	endgameMotor.reset(new WPI_TalonSRX(17)); //FIXME this is actually the shaft motor
	pot.reset(new AnalogPotentiometer(analogInput, 1.0, 0.0));

	//current config
	shaftController->ConfigPeakCurrentLimit(30, 10);
	shaftController->ConfigPeakCurrentDuration(200, 10);
	shaftController->ConfigContinuousCurrentLimit(0, 10);
	shaftController->EnableCurrentLimit(true);

#ifdef TEST_BOT
	RobotMap::driveTrainleftFront->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 5);
#else
	//RobotMap::driveTrainrightBack->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 5);
	RobotMap::driveTrainleftBack->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 1, 5);
#endif
	driveTrainMecanumDrive1.reset(new frc::MecanumDrive(*driveTrainleftFront, *driveTrainleftBack, *driveTrainrightFront, *driveTrainrightBack));
	//lw->AddActuator("DriveTrain", "Mecanum Drive 1", driveTrainMecanumDrive1);
	driveTrainMecanumDrive1->SetSafetyEnabled(true);
	driveTrainMecanumDrive1->SetExpiration(0.1);
	driveTrainMecanumDrive1->SetMaxOutput(1.0);

	RobotMap::shaftController->SetInverted(true);

	try {
		/***********************************************************************
		 * navX-MXP:
		 * - Communication via RoboRIO MXP (SPI, I2C, TTL UART) and USB.
		 * - See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface.
		 *
		 * navX-Micro:
		 * - Communication via I2C (RoboRIO MXP or Onboard) and USB.
		 * - See http://navx-micro.kauailabs.com/guidance/selecting-an-interface.
		 *
		 * Multiple navX-model devices on a single robot are supported.
		 ************************************************************************/
		ahrs = new AHRS(SPI::Port::kMXP);
	} catch (std::exception& ex) {
		std::string err_string = "Error instantiating navX MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}

#ifdef USE_PREFS
	prefs = Preferences::GetInstance();
#endif
#ifdef TEST_BOT
	#ifdef USE_PREFS
		turnP =prefs->GetDouble("Turn P", 0.035f);
		turnI = prefs->GetDouble("Turn I", 0.00f);
		turnD = prefs->GetDouble("Turn D", 0.03f);
	#else
		turnP = 0.035f;
		turnI = 0.00f;
		turnD = 0.03f;
	#endif

#else
	#ifdef USE_PREFS
			turnP = prefs->GetDouble("Turn P", 0.07f);
			turnI = prefs->GetDouble("Turn I", 0.0f);
			turnD = prefs->GetDouble("Turn D", 0.0315f);
	#else
		turnP = 0.026f;
		turnI = 0.00f;
		turnD = 0.045f;
	#endif
#endif

	//prefs->PutDouble("Turn P", turnP);
	//prefs->PutDouble("Turn I", turnI);
	//prefs->PutDouble("Turn D", turnD);
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS


}
