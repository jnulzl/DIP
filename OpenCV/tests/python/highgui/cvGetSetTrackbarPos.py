#! /usr/bin/env python
"""
This script will test highgui's Get/Set functionality for the trackbar
"""

# name of this test and it's requirements
TESTNAME = "cvGetSetTrackbarPos"
REQUIRED = ["cvCreateTrackbar"]

 
# needed for sys.exit(int) and .works file handling
import sys
import works

# check requirements and delete old flag file, if it exists
if not works.check_files(REQUIRED,TESTNAME):
	sys.exit(77)

# import the necessary things for OpenCV
import opencv
from opencv.highgui import *
from opencv.cv      import *

# some definitions
win_name = "testing..."
bar_name = "foo"

# create output window
cvNamedWindow(win_name,CV_WINDOW_AUTOSIZE)

# create our trackbar
cvCreateTrackbar( bar_name, win_name, 127, 255, 0 )

# trackbar pos must be 127, we set it here __^__
if cvGetTrackbarPos( bar_name, win_name ) != 127:
	print "(ERROR) cvGetTrackbarPos() returned wrong value (!=127)."
	sys.exit(1)

# set the trackbar to new position and compare it
cvSetTrackbarPos( bar_name, win_name, 255 )

if cvGetTrackbarPos( bar_name, win_name ) != 255:
	print "(ERROR) cvSetTrackbarPos() didn't set value correctly."
	sys.exit(1)
	

# create flag file for following tests
works.set_file(TESTNAME)

# return 0 (success)
sys.exit(0)
