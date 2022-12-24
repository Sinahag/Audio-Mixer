/*
Module to enable the support of starting and joining threads
Interface between beatbox and threads
This allows encapsulation between user and files
Easy to read, easy to use 3 simple functions
*/

#ifndef THREADCONTROL_H_
#define THREADCONTROL_H_

#include "button.h"
#include "Joystick.h"
#include "MatrixLED.h"
#include "audioMixer.h"
#include "Threads.h"
#include <pthread.h>

void initalizeHW();

void initalizeThreads();

void cancelThreads();

#endif