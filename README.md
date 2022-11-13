# X16 C Examples

This repository aims to provide C examples for the Commander X16 for interacting with low level stuff in a intuitive way. The compiler used is [CC65](https://cc65.github.io/getting-started.html).

Disclaimer: I'm a newcomer and this repository is under development.

## Compiling
### sprites.c
```
./png2sprite.py -n arrow_data arrow.png arrow_data.inc
cl65 -t cx16 -O -o sprites.prg sprites.c
```
## Running
You can test the examples with the following commands using the [Commander X16 emulator](https://github.com/commanderx16/x16-emulator):
```
EMULATOR_PATH/x16emu -prg FILENAME.prg -run -scale 2 -quality nearest
```

## Todo
* ~~Sprites~~
* Tiles
* Keyboard
* Gamepad
* Sounds
* Music

## See also
* [VERA Programmer's Reference](https://github.com/commanderx16/x16-docs/blob/master/VERA%20Programmer's%20Reference.md) for understanding what specific addresses do and how they're structured
* [x16-demo](https://github.com/commanderx16/x16-demo) - demo I've learned from before making this (also where I got the png2sprite.py tool from)
* [CC65-Advanced-Optimizations](https://github.com/ilmenit/CC65-Advanced-Optimizations) - optimizations to be considered when making more advanced projets
