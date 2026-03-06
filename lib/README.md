# lib/

This directory contains third-party dependencies.

## Required Libraries

### MinHook
- **Purpose**: Function hooking
- **Source**: https://github.com/TsudaKageyu/minhook
- **License**: BSD 2-Clause
- **Installation**: 
  ```bash
  git clone https://github.com/TsudaKageyu/minhook.git
  cd minhook
  mkdir build && cd build
  cmake ..
  cmake --build . --config Release
  ```

### Kiero
- **Purpose**: DirectX hooking
- **Source**: https://github.com/Rebzzel/kiero
- **License**: MIT
- **Installation**: Header-only, just copy `kiero.h` and `kiero.cpp`

### libhat (Optional)
- **Purpose**: Memory utilities (member_at helper)
- **Source**: https://github.com/BasedInc/libhat
- **License**: MIT
- **Installation**: Header-only

## Directory Structure

```
lib/
├── minhook/
│   ├── include/
│   └── lib/
├── kiero/
│   ├── kiero.h
│   └── kiero.cpp
└── libhat/
    └── include/
```

## CMakeLists.txt

Add to `lib/CMakeLists.txt`:

```cmake
# MinHook
add_subdirectory(minhook)

# Kiero
add_library(kiero STATIC
    kiero/kiero.cpp
    kiero/kiero.h
)
target_include_directories(kiero PUBLIC kiero)

# libhat (header-only)
add_library(libhat INTERFACE)
target_include_directories(libhat INTERFACE libhat/include)
```
