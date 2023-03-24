# Path Planning Visualizer in C++

## Getting started
This project makes use of C++ and SFML (Simple and Fast Multimedia Library). All run instructions assume the user is running on Ubuntu Linux 20.04. First, clone this repository to a designated location on your PC.
```
git clone git@github.com:sziselman/Path-Planning-Visualizer.git
```
Next, make sure that SFML is installed on your PC.
```
sudo apt-get install libsfml-dev
```

## Usage
Open a terminal, navigate to the repository, and run the executable.
```
cd /path/to/repo/
./path_planning_visualizer
```
A window will pop-up on the screen. To add obstacles, right click on an unoccuppied tile. To change the start (noted in crimson) and the goal (noted in pink), left click on the respective tiles and left click on an unoccuppied tile. To start the A* search implementation, press the Enter button.
<img src="img/astar.gif"/>