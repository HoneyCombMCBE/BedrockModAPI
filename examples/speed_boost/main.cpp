#include <bedrock/api.h>
#include <bedrock/core/events.h>

using namespace Bedrock;

// Example mod: Speed Boost
class SpeedBoost : public Mod {
private:
    float speedMultiplier = 2.0f;
    bool active = false;
    
public:
    SpeedBoost() : Mod("SpeedBoost", "1.0.0") {}
    
    void onInitialize() override {
        log("Speed Boost initialized!");
        log("Hold SHIFT to activate speed boost");
    }
    
    void onTick() override {
        auto player = API::getLocalPlayer();
        if (!player) return;
        
        // Check if shift is held
        bool shiftHeld = API::isKeyDown(VK_SHIFT);
        
        if (shiftHeld && !active) {
            active = true;
            log("Speed boost activated!");
        } else if (!shiftHeld && active) {
            active = false;
            log("Speed boost deactivated");
        }
        
        if (active) {
            // Get current velocity
            auto vel = player->getVelocity();
            
            // Apply speed multiplier to horizontal movement
            vel.x *= speedMultiplier;
            vel.z *= speedMultiplier;
            
            // Set new velocity
            player->setVelocity(vel);
        }
    }
    
    void onRender() override {
        if (active) {
            // Draw indicator
            API::drawText("SPEED BOOST ACTIVE", 10, 100, Color::Yellow(), 1.5f);
        }
    }
    
    void onKeyPress(int key, bool isDown) override {
        // Toggle mod with 'B' key
        if (key == 0x42 && isDown) {  // 'B' key
            setEnabled(!isEnabled());
            log(isEnabled() ? "Mod enabled" : "Mod disabled");
        }
    }
};

BEDROCK_MOD(SpeedBoost)
