# Gate Keeper

[![license](http://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Blackhawk-TA/32blit-rpg/blob/master/LICENSE.md)
![Build](https://github.com/Blackhawk-TA/32blit-rpg/workflows/Build/badge.svg)
[![github](https://img.shields.io/github/release/Blackhawk-TA/32blit-rpg.svg?color=brightgreen)](https://github.com/Blackhawk-TA/TowerDefense/releases)

An RPG game called GateKeeper made for the 32blit and PicoSystem retro consoles.
It also runs on Linux, MacOS and Windows.

## Build
Linux:
```
mkdir build
cd build
cmake ..
make
```

32Blit:
```
mkdir build.stm32
cd build.stm32
cmake .. -DCMAKE_TOOLCHAIN_FILE="../32blit-sdk/32blit.toolchain"
make GateKeeper
```

PicoSystem:
```
mkdir build.pico
cd build.pico
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../32blit-sdk/pico.toolchain -DPICO_BOARD=pimoroni_picosystem
make
```

## Sprites
All sprites were created by [Gif](https://gif-superretroworld.itch.io/), [Noiracide](https://noiracide.itch.io/) and [TheRoro](https://drpixelo.itch.io/).
The packs can be found here: https://gif-superretroworld.itch.io/ \
All sprites are licensed under the Creative Commons Attribution v4.0 International license. \
I modified all character sprites to fit the 16x16 tile bounds.
The white tiles with borders used for in game menus were made by me.
