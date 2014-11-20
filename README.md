CS 271 - Words (with Friends) AI 
======


###  General requirements to build & run:

#### OpenCV

You'll need to download opencv 3.0 alpha @:

* http://opencv.org/downloads.html

AND

Reconfigure the project properties to point to your opencv installation directory.

Default dir is  @ 

> C:\opencv.

*Note,* it you're having trouble opening the solution, may be better to create a new project and just import the files.

#### Android Debug Bridge

You can either download the entire android sdk which includes ADB.exe

* https://developer.android.com/sdk/installing/index.html?pkg=tools

OR

you could try using the standalone ADB program (excludes unnecessary sdk files):

* http://sourceforge.net/projects/adbstandalone/



#### Instructions:

* Move screen.bat to the same directory as your adb.exe.

* Also, update the ADB_DIR file path variable  in opencv.hpp to your adb file path.

* Ensure debugging privileges is enabled on your phone, and your phone is connected to your comp. via usb.

* Start a new WORDS game, enter a match, and zoom all the way out so the entire board and tiles are visible.

* Run the program.

...

*Note,* If adb cannot take a screenshot, it may be the case adb cannot find your phone.
Run these params, and see if you're your phone is listed

> adb kill-server

> adb devices

If your device is not listed, verify you have debugging privilege enabled on your phone. 
Newer versons of android require covert steps to enable.

...

...

**main.cpp** contains all the functions for retrieval and image processing of the the screenshot.


This program uses the template image file (images\all.png) and attemps to identify all valid letters in the screenshot.

It first crops two sub-images (the game board and the panel that displays your available letters.) and cleans the image for better feature detection. Currently the code is fine tuned for the screenshot resolution of my phone, we may have to adjust a few variables depending on your screenshot reso.

**AI.cpp** contains all the logic for the decision making / word search. I have included various helper functions.

**dict.txt** contains all the valid words in the game's dictionary.



...
