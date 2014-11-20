CS 271 - Words (with Friends) AI 
======


###  General requirements to build & run:




###### OpenCV

You'll need to download opencv 3.0 alpha @:

> http://opencv.org/downloads.html

AND

Reconfigure the project properties to point to your opencv installation directory. Default dir is located @ 

> C:\opencv\

*Note,* it you're having trouble opening the solution, may be better to create a new project and just import the files.



###### Android Debug Bridge

You can either download the entire android sdk which includes ADB.exe

> https://developer.android.com/sdk/installing/index.html?pkg=tools

OR

you could try using the standalone ADB program (excludes unnecessary sdk files):

>  http://sourceforge.net/projects/adbstandalone/



#### Instructions:

* Move screen.bat to the same directory as your adb.exe.

* Also, update the ADB_DIR file path variable  in opencv.hpp to your adb file path.

* Ensure debugging privileges is enabled on your phone, and your phone is connected to your comp. via usb.

* Start a new WORDS game, enter a match, and zoom all the way out so the entire board and tiles are visible.

* Run the program.


*Note,* If adb cannot take a screenshot, it may be the case adb cannot find your phone.
Run these commands below , and see if you're your phone is listed

> adb kill-server

> adb devices

If your device is not listed, verify you have debugging privilege enabled on your phone. 
Newer versons of android hide this option by default, you'll have to google.


### File Synopsis

**main.cpp** contains all the functions for retrieval and image processing of the the screenshot.
This program at a basic level uses the template image file (images\all.png) and attemps to identify all valid letters in the screenshot. It first crops two sub-image of the game board and letter panel and applies filters to clean the image for better feature detection. Currently the code is fine tuned for the screenshot resolution of my phone, we may have to adjust a few variables depending on your screenshot reso. 

**AI.cpp** contains the AI_Manager class which holds all the data and logic for our bot. I have included various helper functions to get us started. 

**dict.txt** contains all the valid words in the game's dictionary. Ideally we'll load these words in a trie (not memory efficient unless we use a compact trie), but for our purposes we can trade off space for the speed of fast dictionary lookups. We'll likely have to customize our own version of the radix/patricia/suffix tree so we can find words via certain patterns and words that are similiar to another word.



### AI Approach 

I'm just brainstorming here, but here's what I had in mind:

TODO:
Find all valid words that can be formed using the 7 letters available.

-Find all permutations and check if it is contained in the dictionary.

-Add these words to a priority queue using the word point value (without modifiers) as a key.

(Each letter has it's own point value, total points of any word equals equals the sum of all points of the letters + any modifiers the letters are placed on: Tripple Letter, Tripple Word, Double Letter, Double Word)

-For our preliminary heuristic, we can ignore the modifiers.

-At some point, we'll have to include the points with modifiers.

Words can also be formed by using existing tiles/letters on the game board. We'll have to iterate through each letter on the board and add it to our pool of currently available letters. Then recompute all  valid words. 

After some analysis, we can probably make inferences on how to algorithmitically simply this process.







...
