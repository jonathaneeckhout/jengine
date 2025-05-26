# JEngine

A small 2D c++ game engine used for learning purposes.


## Requirements

- CMake ≥ 3.16
- C++17 compiler (`clang++`)

Example using Ubuntu
```bash
sudo apt install clang
sudo snap install cmake --classic
```

## Build instructions

Fetch the sources
```bash
git clone https://github.com/jonathaneeckhout/jengine.git
cd jengine
```

Create the build Directory
``` bash
cmake -B build
```

Build the library
``` bash
cmake --build build
```

## Resources
This engine uses a resource system where all assets (sounds, images, fonts, etc.) are embedded directly into the game's executable. This approach simplifies distribution and ensures all necessary files are bundled together.

To embed a resource, you first need to convert it into a C array. On Linux, you can do this using xxd:

```bash
xxd -i my_sound.wav > my_sound.h
```

This will generate a header file containing a C-style array of the file's contents.

Include the generated header in your project, and then load the resource using the resource manager like this:

#include "my_sound.h" // Contains my_sound_wav and my_sound_wav_len

```c++
Resources *resources = Resources::getInstance();
resources->loadResource("defaultFont", __8x8_square_roguelike_ascii_font_ttf, __8x8_square_roguelike_ascii_font_ttf_len);
```

Replace "defaultFont" and the variable names with those corresponding to your resource. This allows you to access your assets by name within the engine, with no need to load external files at runtime.
