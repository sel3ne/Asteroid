# Asteroid
Asteroid game :)

## Arch Linux

### Building and Running

Install the `sfml` package.

To run:
`g++ asteroid.cpp globalStuff.cpp main.cpp -o asteroid -lsfml-graphics -lsfml-window -lsfml-system && ./asteroid`

### Play
Use the arrow keys to stir the ship. Use space to shoot at the asteroids. If you shoot a heart, it will disappear. To get extra lives you need to collect the heart. To level up you need to destroy all the asteroids. The leaderboard will probably not write your name, unless you change that in the main.cpp file on line 436.

Have fun :)
