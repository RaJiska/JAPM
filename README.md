# JAPM (Just Another PBO Manager)
Utility allowing you to pack / unpack Bohemia Interactive's PBO files for Arma 3 game.  Implemented in C and is cross-platform Linux / Windows, this piece of software can be used in automatized scripts which may come handy for server owners.

## Features
- Pack / Unpack
- Supports Extended Header Format
- Supports Compression

## Building From Sources
#### Linux
```
$ mkdir build && cd build
$ cmake ..
$ make
```

#### Windows (cross-building)
```
$ mkdir build && cd build
$ cmake -DCMAKE_TOOLCHAIN_FILE=../windows.cmake ..
$ make
```

## USAGE
```
$ ./JAPM -h
USAGE
        ./JAPM [OPTIONS] input [output]

OPTIONS
        -h      Print this help message and discard other options
        -q      Quiet: does not print status
        -w      No warning
        -v      Display version and discard other options
```

## Credits
[SHA1 Library](https://github.com/clibs/sha1) by Steve Reid

## Thanks
- Mikero for his PBO File Format wiki page
- The various people who helped me searching how it was all working