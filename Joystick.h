/*
Module to enable the support of joystick component on the BeagleBone Board
Allows us to see what direction the joystick is at with one simple function
*/

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#define A2D_FILE_VOLTAGE2 "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define A2D_FILE_VOLTAGE3 "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"

#define NEUTRAL 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

// returns an integer referring to the joystick direction
int Joystick_getDirection();

#endif