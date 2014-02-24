#!/bin/bash 

# Set library path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/pi/MY_PROJECT/SHP/arm_lib/libxml2:/home/pi/MY_PROJECT/SHP/arm_lib/log4c:/home/pi/MY_PROJECT/SHP/arm_lib/wiringPi:/home/pi/MY_PROJECT/SHP/arm_lib/raspbian:/home/pi/MY_PROJECT/SHP/arm_lib/raspbian/arm-linux-gnueabihf

# Set log4c resource path
export LOG4C_RCPATH=/home/pi/MY_PROJECT/SHP/cfg

# Conform library path
ldd ./SHP

# Load application
./SHP

