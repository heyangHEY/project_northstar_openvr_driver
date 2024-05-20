### MSVC
```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=./install
cmake --build build --config Release
cmake --install build --config Release
```
