# ARDUINO WORKSPACE

## Getting Started

### Setup

1. Install Arduino IDE
2. Install a text editor e.g. VSCode, nvim etc
3. Install Github
4. Download the repository `git clone https://github.com/bentjh01/MA4012_Ball_Fondlers.git`
5. Create your own branch `git checkout -b my_branch`
6. Update the repository with new branch `git push --set-upstream origin my_branch`

### Uploading Code

1. open arduino_ws.ino in ArduinoIDE
2. upload

### Development

1. Switch to your branch `git checkout my_branch`
2. create new folder e.g. feature_name
3. create source and header files e.g. feature_name.cpp and feature_name.h
4. Prevent recursion of header files i.e. `#ifndef FEATURE_NAME_H` ...
5. Include necessary libraries in header
6. Include header file in `main.h`
7. Include header file in source file i.e. `#include "feature_name.h"`
8. Start coding in source file
9. Add functions and variables to header file e.g. `void blink_led(int duration)`

## Dependencies

- Arduino.h
- Wire.h
