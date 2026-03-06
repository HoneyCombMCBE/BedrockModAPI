# Build Instructions

## Prerequisites

### Required
- **Windows 10/11** (64-bit)
- **Visual Studio 2022** or later with C++ desktop development
- **CMake 3.24** or later
- **Git**

### Optional
- **Visual Studio Code** with CMake Tools extension
- **Ninja** build system (faster builds)

## Dependencies

Before building, you need to set up the dependencies in the `lib/` folder.

### 1. MinHook

```bash
cd lib
git clone https://github.com/TsudaKageyu/minhook.git
cd minhook
mkdir build && cd build
cmake ..
cmake --build . --config Release
cd ../..
```

### 2. Kiero

```bash
cd lib
git clone https://github.com/Rebzzel/kiero.git
cd ..
```

### 3. libhat (Optional)

```bash
cd lib
git clone https://github.com/BasedInc/libhat.git
cd ..
```

## Building BedrockModAPI

### Using CMake (Command Line)

```bash
# From project root
mkdir build
cd build

# Configure
cmake ..

# Build Release
cmake --build . --config Release

# Build Debug
cmake --build . --config Debug
```

Output will be in `build/bin/Release/` or `build/bin/Debug/`

### Using Visual Studio

1. Open Visual Studio 2022
2. File → Open → CMake...
3. Select `CMakeLists.txt` from project root
4. Visual Studio will configure automatically
5. Build → Build All (Ctrl+Shift+B)

### Using Visual Studio Code

1. Install CMake Tools extension
2. Open project folder
3. Press Ctrl+Shift+P → "CMake: Configure"
4. Press Ctrl+Shift+P → "CMake: Build"

## Building Example Mods

Example mods are built automatically if `BUILD_EXAMPLES` is ON (default).

To build manually:

```bash
cd examples/coordinate_display
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## Build Configurations

### Release (Optimized)
```bash
cmake --build . --config Release
```
- Optimizations enabled
- No debug symbols
- Smaller binary size
- Use for distribution

### Debug (Development)
```bash
cmake --build . --config Debug
```
- No optimizations
- Full debug symbols
- Larger binary size
- Use for development and debugging

## CMake Options

```bash
# Disable example mods
cmake .. -DBUILD_EXAMPLES=OFF

# Disable documentation
cmake .. -DBUILD_DOCS=OFF

# Use Ninja generator (faster)
cmake .. -G Ninja

# Specify Visual Studio version
cmake .. -G "Visual Studio 17 2022"
```

## Troubleshooting

### CMake can't find dependencies

Make sure dependencies are in `lib/` folder:
```
lib/
├── minhook/
├── kiero/
└── libhat/
```

### Build fails with "cannot open file"

- Run Visual Studio as Administrator
- Check antivirus isn't blocking files
- Ensure all dependencies are built

### Linker errors

- Make sure you built dependencies in the same configuration (Release/Debug)
- Check that all required .lib files exist

### "MSVC not found"

Install Visual Studio 2022 with "Desktop development with C++" workload.

## Installing

After building:

```bash
cmake --install . --prefix install
```

This creates an `install/` directory with:
```
install/
├── bin/
│   └── BedrockModAPI.dll
├── lib/
│   └── BedrockModAPI.lib
└── include/
    └── bedrock/
```

## Creating a Release Package

```bash
# Build in Release mode
cmake --build . --config Release

# Create package
cpack
```

This creates a distributable package with the DLL and headers.

## Next Steps

After building:
1. Read [Getting Started](docs/getting-started.md) to create your first mod
2. Check out [Examples](examples/) for reference
3. See [API Reference](docs/api-reference.md) for complete API documentation
