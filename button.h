/*
Module to enable the support of GPIO pins on the BeagleBone Board
Every button used is defined and configured to be able to be read
Also contains runCommand function to run command line commands
*/

#ifndef BUTTON_H_
#define BUTTON_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define config15 "config-pin p8.15 gpio"
#define config16 "config-pin p8.16 gpio"
#define config17 "config-pin p8.17 gpio"
#define config18 "config-pin p8.18 gpio"

#define value15 "/sys/class/gpio/gpio47/value"
#define value16 "/sys/class/gpio/gpio46/value"
#define value17 "/sys/class/gpio/gpio27/value"
#define value18 "/sys/class/gpio/gpio65/value"

#define direction15 "/sys/class/gpio/gpio47/direction"
#define direction16 "/sys/class/gpio/gpio46/direction"
#define direction17 "/sys/class/gpio/gpio27/direction"
#define direction18 "/sys/class/gpio/gpio65/direction"

#define activeLow15 "/sys/class/gpio/gpio47/active_low"
#define activeLow16 "/sys/class/gpio/gpio46/active_low"
#define activeLow17 "/sys/class/gpio/gpio27/active_low"
#define activeLow18 "/sys/class/gpio/gpio65/active_low"

void runCommand(char* command);
//runs a command

void buttonDefine(char* path, char* pin);
//writes to file

bool buttonPress(char* fileName);
//checks certain button is pressed

void userbtnInitalize();
//assigns to let linux know to use gpio and can read

bool checkBtn(char btn);
//checks if button is pressed, accepts char input so of mode, bass, snare, hihat
//accepts single letter so m for mode, b for bass, s for snare, h for hihat


#endif
