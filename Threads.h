/* 
Module to enable the usable of threads, does functions from other header files
This threads.h allows us to make the functions that will be called with pthread_create
All the treads are put into this function for encapsulation
Also allows us to easily phread_join using a function that changes a bool variable
*/

#ifndef THREADS_H_
#define THREADS_H_
#include "button.h"
#include "Joystick.h"
#include "MatrixLED.h"
#include "audioMixer.h"

#define debounceTime 50
#define MAXMODES 3

void Threads_init();
void sleepForMs(long long delayInMs);

void *beatOne();
void *beatTwo();
void *modeBtn();
void *bassBtn();
void *snareBtn();
void *hihatBtn();
void *joystickRead();
void endThreads();
#endif