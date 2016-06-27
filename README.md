# ZombieChase, Final Project, Developed for CPSC 870: Object-Oriented Development

## Description

This repository contains the final milestone for CPSC 870: Object-Oriented Development.  CPSC 870 was a
semester long course on object-oriented development within the context of video game development.

The game was developed in OO C++ using several external libraries from the SDL (SimpleDirect Media Layer) libraries.  The game application allows the user to select from one of two games to play.  The first game, originally designed over the first 12 weeks of the semester, ZombieChase, is a top-down shooter/zombie game.  The player may opt to play as a human, moving around the map shooting zombies, or a zombie, moving around the map attempting to eat the humans.  Score is tabulated based on how many zombies or humans are killed.  Killing a human spawns a new zombie.

The second game, Zombie Defense, is a 'tower defense' style game.  Prior to the start of the game, the player places stationary humans around the map.  Waves of zombies attempt to move from the right side of the screen to the left to eat the damsel in distress.  The station humans shoot bullets at the zombies at a static interval.  The player may place additional human defense towers as they kill more zombies.

Both games support the following features:
  * Save Game
  * Load Game
   
The games demonstrate the following game features:
  * Animated Sprites
  * Sprite explosions
  * Zombie AI
  * Human AI
  * Parralax Scrolling with Viewport
  * Sound

All graphical development assets and source code were produced by the author.  The sounds were obtained via open source license.  The game was verified at completion time to be memory leak free, excluding memory leaks included from third-party libraries (SDL-Image, I'm looking at you) with the valgrind virtual memory analzyer.  The makefile provides options for testing for memory leaks with valgrind, as well as xml validation using xmllint.  The game was developed on a CentOS Distribution of Linux using the GNU G++ compiler and *should* be warning free using -Wall and -pedantic G++ flags.

The project makes novel use of design patterns, which was a central learning objective of the course.  This includes Singletons for data input/output, storage of game objects.  The project uses factories that generate flyweight objects to reduce the memory useage by duplicate graphical objects.  The project uses a Composite pattern to handle coarse game state and menu screens.

Seeing as the code is 4+ years old, I make no guarantees on compatibility with new versions of G++, new versions of SDL libraries or the stability of the code.

## Installation

1. Clone the code to your computer.
2. Install the following SDL libraries: SDL, SDL-Image, SDL-Graphic, SDL-Sound
3. Compile using the makefile

## Usage
1. Run the program with syntax ./executable -- No input flags or parameters are necessary.
2. Have fun shooting zombies.

## Contributing

Please do not contribute to this project.  This compiler was a pedagogical exercise in OO development for CPSC 870: Object-Oriented Development.  It is not meant to be extended or contributed to, and is functionally a dead project.  It is only here for demonstrable reasons.

## Credits

Credit goes to me, myself, Yates Monteith, for the development of this project.

## License

GNU GPL v2.0.  See License
