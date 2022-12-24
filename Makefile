# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
TARGET= beatbox

SOURCES= beatbox.c audioMixer.c button.c Joystick.c MatrixLED.c intervalTimer.c Threads.c

PUBDIR = $(HOME)/cmpt433/public/myApps
OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror

# Asound process:
# get alibsound2 lib on target:
# 	# apt-get install libasound2
# Copy target's /usr/lib/arm-linux-gnueabihf/libasound.so.2.0.0 
#      to host  ~/public/asound_lib_BBB/libasound.so
# Copy to just base library:

LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB

# -pg for supporting gprof profiling.
#CFLAGS += -pg

all: clean wav
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound -lm

# Copy wave files to the shared folder
wav:
	mkdir -p $(PUBDIR)/wave-files/
	cp wave-files/* $(PUBDIR)/wave-files/

#beatbox:
#	cp beatbox $(PUBDIR)

#button.o: button.c
#	$(CC_C) $(CFLAGS) -c -g button.c

#Joystick.o: Joystick.c
#	$(CC_C) $(CFLAGS) -c -g Joystick.c

#MatrixLED.o: MatrixLED.c
#	$(CC_C) $(CFLAGS) -c -g MatrixLED.c

clean:
	rm -f $(OUTDIR)/$(TARGET)

