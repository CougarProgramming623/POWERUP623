#pragma once

#define SIDE_LEFT   0
#define SIDE_CENTER 1
#define SIDE_RIGHT  2

#define WHEEL_DIAMETER 8;
#define ENCODER_DIAMETER 2.5
#define TICKS_PER_REVOLUTION 600
#define TICKS_PER_INCH 63/2

#define ROBOT_WIDTH 34.0// inches
#define ROBOT_LENGTH 39.0// inches
#define ROBOT_DIAGONAL 42.1545f

#define FEET_TO_INCHES 12.0

#define CAMERA_WIDTH 960
#define HALF_CAMERA_WIDTH CAMERA_WIDTH /2

//12 feet to the front plus half of its width for the center
#define DISTANCE_TO_SWITCH (12.0 * FEET_TO_INCHES + (2.0 * FEET_TO_INCHES) / 3.0)
#define DISTANCE_TO_SCALE (27.0 * FEET_TO_INCHES)
#define HALF_ROBOT_WIDTH (ROBOT_WIDTH / 2.0)
#define HALF_ROBOT_LENGTH (ROBOT_LENGTH / 2.0)

#define TURN_SPEED 1.0
#define SPEED 0.45
#define FAST_SPEED 0.6
#define TIMEOUT 10

#define WAIT_SEC(x) AddSequential(new WaitCommand(x));
#define WAIT WAIT_SEC(0.35)

#define LENGTH_OF_SWITCH 12 * FEET_TO_IN


#define normalize(min, max, value) (value - min) / (max - min)

#define lerp(a, b, f) a + f * (b - a)

#define map(value, sourceMin, sourceMax, destMin, destMax) lerp(destMin, destMax, normalize(sourceMin, sourceMax, value))

#define minFRC(a, b) a < b ? a : b;

#define maxFRC(a, b) a > b ? a : b;
