# Game of Thorns

A small C++17 2D platformer built with [SFML 3](https://www.sfml-dev.org/).
The game includes animated player sprites, keyboard movement, jumping,
collision/death tiles, a moving enemy, background music, and a simple position
save file.

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-3.2-8CC445)
![Build](https://img.shields.io/badge/build-CMake-064F8C?logo=cmake&logoColor=white)

## Features

- Responsive platformer movement with keyboard controls
- Sprite-sheet animations for idle, running, and attacking
- Pixel-based collision map with solid and death tiles
- Enemy that patrols a bounded area
- Background music and automatic position saving
- Reproducible, out-of-source CMake builds
- Bundled SFML dependency for offline configuration

## Requirements

Install the following tools before building:

- CMake 3.20 or newer
- A C++17 compiler
  - Linux: GCC 10+ or Clang 12+
  - Windows: Visual Studio 2022 (Desktop C++ workload) or MinGW-w64
- Git, if cloning the repository

No system SFML installation is required; the compatible SFML source is included
in [`libs/SFML`](./libs/SFML).

## Build and run

All commands below work from Linux shells and Windows PowerShell. Use a fresh
build directory when switching operating systems, compilers, or generators.

### Linux

```bash
cmake -S . -B build-linux -DCMAKE_BUILD_TYPE=Release
cmake --build build-linux --parallel
./build-linux/platformer
```

### Windows with Visual Studio

```powershell
cmake -S . -B build-windows -G "Visual Studio 17 2022" -A x64
cmake --build build-windows --config Release --parallel
.\build-windows\Release\platformer.exe
```

### Windows with MinGW

```powershell
cmake -S . -B build-windows -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build-windows --parallel
.\build-windows\platformer.exe
```

The build copies all required images and audio beside the executable, so the
commands above can be run without manually copying assets.

For a relocatable install tree:

```bash
cmake --install build-linux --prefix dist
```

On a multi-config generator, add `--config Release` to the install command.

## Controls

| Action | Keys |
| --- | --- |
| Move left/right | `A` / `D` or arrow keys |
| Jump | `W`, `Up`, or `Space` |
| Attack | `J` |
| Reset position | `R` |
| Quit | Close the game window |

The current player position is saved as `savefile.txt` next to the executable
when the game window closes.

## Project layout

```text
.
├── CMakeLists.txt       # Cross-platform build and asset staging
├── src/
│   ├── main.cpp         # Game loop and save/load behavior
│   ├── Player.h         # Player movement and animation
│   ├── TileManager.h    # Map loading and collision detection
│   └── *.png, *.wav     # Runtime assets
└── libs/SFML/           # Bundled SFML dependency
```

Additional build notes and troubleshooting are in
[`docs/BUILDING.md`](./docs/BUILDING.md).

## Troubleshooting

- **CMake reports a different source/build directory:** remove the build
  directory and configure a new one. CMake caches absolute paths.
- **The window opens but assets are missing:** run the executable from the
  build configuration's output directory, or use the provided build commands
  so CMake can stage the assets beside it.
- **Visual Studio cannot find a configuration:** pass
  `--config Debug` or `--config Release` to build and install commands.

## Contributing

Keep generated files out of commits, build out of source, and verify both
configuration and compilation before opening a pull request:

```bash
cmake -S . -B build-check -DCMAKE_BUILD_TYPE=Release
cmake --build build-check --parallel
```

## License

This project does not currently declare a project-level license. Add one before
distributing the game. SFML remains under the license included in
[`libs/SFML`](./libs/SFML).
