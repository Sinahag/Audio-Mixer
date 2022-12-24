/*
Module to enable the support of 8x8 Matrix hardware on the BeagleBone Board
MatrixLED support, allows for the configuration of the 8x8 matrix
This module allows control over the registers of the 8x8 matrix
All hardware commands are defined and can be easily changed
*/


#ifndef MATRIXLED_H_
#define MATRIXLED_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#define i2cStartpin1 "config-pin P9_18 i2c"
#define i2cStartpin2 "config-pin P9_17 i2c"
#define matrixOn "i2cset -y 1 0x70 0x21 0x00"
#define displayOn "i2cset -y 1 0x70 0x81 0x00"
#define doubleLED "i2cset -y 1 0x70 0x00 0x04"
#define clearDouble "i2cset -y 1 0x70 0x00 0x00"
#define writeSize 7
#define I2C_DEVICE_ADDRESS 0x70
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"

void i2cCommand(char* command);

void initMatrix();

void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);

int initI2cBus(char* bus, int address);

void dispInt(int val);

void dispMode(int val);
#endif