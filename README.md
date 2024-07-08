# MankalaEngine

MankalaEngine is an engine used for creating computerized
opponents for Mancala variants.

## Building the Source

To build MankalaEngine, follow this steps:

```sh
git clone https://invent.kde.org/joaotgouveia/mankalaengine.git
cd mankalaengine
mkdir build
cmake -S . -B build
cmake --build build
```

## Running Tests

After you have built the library, you can check if everything
is working correctly by running the tests:

```sh
cd build
ctest
```

## How to use

The `examples/` folder contains usage examples, including a simple
TUI that allows a user to play a game against a computerized opponent.
You can also build the Doxygen documentation by specifying the cmake
option `BUILD_DOCS`.

## Comparing different move selection functions

The `benchmark/` folder contains a utility that can be used
to compare different move selection functions.
