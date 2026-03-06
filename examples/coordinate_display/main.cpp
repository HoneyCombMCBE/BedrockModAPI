#include <bedrock/api.h>
#include <bedrock/core/events.h>

using namespace Bedrock;

// Example mod: Coordinate Display
class CoordinateDisplay : public Mod {
public:
    CoordinateDisplay() : Mod("CoordinateDisplay", "1.0.0") {}
    
    void onInitialize() override {
        log("Coordinate Display initialized!");
        log("Press 'C' to toggle display");
    }
    
    void onRender() override {
        if (!isEnabled()) return;
        
        auto player = API::getLocalPlayer();
        if (!player) return;
        
        auto pos = player->getPosition();
        
        // Draw background
        API::drawRect(5, 5, 250, 80, Color(0, 0, 0, 0.5f), true);
        
        // Draw title
        API::drawText("Coordinates", 10, 10, Color::Green(), 1.2f);
        
        // Draw coordinates
        std::string xText = "X: " + std::to_string((int)pos->x);
        std::string yText = "Y: " + std::to_string((int)pos->y);
        std::string zText = "Z: " + std::to_string((int)pos->z);
        
        API::drawText(xText, 10, 35, Color::White());
        API::drawText(yText, 10, 50, Color::White());
        API::drawText(zText, 10, 65, Color::White());
    }
    
    void onKeyPress(int key, bool isDown) override {
        // Toggle with 'C' key
        if (key == 0x43 && isDown) {  // 'C' key
            setEnabled(!isEnabled());
            log(isEnabled() ? "Display enabled" : "Display disabled");
        }
    }
};

BEDROCK_MOD(CoordinateDisplay)
