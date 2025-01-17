# TETRIS CORE
A (not perfect) clone of NES Tetris with a 2 player mode

![Tetris-Core](https://i.imgur.com/VMui1fl.png)

## Getting Started on WINDOWS
Download the latest Release and launch the executable. Windows Defender might think that the executable is a Trojan and will refuse to execute it.

## Getting Started on LINUX
Download the latest Release and launch the executable. The executable is statically built with SDL2 so you shouldn't have any dependencies issues, but just in case,
here's a small list of external dependencies:
* LibGL
* Libm
* Libfreetype
* libz

## Controls

### One Player:

LEFT -> 'A', 'Left-Arrow'

RIGHT -> 'D', 'Right-Arrow'

ROTATE CLOCKWISE -> 'W'. 'X', 'Up-Arrow'

ROTATE COUNTER CLOCKWISE -> 'Z'

DOWN ACCELERATION -> 'S', 'Down-Arrow'

PAUSE GAME -> 'ESCAPE'

SELECT -> 'ENTER/RETURN'

### Two Player:

**PLAYER 1**

LEFT -> 'A'

RIGHT -> 'D'

ROTATE CLOCKWISE -> 'W'. 'X'

ROTATE COUNTER CLOCKWISE -> 'Z'

DOWN ACCELERATION -> 'S'

**PLAYER 2**

LEFT -> 'Left-Arrow'

RIGHT -> 'Right-Arrow'

ROTATE CLOCKWISE -> 'Up-Arrow'

ROTATE COUNTER CLOCKWISE -> 'M'

DOWN ACCELERATION -> 'Down-Arrow'

## Current Features
* Two Player Mode
* No Hard Drop
* No Wall Kick
* NRS
* Bag Randomizer (smaller chance to get the same piece twice in a row)
* Classic Tetris Score and Level System
* Pieces fall at 200m/s with 10m/s acceleration (piece acceleration happens at the same levels that the NES Tetris acceleration happens)

## Future Features
* Save Top Score
* Add Statistics on Falling Pieces
* Add Controller Support
* Add Down Acceleration points
* Add Multiplayer
