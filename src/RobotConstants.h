#pragma once

#define SIDE_LEFT   0
#define SIDE_CENTER 1
#define SIDE_RIGHT  2

#define WHEEL_DIAMETER 8;
#define ENCODER_DIAMETER 2.5
#define TICKS_PER_REVOLUTION 600
#define TICKS_PER_INCH 63/2
#define ROBOT_WIDTH 39.0// 39 inches
#define FEET_TO_INCHES 12.0
#define LENGTH_OF_SWITCH 12 * FEET_TO_IN

#define normalize(min, max, value) (value - min) / (max - min)

#define lerp(a, b, f) a + f * (b - a)

#define map(value, sourceMin, sourceMax, destMin, destMax) lerp(destMin, destMax, normalize(sourceMin, sourceMax, value))

#define minFRC(a, b) a < b ? a : b;

#define maxFRC(a, b) a > b ? a : b;
