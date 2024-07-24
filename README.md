# MankalaEngine

MankalaEngine is an engine used for creating computerized
opponents for Mancala variants.

## Building The Source

To build MankalaEngine, follow this steps:

```sh
git clone https://invent.kde.org/joaotgouveia/mankalaengine.git
cd mankalaengine
mkdir build
cmake -S . -B build
cmake --build build
```

You only need CMake and a C++ compiler to build the library.

### Running The Tests

After you have built the library, you can check if everything
is working correctly by running the tests:

```sh
cd build
ctest
```

## Usage

The `examples/` folder contains usage examples, including a simple
TUI that allows a user to play a game against a computerized opponent.
You can also build the Doxygen documentation by specifying the cmake
option `BUILD_DOCS`.

### Installing

If you've already followed the steps in [Building The Source](#Building The Source),
you can install the library by running:

```sh
cmake --build build --target install
```

### Adding It To Your Project

If you've the library installed, you can now add it to your project.
Add the following lines to your `CMakeLists.txt`:

```
find_package(MankalaEngine REQUIRED)
add_executable(MyApp myapp.cpp)
target_link_libraries(MyApp MankalaEngine::MankalaEngine)
```

### Comparing Different Move Selection Functions

The `benchmark/` folder contains a utility that can be used
to compare different move selection functions.
