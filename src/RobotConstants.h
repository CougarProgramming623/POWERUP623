#pragma once

#define BUMP_DELTA_PITCH_LIMIT 0.5
#define BUMP_DELAY 0.5

#define TEST_BOT

#define SIDE_LEFT   0
#define SIDE_CENTER 1
#define SIDE_RIGHT  2

#define WHEEL_DIAMETER 8;
#define ENCODER_DIAMETER 2.5
#define TICKS_PER_REVOLUTION 600

#ifdef TEST_BOT
#define TICKS_PER_INCH 63 / 2 * 120 / 96 * 120 / 110 * 120 / 127.5 * 120 / 116.5 * 120 / 109
#define TICKS_PER_INCH_STRAFE TICKS_PER_INCH

#else //real bot

#define TICKS_PER_INCH 21.08
#define TICKS_PER_INCH_STRAFE 29.7
#endif

#define ROBOT_WIDTH 33.5// inches
#define ROBOT_LENGTH 39.0// inches
#define HALF_ROBOT_LENGTH ROBOT_LENGTH/2
#define HALF_ROBOT_WIDTH ROBOT_WIDTH/2
#define ROBOT_DIAGONAL 42.1545f

#define FEET_TO_INCHES 12.0
#define CM_TO_INCHES 0.393701

#define CAMERA_WIDTH 960
#define HALF_CAMERA_WIDTH CAMERA_WIDTH /2

//12 feet to the front plus half of its width for the center
#define DISTANCE_TO_SWITCH 12.0 * FEET_TO_INCHES + (2.0 * FEET_TO_INCHES)
#define DISTANCE_TO_SCALE (27.0 * FEET_TO_INCHES)

#define LIDAR_ARR_SIZE 10
#define LIDAR_THRESHOLD 0 //FIXME correct value

#define TURN_SPEED 1.0
#define SPEED 0.45
#define FAST_SPEED 0.6
#define SLOW_SPEED 0.2
#define TIMEOUT 10
#define TURN_TIMEOUT 2

#define INTAKE_SPEED 1
#define TELEOP_EXPUNGE_SPEED 1
#define AUTO_EXPUNGE_SPEED 1
#define INTAKE_MAX_CURRENT 1
#define INTAKE_MAX_NUM_SPIKES 3

#define CLIMB_SPEED 1
#define RAMP_LIFT_SPEED -0.5
#define RAMP_LIFT_TIMEOUT 0.5
#define ENDGAME_CLIMB true
#define ENDGAME_RAMP false

#define WAIT_SEC(x) AddSequential(new WaitCommand(x));
#define WAIT WAIT_SEC(0.35)

#define LENGTH_OF_SWITCH 12 * FEET_TO_INCHES
#define HALF_SWITCH_LENGTH LENGTH_OF_SWITCH/2
#define WIDTH_OF_SWITCH 56
//0.73417 top ~ 0.735
//
#define ELEVATOR_SWITCH_OFFSET 0.25
#define ELEVATOR_DELTA 0.710
#define ELEVATOR_TOP ELEVATOR_DELTA + ELEVATOR_BOTTOM

#define DRIVE_ANGLE_RIGHT atan((140 - ROBOT_LENGTH) / ((HALF_SWITCH_LENGTH - 25) - (HALF_ROBOT_WIDTH - 12))) * (180 / M_PI) //ANGLED-DISTANCE DRIVE ANGLE
#define DRIVE_ANGLE_LEFT atan((140 - ROBOT_LENGTH) / ((HALF_SWITCH_LENGTH - 25) + (HALF_ROBOT_WIDTH - 12))) * (180 / M_PI)//ANGLED-DISTANCE DRIVE ANGLE

#ifdef TEST_BOT
#define STRAFE_SCALAR 48.0/33.0 * 48.0/44.0 * 48.0/51.0 * 48.0/47.0 * 48.0/50.0
#else
#define STRAFE_SCALAR 1
#endif

#define END_GAME_TIME 31

#define minFRC(a, b) a < b ? a : b

#define lerp(a, b, f) a + f * (b - a)

#define normalize(min, max, value) (value - min) / (max - min)

#define map(value, sourceMin, sourceMax, destMin, destMax) lerp(destMin, destMax, normalize(sourceMin, sourceMax, value))

#define maxFRC(a, b) a > b ? a : b;

#define avg(a, b) (a + b) / 2
