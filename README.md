# Game of Life
Yet another implemantation of Conway's Game of Life cellular automaton.
With C++17 and the great SFML library.

Demo : https://youtu.be/OiU8AtZTn5I


## Compilation
This program will compile on any machine running Linux, MacOS or Windows with the SFML library version 2.4.2 or higher installed, and a C++17 compiler.
You need to link against the C++ standard filesystem library.

I compiled it with GCC 8.1 and the following command line, from the project root folder :

```bash
g++ ./**/*.cpp -std=c++17 -I. -I./classes -o./build/automaton -lstdc++fs -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
```


## Usage
The program is divided in two modes : the editing and the simulation mode. It starts in editing mode, in which you can draw live cells or erase them, with the mouse. Then, on a press on the return key, the simulation starts, until you press this key again. You cannot draw in simulation mode.

#### Keys : 
+ Left click on cells to toggle their state in drawing mode
+ Right click in drawing mode to select and delete multiple cells
+ Mouse Wheel or PageUp/PageDown to Zoom in and out
+ '+' and '−' key to speed up / slow down the simulation
+ Return to switch from drawing to simulation mode
+ Escape for the quit menu.
+ Z to set back the default zoom level.


## A word
This program needs refactoring and the addition of numerous features like a proper UI, app states, messaging system between classes, and some other cool stuff.
The primary goal was to obtain a working "Game of Life" simulation. This is achieved, so it is published as is for now.

Many thanks to SFML's contributors, it is really a great and fun library to use.


## License
All the code in this repository is licensed under the MIT license. You can find a copy of this license in the LICENSE file in the root folder of the repository.
