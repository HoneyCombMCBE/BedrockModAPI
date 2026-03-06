# API Reference

Complete API reference for BedrockModAPI.

## Table of Contents

- [Core API](#core-api)
- [Mod Class](#mod-class)
- [Events](#events)
- [SDK](#sdk)
- [Memory](#memory)
- [Hooks](#hooks)

---

## Core API

### Bedrock::API Namespace

Main API functions for accessing game state and rendering.

#### Game Access

```cpp
LocalPlayer* getLocalPlayer()
```
Returns the local player instance, or `nullptr` if not in game.

```cpp
Level* getLevel()
```
Returns the current level (world), or `nullptr` if not in game.

```cpp
bool isInGame()
```
Returns `true` if player is in a world (not in menu).

#### Rendering

```cpp
void drawText(const std::string& text, float x, float y, 
              const Color& color = Color::White(), float scale = 1.0f)
```
Draw text on screen at specified position.

**Parameters:**
- `text` - Text to display
- `x, y` - Screen coordinates (top-left origin)
- `color` - Text color (default: white)
- `scale` - Text scale multiplier (default: 1.0)

```cpp
void drawRect(float x, float y, float width, float height, 
              const Color& color, bool filled = true)
```
Draw a rectangle on screen.

**Parameters:**
- `x, y` - Top-left corner position
- `width, height` - Rectangle dimensions
- `color` - Rectangle color
- `filled` - Fill rectangle (true) or draw outline (false)

```cpp
void drawLine(float x1, float y1, float x2, float y2, 
              const Color& color, float thickness = 1.0f)
```
Draw a line on screen.

**Parameters:**
- `x1, y1` - Start position
- `x2, y2` - End position
- `color` - Line color
- `thickness` - Line thickness in pixels

#### Screen Info

```cpp
Vec2<float> getScreenSize()
```
Returns the screen resolution (width, height).

```cpp
Vec2<float> getMousePos()
```
Returns the current mouse position.

#### Input

```cpp
bool isKeyDown(int key)
```
Check if a keyboard key is currently pressed.

**Parameters:**
- `key` - Virtual key code (e.g., `VK_SPACE`, `0x41` for 'A')

```cpp
bool isMouseButtonDown(int button)
```
Check if a mouse button is currently pressed.

**Parameters:**
- `button` - Button index (0=left, 1=right, 2=middle)

---

## Mod Class

Base class for all mods. Inherit from this to create your mod.

### Constructor

```cpp
Mod(const std::string& name, const std::string& version)
```

**Example:**
```cpp
class MyMod : public Bedrock::Mod {
public:
    MyMod() : Mod("MyMod", "1.0.0") {}
};
```

### Lifecycle Hooks

```cpp
virtual void onInitialize()
```
Called once when the mod is loaded. Use for initialization.

```cpp
virtual void onShutdown()
```
Called once when the mod is unloaded. Use for cleanup.

```cpp
virtual void onEnable()
```
Called when the mod is enabled.

```cpp
virtual void onDisable()
```
Called when the mod is disabled.

### Event Hooks

```cpp
virtual void onTick()
```
Called every game tick (~20 times per second).

```cpp
virtual void onRender()
```
Called every frame (60+ times per second). Use for rendering.

```cpp
virtual void onKeyPress(int key, bool isDown)
```
Called when a keyboard key is pressed or released.

**Parameters:**
- `key` - Virtual key code
- `isDown` - `true` if pressed, `false` if released

```cpp
virtual void onMouseMove(float x, float y)
```
Called when the mouse moves.

**Parameters:**
- `x, y` - New mouse position

```cpp
virtual void onMouseClick(int button, bool isDown)
```
Called when a mouse button is clicked.

**Parameters:**
- `button` - Button index (0=left, 1=right, 2=middle)
- `isDown` - `true` if pressed, `false` if released

### Utility Methods

```cpp
void log(const std::string& message)
```
Log an info message to console.

```cpp
void logError(const std::string& message)
```
Log an error message to console.

```cpp
void logWarning(const std::string& message)
```
Log a warning message to console.

```cpp
const std::string& getName() const
```
Get the mod name.

```cpp
const std::string& getVersion() const
```
Get the mod version.

```cpp
bool isEnabled() const
```
Check if the mod is currently enabled.

```cpp
void setEnabled(bool enabled)
```
Enable or disable the mod.

---

## Events

Event classes for advanced event handling.

### Event Types

```cpp
enum class EventType {
    Tick,
    Render,
    KeyPress,
    MouseMove,
    MouseClick,
    PacketReceive,
    PacketSend,
}
```

### Base Event

```cpp
class Event {
public:
    virtual EventType getType() const = 0;
    
    bool cancelled;
    void cancel();
}
```

### TickEvent

```cpp
class TickEvent : public Event
```
Fired every game tick.

### RenderEvent

```cpp
class RenderEvent : public Event {
public:
    float deltaTime;  // Time since last frame
}
```
Fired every frame.

### KeyEvent

```cpp
class KeyEvent : public Event {
public:
    int key;
    bool isDown;
    bool isRepeat;
}
```
Fired on keyboard input.

### MouseMoveEvent

```cpp
class MouseMoveEvent : public Event {
public:
    float x, y;
    float deltaX, deltaY;
}
```
Fired on mouse movement.

### MouseClickEvent

```cpp
class MouseClickEvent : public Event {
public:
    int button;
    bool isDown;
    float x, y;
}
```
Fired on mouse click.

---

## SDK

Game SDK classes for accessing Minecraft internals.

### Actor

Base entity class.

```cpp
Vec3<float>* getPosition()
Vec3<float> getVelocity()
void setPosition(const Vec3<float>& pos)
void setVelocity(const Vec3<float>& vel)

Vec2<float> getRotation()
void setRotation(const Vec2<float>& rot)

bool getFlag(ActorFlag flag)
void setFlag(ActorFlag flag, bool value)
bool isOnGround()

float getHealth()
float getMaxHealth()
void setHealth(float health)

std::string* getNametag()
void setNametag(const std::string& name)

Level* getLevel()
bool isValid()
```

### Player

Player entity (extends Actor).

```cpp
std::string& getPlayerName()
PlayerInventory* getInventory()
ItemStack* getSelectedItem()
Gamemode* getGamemode()
float getHunger()
float getSaturation()
```

### LocalPlayer

The client's player (extends Player).

```cpp
void applyTurnDelta(Vec2<float>* delta)
MoveInputComponent* getMoveInput()
```

### Level

World/level class.

```cpp
std::vector<Player*> getPlayers()
std::vector<Actor*> getRuntimeActorList()
std::string getWorldName()
BlockSource* getBlockSource()
HitResult* getHitResult()
```

### ClientInstance

Main game instance.

```cpp
static ClientInstance* get()

LocalPlayer* getLocalPlayer()
Level* getLevel()
BlockSource* getBlockSource()
GuiData* getGuiData()
MinecraftGame* getMinecraftGame()

std::string getScreenName()
Vec2<float> getFov()
float getFovX()
float getFovY()

void grabMouse()
void releaseMouse()
```

---

## Memory

Memory scanning and management.

### SignatureScanner

```cpp
static uintptr_t findPattern(const char* pattern)
```
Find a signature pattern in memory.

**Example:**
```cpp
auto addr = SignatureScanner::findPattern("48 89 5C 24 ? 57 48 83 EC");
```

### SignatureManager

```cpp
static SignatureManager& getInstance()

void addSignature(const std::string& name, const char* signature)
void addOffset(const std::string& name, int offset)

uintptr_t getSignatureAddress(const std::string& name)
int getOffset(const std::string& name)

void scanAll()
```

**Macros:**
```cpp
ADD_SIG(name, signature)
GET_SIG(name)
ADD_OFFSET(name, offset)
GET_OFFSET(name)
```

---

## Hooks

Function hooking system.

### HookManager

```cpp
static HookManager& getInstance()

bool initialize()
void shutdown()

bool createHook(void* target, void* detour, void** original)
bool enableHook(void* target)
bool disableHook(void* target)
bool removeHook(void* target)
```

### DirectXHooks

```cpp
static DirectXHooks& getInstance()

bool initialize()
void shutdown()

void addPresentCallback(const std::string& name, PresentCallback callback)
void addResizeCallback(const std::string& name, ResizeCallback callback)

void* getDevice()
void* getContext()
void* getSwapChain()
```

---

## Types

### Vec2<T>

```cpp
template<typename T>
struct Vec2 {
    T x, y;
    Vec2(T x, T y);
}
```

### Vec3<T>

```cpp
template<typename T>
struct Vec3 {
    T x, y, z;
    Vec3(T x, T y, T z);
}
```

### Color

```cpp
struct Color {
    float r, g, b, a;
    Color(float r, float g, float b, float a = 1.0f);
    
    static Color White();
    static Color Black();
    static Color Red();
    static Color Green();
    static Color Blue();
}
```

---

## Mod Registration

Use the `BEDROCK_MOD` macro to register your mod:

```cpp
BEDROCK_MOD(MyModClass)
```

This creates the required export functions for the mod loader.
