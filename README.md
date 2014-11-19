271-AI
======


## Requirements to build & run:

### OpenCV


You'll need to download opencv 3.0 alpha @:

* http://opencv.org/downloads.html

AND

reconfigure the project properties to point to your opencv installation directory.

Currently it's set @ C:\opencv.

It may be better to create a new solution (if you're using visual studio) and just import the .cpp&.hpp file.

### Android Debug Bridge

You can either download the entire android sdk which includes ADB.exe

* https://developer.android.com/sdk/installing/index.html?pkg=tools

OR

you could try using the standalone ADB program (excludes unnecessary sdk files):

* http://sourceforge.net/projects/adbstandalone/



Instructions:

First you'll need to move screen.bat to the same directory as your adb.exe.

Also, update the ADB_DIR file path variable  in opencv.hpp accordingly.

Ensure debugging privileges is enabled on your phone, and your phone is connected to your comp. via usb.

Start a new WORDS game, enter a match, and zoom all the way out so the entire board and tiles are visible
Run the program.

IF adb cannot take a screenshot, it may be the case adb cannot find your phone.

Run these params, and see if you're your phone is listed

> adb kill-server

> adb devices

This program uses the template image file (images\all.png) and attemps to identify all valid letters in the screenshot.

It first crops two sub-images (the game board and the panel that displays your available letters.) and cleans the image for better feature detection.

Currently the code is fine tuned for the screenshot resolution of my phone, we may have to adjust a few variables depending on your screenshot reso.







 
