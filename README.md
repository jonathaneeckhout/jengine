# JEngine

A small 2D c++ game engine used for learning purposes.


## Requirements

- CMake ≥ 3.16
- C++17 compiler (`clang++`)
- Make (optional, but recommended for Unix-like systems)


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

Install the library (default to /usr/local)
``` bash
sudo cmake --install build
```

To install elsewhere
```bash
sudo cmake --install build --prefix /your/custom/path
```

To remove installed files

```bash
sudo cmake --build build --target uninstall
```

## Usage in other projects
To use JEngine in another CMake project
```cmake
find_package(JEngine REQUIRED)

target_link_libraries(MyApp PRIVATE JEngine::JEngine)
```
Make sure lib/cmake/JEngine is discoverable via CMAKE_PREFIX_PATH.