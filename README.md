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
