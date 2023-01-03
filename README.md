# CPU Emulator

CPU emulator written in C++

## How to clone this repository?

The easiest way is to clone the entire repository, including submodules, with one command:

```bash
# -j8 is an optional parameter that specifies
# how many cores can be used in cloning.
git clone -j8 --recurse-submodules git@github.com:RISCie-CPU/cpu-cpp-emulator.git
```

The second option is to use the basic `git clone url_to_repo` and then add commands to initialize and download submodules:

```bash
# cloning a repository without submodules
git clone git@github.com:RISCie-CPU/cpu-cpp-emulator.git
# the following command initializes the submodules
git submodule init
# the last command clone the submodules
git submodule update
```

## Compilation

Compilation is built on a Makefile, run as follows:

```bash
# it is necessary to be in the folder where the Makefile is located
make
```

Compilation requires the `png.h` library to be installed on the system, this can be achieved on debian derivatives as follows:

```bash
sudo apt install libpng-dev
```
