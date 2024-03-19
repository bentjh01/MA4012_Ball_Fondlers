# MA4012 Ball_Fondlers

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

## Folders

### roboC_ws

- main workspace for the final code of the robot.

### unit_tests

#### motor_control

- tests the motors motion
- tune the closed loop and open loop control of servo and drive motors

#### localisation

- tests the odometry functionality of the robot
- tune the filter gains for the alpha-beta filters

### sensors

- tests the sensor readings of all sensors
- tune the cutoff frequencies of filters
- tune the threshold values of sensors

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

## Links

- [Meeting Minutes and Agenda](./meetingMinutesAndAgenda/)
