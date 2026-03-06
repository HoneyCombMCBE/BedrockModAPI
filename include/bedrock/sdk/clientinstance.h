#pragma once

#include "../api.h"
#include "actor.h"
#include "level.h"

namespace Bedrock {
namespace SDK {

// GUI data (screen info)
class BEDROCK_API GuiData {
public:
    Vec2<float> getScreenSize();
    Vec2<float> getScreenSizeScaled();
    float getGuiScale();
    
    // Mouse
    Vec2<float> getMousePos();
    
    // Display message
    void displayClientMessage(const std::string& message);
};

// Minecraft game instance
class BEDROCK_API MinecraftGame {
public:
    // Texture access
    class TextureGroup* getTextureGroup();
    
    // Mouse grab
    bool isMouseGrabbed();
};

// Client instance (main game object)
class BEDROCK_API ClientInstance {
public:
    static ClientInstance* get();
    
    // Player
    LocalPlayer* getLocalPlayer();
    
    // Level
    Level* getLevel();
    class BlockSource* getBlockSource();
    
    // GUI
    GuiData* getGuiData();
    
    // Game
    MinecraftGame* getMinecraftGame();
    
    // Screen
    std::string getScreenName();
    static std::string getTopScreenName();
    
    // Camera
    Vec2<float> getFov();
    float getFovX();
    float getFovY();
    
    // Mouse
    void grabMouse();
    void releaseMouse();
    
    // Rendering
    class LevelRender* getLevelRender();
};

} // namespace SDK
} // namespace Bedrock
