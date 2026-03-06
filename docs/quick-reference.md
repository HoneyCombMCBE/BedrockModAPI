# Quick Reference

Quick reference guide for common BedrockModAPI tasks.

## Basic Mod Template

```cpp
#include <bedrock/api.h>

class MyMod : public Bedrock::Mod {
public:
    MyMod() : Mod("MyMod", "1.0.0") {}
    
    void onInitialize() override {
        log("Mod loaded!");
    }
    
    void onTick() override {
        // Game logic (20 times/sec)
    }
    
    void onRender() override {
        // Rendering (60+ times/sec)
    }
    
    void onKeyPress(int key, bool isDown) override {
        // Handle input
    }
};

BEDROCK_MOD(MyMod)
```

## Common Tasks

### Get Player Position
```cpp
auto player = API::getLocalPlayer();
if (player) {
    auto pos = player->getPosition();
    float x = pos->x;
    float y = pos->y;
    float z = pos->z;
}
```

### Modify Player Velocity
```cpp
auto player = API::getLocalPlayer();
if (player) {
    auto vel = player->getVelocity();
    vel.y += 0.5f;  // Jump boost
    player->setVelocity(vel);
}
```

### Draw Text
```cpp
API::drawText("Hello World", 10, 10, Color::White(), 1.0f);
```

### Draw Rectangle
```cpp
// Filled
API::drawRect(50, 50, 200, 100, Color::Red(), true);

// Outline
API::drawRect(50, 50, 200, 100, Color::Blue(), false);
```

### Draw Line
```cpp
API::drawLine(0, 0, 100, 100, Color::Green(), 2.0f);
```

### Check Key State
```cpp
if (API::isKeyDown(VK_SPACE)) {
    // Space is pressed
}

if (API::isKeyDown(0x57)) {  // 'W' key
    // W is pressed
}
```

### Check Mouse Button
```cpp
if (API::isMouseButtonDown(0)) {  // Left click
    // Left mouse button is down
}
```

### Get Screen Size
```cpp
auto screenSize = API::getScreenSize();
float width = screenSize.x;
float height = screenSize.y;
```

### Get Mouse Position
```cpp
auto mousePos = API::getMousePos();
float x = mousePos.x;
float y = mousePos.y;
```

### Toggle Mod On/Off
```cpp
void onKeyPress(int key, bool isDown) override {
    if (key == VK_F1 && isDown) {
        setEnabled(!isEnabled());
    }
}
```

### Log Messages
```cpp
log("Info message");
logWarning("Warning message");
logError("Error message");
```

### Check If In Game
```cpp
if (API::isInGame()) {
    // Player is in a world
}
```

### Get Player Name
```cpp
auto player = API::getLocalPlayer();
if (player) {
    std::string name = player->getPlayerName();
}
```

### Get Player Health
```cpp
auto player = API::getLocalPlayer();
if (player) {
    float health = player->getHealth();
    float maxHealth = player->getMaxHealth();
}
```

### Check Player State
```cpp
auto player = API::getLocalPlayer();
if (player) {
    bool onGround = player->isOnGround();
    bool sneaking = player->getFlag(ActorFlag::Sneaking);
    bool sprinting = player->getFlag(ActorFlag::Sprinting);
}
```

### Get Level Info
```cpp
auto level = API::getLevel();
if (level) {
    std::string worldName = level->getWorldName();
    auto players = level->getPlayers();
}
```

## Virtual Key Codes

Common key codes for `onKeyPress` and `isKeyDown`:

```cpp
VK_SPACE      // Space bar
VK_RETURN     // Enter
VK_ESCAPE     // Escape
VK_SHIFT      // Shift
VK_CONTROL    // Ctrl
VK_MENU       // Alt
VK_TAB        // Tab
VK_BACK       // Backspace

// Letters (A-Z)
0x41 - 0x5A   // 'A' = 0x41, 'Z' = 0x5A

// Numbers (0-9)
0x30 - 0x39   // '0' = 0x30, '9' = 0x39

// Function keys
VK_F1 - VK_F12

// Arrow keys
VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN
```

## Colors

```cpp
Color::White()   // (1, 1, 1, 1)
Color::Black()   // (0, 0, 0, 1)
Color::Red()     // (1, 0, 0, 1)
Color::Green()   // (0, 1, 0, 1)
Color::Blue()    // (0, 0, 1, 1)

// Custom color
Color(0.5f, 0.5f, 0.5f, 1.0f)  // Gray
Color(1.0f, 1.0f, 0.0f, 0.5f)  // Semi-transparent yellow
```

## Build Commands

```bash
# Configure
cmake ..

# Build Release
cmake --build . --config Release

# Build Debug
cmake --build . --config Debug

# Clean
cmake --build . --target clean

# Install
cmake --install . --prefix install
```

## CMakeLists.txt for Mod

```cmake
cmake_minimum_required(VERSION 3.24.0)
project(MyMod)

set(CMAKE_CXX_STANDARD 20)

find_package(BedrockModAPI REQUIRED)

add_library(MyMod SHARED main.cpp)
target_link_libraries(MyMod BedrockModAPI::BedrockModAPI)
```

## Debugging

### Attach Debugger (Visual Studio)
1. Debug → Attach to Process
2. Select Minecraft.Windows.exe
3. Set breakpoints in your mod code

### View Debug Output
Use DebugView++ to see `log()` messages:
1. Download DebugView++
2. Run as Administrator
3. Capture → Capture Global Win32

### Common Issues

**Mod doesn't load**
- Check `BedrockModAPI.dll` is injected
- Verify mod is in `mods/` folder
- Check for `CreateMod` export

**Crashes on startup**
- Build in Debug mode
- Attach debugger
- Check for null pointers

**Can't find player**
- Ensure you're in a world
- Check `API::isInGame()` first

## Performance Tips

- Avoid heavy operations in `onRender()`
- Cache frequently accessed data
- Use `onTick()` for game logic, not `onRender()`
- Check `isEnabled()` before doing work
- Minimize string allocations

## Best Practices

1. **Always check for null**
   ```cpp
   auto player = API::getLocalPlayer();
   if (!player) return;
   ```

2. **Use early returns**
   ```cpp
   if (!isEnabled()) return;
   if (!API::isInGame()) return;
   ```

3. **Cache expensive calls**
   ```cpp
   static auto screenSize = API::getScreenSize();
   ```

4. **Handle errors gracefully**
   ```cpp
   try {
       // Risky operation
   } catch (const std::exception& e) {
       logError(e.what());
   }
   ```

5. **Clean up resources**
   ```cpp
   void onShutdown() override {
       // Free resources
   }
   ```
