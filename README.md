# Game of Life
Yet another implemantation of Conway's Game of Life cellular automaton. With C++ and the great SFML library

Demo : https://youtu.be/OiU8AtZTn5I

## Compiling
This program was written in an environment using SFML 2.4.2 and GCC 5.4. The code use C++14 features.
Here is the complete command line used to compile this program, from the project root folder :

```bash
g++ ./**/*.cpp -std=c++14 -I/usr/local/include/ -I. -I./classes -o./build/automaton -L/usr/local/lib -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
```

## Using
#### Keys : 
+ Mouse Wheel or PageUp/PageDown to Zoom in and out
+ '+' and '−' key to speed up / slow the simulation
+ Enter to switch from drawing to simulation mode
+ Left click on cells to toggle their state in drawing mode
+ Right click in drawing mode to select and delete multiple cells at once
+ Escape for the quit menu.


## A word
This program needs a lot of polishing, code refactoring, debugging. The goal was to achieve a working "Game of Life" simulation, so it is published as is.
There is an error in the implementation of the "infinite grid", which has an impact on the simulation. That bug will be corrected soon.
Many thanks to SFML's contributors, it really is a great and fun library to use.


## License
All the code in this repository is licensed under the MIT license. You can find a copy of this license in the LICENSE file in the root folder of the repository.
