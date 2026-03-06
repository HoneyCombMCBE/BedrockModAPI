# Getting Started with BedrockModAPI

This guide will walk you through creating your first Minecraft Bedrock mod using BedrockModAPI.

## Prerequisites

- Windows 10/11 (64-bit)
- Visual Studio 2022 or later (with C++ desktop development)
- CMake 3.24 or later
- Minecraft Bedrock Edition 1.21.11X

## Building the API

1. Clone the repository:
```bash
git clone https://github.com/yourusername/BedrockModAPI.git
cd BedrockModAPI
```

2. Build with CMake:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

3. The compiled `BedrockModAPI.dll` will be in `build/bin/Release/`

## Creating Your First Mod

### Step 1: Project Setup

Create a new directory for your mod:
```bash
mkdir MyFirstMod
cd MyFirstMod
```

Create `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.24.0)
project(MyFirstMod)

set(CMAKE_CXX_STANDARD 20)

# Find BedrockModAPI
find_package(BedrockModAPI REQUIRED)

# Create mod DLL
add_library(MyFirstMod SHARED
    src/main.cpp
)

target_link_libraries(MyFirstMod 
    BedrockModAPI::BedrockModAPI
)
```

### Step 2: Write Your Mod

Create `src/main.cpp`:
```cpp
#include <bedrock/api.h>
#include <bedrock/core/events.h>

using namespace Bedrock;

class MyFirstMod : public Mod {
public:
    MyFirstMod() : Mod("MyFirstMod", "1.0.0") {}
    
    void onInitialize() override {
        log("MyFirstMod initialized!");
    }
    
    void onTick() override {
        // Get local player
        auto player = API::getLocalPlayer();
        if (!player) return;
        
        // Get player position
        auto pos = player->getPosition();
        
        // Log position every 100 ticks
        static int tickCount = 0;
        if (++tickCount >= 100) {
            log("Player position: " + 
                std::to_string(pos->x) + ", " + 
                std::to_string(pos->y) + ", " + 
                std::to_string(pos->z));
            tickCount = 0;
        }
    }
    
    void onRender() override {
        // Draw text on screen
        API::drawText("MyFirstMod Active!", 10, 10, Color::Green());
        
        // Draw player coordinates
        auto player = API::getLocalPlayer();
        if (player) {
            auto pos = player->getPosition();
            std::string coordText = "X: " + std::to_string((int)pos->x) + 
                                   " Y: " + std::to_string((int)pos->y) + 
                                   " Z: " + std::to_string((int)pos->z);
            API::drawText(coordText, 10, 30, Color::White());
        }
    }
    
    void onKeyPress(int key, bool isDown) override {
        // Press 'K' to toggle mod
        if (key == 0x4B && isDown) {  // 'K' key
            setEnabled(!isEnabled());
            log(isEnabled() ? "Mod enabled" : "Mod disabled");
        }
    }
};

// Register the mod
BEDROCK_MOD(MyFirstMod)
```

### Step 3: Build Your Mod

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Your mod DLL will be in `build/Release/MyFirstMod.dll`

### Step 4: Load Your Mod

1. Inject `BedrockModAPI.dll` into Minecraft Bedrock
2. Place your `MyFirstMod.dll` in the `mods/` folder
3. Launch Minecraft - your mod will load automatically!

## Understanding the Code

### Mod Lifecycle

```cpp
void onInitialize()  // Called once when mod loads
void onShutdown()    // Called once when mod unloads
void onEnable()      // Called when mod is enabled
void onDisable()     // Called when mod is disabled
```

### Event Hooks

```cpp
void onTick()        // Called every game tick (~20 times/sec)
void onRender()      // Called every frame (60+ times/sec)
void onKeyPress()    // Called on keyboard input
void onMouseMove()   // Called on mouse movement
void onMouseClick()  // Called on mouse click
```

### Accessing Game Data

```cpp
// Get local player
auto player = API::getLocalPlayer();

// Get level (world)
auto level = API::getLevel();

// Check if in game
if (API::isInGame()) {
    // Do something
}
```

### Rendering

```cpp
// Draw text
API::drawText("Hello!", 100, 100, Color::Red(), 1.5f);

// Draw rectangle
API::drawRect(50, 50, 200, 100, Color::Blue(), true);

// Draw line
API::drawLine(0, 0, 100, 100, Color::Green(), 2.0f);
```

## Next Steps

- Read the [API Reference](api-reference.md) for complete API documentation
- Check out [Example Mods](../examples/) for more complex examples
- Learn about the [Event System](events.md)
- Explore the [SDK Documentation](sdk.md) for game internals

## Troubleshooting

### Mod doesn't load
- Ensure `BedrockModAPI.dll` is injected first
- Check that your mod DLL is in the `mods/` folder
- Look for error messages in the console

### Crashes on startup
- Verify you're using the correct Minecraft version
- Check that all dependencies are present
- Enable debug logging to see detailed error messages

### Can't find player/level
- Make sure you're in a world (not main menu)
- Check `API::isInGame()` before accessing game objects

## Getting Help

- Join our Discord: [github.com/HoneyCombMCBE/BedrockModAPI](#)
- Report issues: [GitHub Issues](#)
- Read the FAQ: [FAQ.md](faq.md)
