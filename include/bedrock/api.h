#pragma once

// Main API header - include this in your mods

#ifdef BEDROCK_API_EXPORT
    #define BEDROCK_API __declspec(dllexport)
#else
    #define BEDROCK_API __declspec(dllimport)
#endif

#include <cstdint>
#include <string>
#include <functional>

namespace Bedrock {

// Version info
constexpr const char* API_VERSION = "1.0.0";

// Forward declarations
class Mod;
class Event;
class LocalPlayer;
class Level;

// Math types
template<typename T>
struct Vec2 {
    T x, y;
    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}
};

template<typename T>
struct Vec3 {
    T x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
};

// Color type
struct Color {
    float r, g, b, a;
    Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
    Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
    
    static Color White() { return Color(1, 1, 1, 1); }
    static Color Black() { return Color(0, 0, 0, 1); }
    static Color Red() { return Color(1, 0, 0, 1); }
    static Color Green() { return Color(0, 1, 0, 1); }
    static Color Blue() { return Color(0, 0, 1, 1); }
};

// Event types
enum class EventType {
    Tick,           // Game tick
    Render,         // Frame render
    KeyPress,       // Keyboard input
    MouseMove,      // Mouse movement
    MouseClick,     // Mouse click
    PacketReceive,  // Network packet received
    PacketSend,     // Network packet sent
};

// Base event class
class BEDROCK_API Event {
public:
    virtual ~Event() = default;
    virtual EventType getType() const = 0;
    
    bool cancelled = false;
    void cancel() { cancelled = true; }
};

// Mod base class
class BEDROCK_API Mod {
public:
    Mod(const std::string& name, const std::string& version);
    virtual ~Mod() = default;
    
    // Lifecycle hooks
    virtual void onInitialize() {}
    virtual void onShutdown() {}
    virtual void onEnable() {}
    virtual void onDisable() {}
    
    // Event hooks
    virtual void onTick() {}
    virtual void onRender() {}
    virtual void onKeyPress(int key, bool isDown) {}
    virtual void onMouseMove(float x, float y) {}
    virtual void onMouseClick(int button, bool isDown) {}
    
    // Utility functions
    void log(const std::string& message);
    void logError(const std::string& message);
    void logWarning(const std::string& message);
    
    // Getters
    const std::string& getName() const { return name_; }
    const std::string& getVersion() const { return version_; }
    bool isEnabled() const { return enabled_; }
    
    // Enable/disable
    void setEnabled(bool enabled);
    
protected:
    std::string name_;
    std::string version_;
    bool enabled_ = true;
};

// API functions
namespace API {
    // Game access
    BEDROCK_API LocalPlayer* getLocalPlayer();
    BEDROCK_API Level* getLevel();
    BEDROCK_API bool isInGame();
    
    // Rendering
    BEDROCK_API void drawText(const std::string& text, float x, float y, const Color& color = Color::White(), float scale = 1.0f);
    BEDROCK_API void drawRect(float x, float y, float width, float height, const Color& color, bool filled = true);
    BEDROCK_API void drawLine(float x1, float y1, float x2, float y2, const Color& color, float thickness = 1.0f);
    
    // Screen info
    BEDROCK_API Vec2<float> getScreenSize();
    BEDROCK_API Vec2<float> getMousePos();
    
    // Input
    BEDROCK_API bool isKeyDown(int key);
    BEDROCK_API bool isMouseButtonDown(int button);
}

} // namespace Bedrock

// Mod registration macro
#define BEDROCK_MOD(ModClass) \
    extern "C" BEDROCK_API Bedrock::Mod* CreateMod() { \
        return new ModClass(); \
    } \
    extern "C" BEDROCK_API void DestroyMod(Bedrock::Mod* mod) { \
        delete mod; \
    }
