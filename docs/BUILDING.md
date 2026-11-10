# Building and releasing

This project uses CMake and an out-of-source build. Keeping generated files in
a separate directory prevents compiler output and CMake caches from polluting
the source tree.

## Reproducible local build

Configure and build with:

```text
cmake -S . -B build-local -DCMAKE_BUILD_TYPE=Release
cmake --build build-local --parallel
```

On Visual Studio generators, use:

```text
cmake -S . -B build-local -G "Visual Studio 17 2022" -A x64
cmake --build build-local --config Release --parallel
```

The `POST_BUILD` commands in the root [`CMakeLists.txt`](../CMakeLists.txt)
copy every runtime asset to the executable directory. This works with both
single-configuration generators (Makefiles/Ninja) and multi-configuration
generators (Visual Studio).

## Clean rebuild

If a build directory was created on another machine or with another generator,
do not reuse it. Delete only that build directory and configure again:

```bash
rm -rf build-local
cmake -S . -B build-local -DCMAKE_BUILD_TYPE=Release
cmake --build build-local --parallel
```

In PowerShell:

```powershell
Remove-Item -Recurse -Force build-local
cmake -S . -B build-local -DCMAKE_BUILD_TYPE=Release
cmake --build build-local --parallel
```

## Packaging

Install the executable and assets into a clean directory:

```bash
cmake --install build-local --prefix dist
```

For Visual Studio:

```powershell
cmake --install build-local --config Release --prefix dist
```

The resulting `dist` directory is the portable runtime bundle. Keep the
executable and its copied assets together.

## Release checklist

1. Configure from a clean build directory.
2. Build the Release configuration.
3. Confirm that the executable and these assets are present together:
   `ATTACK 1.png`, `IDLE.png`, `RUN.png`, `bgmusic.wav`, `map.png`, and
   `mapCollision.png`.
4. Launch the executable from its output directory.
5. Do not commit `build-*`, `dist`, compiler output, or local save files.
6. Add a project license before publishing binaries.
