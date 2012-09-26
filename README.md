Coffee over anything
====================

Main goal of this project is to allow me to make a coffee early in the morning, while still laying in the warm bed, using only my phone (which I have just grabbed anyway, to turn the alarm clock off).

Coffee over USB
---------------

[De'Longhi DGI EC5](http://www.shopdelonghi.com/detail/DGI+EC5) is a simple device controlled only by the on-off switch. The switch can be shorted via the relay (I plan to use Mitshubishi Electric SF20-DPS-H1-4), which in turn is controlled by a dirt-chip Atmega8L microcontroller connected by a simple circuit to the USB port using the [V-USB](http://www.obdev.at/products/vusb/index.html) software. This basically turns the coffee maker into an USB device. Source code for the microcontroller can be found in the [atmega](atmega/) directory. Circuit schematics will be drawn and provided later. For now, look at [the USB-Servo](http://www.schatenseite.de/index.php?eID=tx_cms_showpic&file=uploads%2Fpics%2Fcircuit.sch_05.png&md5=9499241df3382e52f51a60c42206365e53ac1274&parameters[0]=YTo0OntzOjU6IndpZHRoIjtzOjQ6IjgwMG0iO3M6NjoiaGVpZ2h0IjtzOjQ6IjYw&parameters[1]=MG0iO3M6NzoiYm9keVRhZyI7czoyNDoiPGJvZHkgYmdjb2xvcj0iI2RkZGRkZCI%2B&parameters[2]=IjtzOjQ6IndyYXAiO3M6Mzc6IjxhIGhyZWY9ImphdmFzY3JpcHQ6Y2xvc2UoKTsi&parameters[3]=PiB8IDwvYT4iO30%3D) to get an idea.

Simple CLI utility for communicating with the coffeemaker's controller is provided in the [cli](cli/).

Coffee over HTTP
----------------

That USB device can be connected to anything. In my case it will be OpenWRT-controlled router with USB port (say, TP-Link MR4320). Simple CGI script is provided in the [cgi](cgi/) directory. It should be placed in the /www/cgi-bin directory of OpenWRT router.

Coffee via tapping the touchscreen
----------------------------------

Android app that talks to the CGI script to control will end up in the [android](android/) directory.

Credits
-------

I used hid-custom-rq V-USB example by Christian Starkjohann when writing all of the AVR-related code.
The circuit is based on [USB-Servo by Ronald Schaten](http://www.schatenseite.de/index.php?id=219&L=2).

WARNING
=======

Nobody said dicking around with electric devices is a good idea. Contrary, it's probably a bad one. I TAKE NO RESPONSIBILITY WHATSOEVER FOR ANY DEATHS, INJURIES, FIRES, PROPERTY DAMAGES, LOST WARRANTIES, DATA LOSS, CAFFEINE OVERDOSE AND ANY OTHER CONSEQUENCES OF ANYONE (YES, THIS INCLUDES YOU) MAKING ANY USE OF STUFF INCLUDED IN HERE. It's your risk.
