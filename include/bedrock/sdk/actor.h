#pragma once

#include "../api.h"
#include <string>

namespace Bedrock {
namespace SDK {

// Actor flags (entity states)
enum class ActorFlag : int {
    OnFire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Invisible = 5,
    Gliding = 32,
    Swimming = 57,
    // Add more as needed
};

// Forward declarations
class Level;
class ItemStack;

// Base actor class (entities)
class BEDROCK_API Actor {
public:
    virtual ~Actor() = default;
    
    // Position and movement
    Vec3<float>* getPosition();
    Vec3<float> getVelocity();
    void setPosition(const Vec3<float>& pos);
    void setVelocity(const Vec3<float>& vel);
    
    // Rotation
    Vec2<float> getRotation();
    void setRotation(const Vec2<float>& rot);
    
    // State
    bool getFlag(ActorFlag flag);
    void setFlag(ActorFlag flag, bool value);
    bool isOnGround();
    bool isInWater();
    bool isInLava();
    
    // Health
    float getHealth();
    float getMaxHealth();
    void setHealth(float health);
    
    // Name
    std::string* getNametag();
    void setNametag(const std::string& name);
    
    // Level
    Level* getLevel();
    
    // Validation
    bool isValid();
};

// Player class
class BEDROCK_API Player : public Actor {
public:
    // Player-specific
    std::string& getPlayerName();
    
    // Inventory
    class PlayerInventory* getInventory();
    ItemStack* getSelectedItem();
    
    // Gamemode
    class Gamemode* getGamemode();
    
    // Hunger
    float getHunger();
    float getSaturation();
};

// Local player (the client player)
class BEDROCK_API LocalPlayer : public Player {
public:
    // Camera
    void applyTurnDelta(Vec2<float>* delta);
    
    // Input
    class MoveInputComponent* getMoveInput();
};

} // namespace SDK
} // namespace Bedrock
