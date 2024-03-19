# MA4012 Ball_Fondlers

This repos is for the MA4012 Mechatronics Engineering Design Project. The task is to build a robot that collects the most tennis balls within an arena. The robot must run autonomously to carrying out its task. The robot is built on a `VEX Cortex` and `ROBOTC` platform. Key concepts that were kept in mind is good design philosophy on all fronts; mechanical, electrical, electronic, and software.

## Navigation

[roboC_ws](./roboC_ws/) | [unitTests](./unit_tests/) | [meetingMinutesAndAgenda](./meetingMinutesAndAgenda/) | [sampleCode](./sample_code/) | [dataSheets](./dataSheets/)

## Contents

### [roboC_ws](./roboC_ws/)

- main workspace for the final code of the robot.
- all code is written in a functional manner.

#### `main.c`

- file to be opened to upload compile and upload code to robot.
- performs tasks in discrete time.

#### `config.h`

- file that contains all tunable parameters
- contains all constants

### [unitTests](./unit_tests/)

- organised into folder with `<folder_name>` with the function or feature to be tested.
  - `<folder_name>.c`
    - the main code to be compiled and uploaded
  - `<folder_name>.h`
    - constants and tunable parameters
  - `<file_name>.c`
    - the supporting function to carry out tests or to provide functionality to the robot.

##### motor_control

- tests the motors motion
- tune the closed loop and open loop control of servo and drive motors

##### localisation

- tests the odometry functionality of the robot
- tune the filter gains for the alpha-beta filters

##### sensors

- tests the sensor readings of all sensors
- tune the cutoff frequencies of filters
- tune the threshold values of sensors

### [meetingMinutesAndAgenda](./meetingMinutesAndAgenda/)

- contains markdown folder of meetings

### [sampleCode](./sample_code/)

- contains past year code

## About VEX

- ROBOTC doesnt play nice with structs 'invalid return type' [link](https://www.vexforum.com/t/robotc-return-struct/36028)
- ROBOTC doesnt recognise the difference between source and header files.
- global variables within a file only exists within that file's scope.
- global variables within a file's scope are static i.e. they retain their value.
- pragma must be in the file that is selected to be compiled i.e. `main.c`.

## GitHub Cheatsheet

### Setup

1. Install Github
2. Download the repository `git clone https://github.com/bentjh01/MA4012_Ball_Fondlers.git`
3. Create your own branch `git checkout -b my_branch`
4. Update the repository with new branch `git push --set-upstream origin my_branch`
5. switch to your branch `git checkout my_branch`

### Saving and Uploading to github

1. Update local repository `git pull`
2. Checking branch and changes `git status`
3. Stage changes `git add directory_of_changed_file`
4. Commit changes `git commit -m "some description under 5 words"`
5. Upload to the cloud `git push`

### Making Pull Requests

1. Update branch with `main` branch. `git merge main`
2. Resolve conflicts if any.
3. Make a pull request on the github page.

## Timeline

- Week 3 - Collector Design and Strategy
- Week 4 - Vehicle Design and Drive System
- Week 6 - Power supply and sensor strategy
- Week 7 - Software strategy for power, sensing, and navigation.
- Recess -
- Week 8 - independant/unit test ()
- week 9 - a moving thing
- Week 10 - Prototype ready, additonal strategies
- Week 11 - Testing, tuning and optimization
- Week 12 - Trial run

## Members

- Benjamin Teh
- Bryan Galenius
- Eunice Ong
- Fan Zifu
- Kelvin Lee
- Chen Lee
- Timothy Liu
- Hong Wei Tan
- Wilsen Lotan
- Wilson
