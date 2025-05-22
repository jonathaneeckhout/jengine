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
git clone https://github.com/yourname/jengine.git
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