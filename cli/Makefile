# Name: Makefile
# Project: hid-custom-rq example
# Author: Christian Starkjohann
# Creation Date: 2008-04-06
# Tabsize: 4
# Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
# License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
# This Revision: $Id$


# Concigure the following definitions according to your system.
# This Makefile has been tested on Mac OS X, Linux and Windows.

# Use the following 3 lines on Unix (uncomment the framework on Mac OS X):
USBFLAGS = `libusb-config --cflags`
USBLIBS = `libusb-config --libs`

NAME = coffee-control

STD_OBJECTS = opendevice.o coffeemaker.o coffee-control.o
MOCK_OBJECTS = opendevice.o coffeemaker-mock.o coffee-control.o

CC		= gcc
CFLAGS	= $(CPPFLAGS) $(USBFLAGS) -O -g -Wall
LIBS	= $(USBLIBS)

all: coffee-control mock-coffee-control

.c.o:
	$(CC) $(CFLAGS) -c $<

coffee-control: $(STD_OBJECTS)
	$(CC) -o $@ $(STD_OBJECTS) $(LIBS)

mock-coffee-control: $(MOCK_OBJECTS)
	$(CC) -o $@ $(MOCK_OBJECTS) $(LIBS)

clean:
	rm -f *.o $(PROGRAM)
