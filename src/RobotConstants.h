#pragma once

#define BUMP_DELTA_PITCH_LIMIT 0.5
#define BUMP_DELAY 0.5

#define TEST_ROBOT

#define SIDE_LEFT   0
#define SIDE_CENTER 1
#define SIDE_RIGHT  2

#define WHEEL_DIAMETER 8;
#define ENCODER_DIAMETER 2.5
#define TICKS_PER_REVOLUTION 600

#ifdef TEST_BOT
#define TICKS_PER_INCH 63/2
#define TICKS_PER_INCH 63/2


#else //real bot

#define TICKS_PER_INCH 21.08
#define TICKS_PER_INCH_STRAFE 29.7
#endif

#define ROBOT_WIDTH 33.0// inches
#define ROBOT_LENGTH 33.0// inches
#define HALF_ROBOT_LENGTH ROBOT_LENGTH/2
#define ROBOT_DIAGONAL 42.1545f

#define FEET_TO_INCHES 12.0

#define CAMERA_WIDTH 960
#define HALF_CAMERA_WIDTH CAMERA_WIDTH /2

//12 feet to the front plus half of its width for the center
#define DISTANCE_TO_SWITCH 12.0 * FEET_TO_INCHES + (2.0 * FEET_TO_INCHES)
#define DISTANCE_TO_SCALE (27.0 * FEET_TO_INCHES)
#define HALF_ROBOT_WIDTH (ROBOT_WIDTH / 2.0)

#define TURN_SPEED 1.0
#define SPEED 0.45
#define FAST_SPEED 0.6
#define SLOW_SPEED 0.2
#define TIMEOUT 10

#define INTAKE_SPEED 1
#define EXPUNGE_SPEED 1
#define INTAKE_MAX_CURRENT 1
#define INTAKE_MAX_NUM_SPIKES 3

#define WAIT_SEC(x) AddSequential(new WaitCommand(x));
#define WAIT WAIT_SEC(0.35)

#define LENGTH_OF_SWITCH 12 * FEET_TO_IN
#define WIDTH_OF_SWITCH 56

#define ELEVATOR_TOP 0
#define ELEVATOR_DELTA 0

#define normalize(min, max, value) (value - min) / (max - min)

#define lerp(a, b, f) a + f * (b - a)

#define map(value, sourceMin, sourceMax, destMin, destMax) lerp(destMin, destMax, normalize(sourceMin, sourceMax, value))

#define minFRC(a, b) a < b ? a : b;

#define maxFRC(a, b) a > b ? a : b;
