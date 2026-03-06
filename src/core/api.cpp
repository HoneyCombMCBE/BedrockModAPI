#include "bedrock/api.h"
#include "bedrock/sdk/clientinstance.h"
#include <Windows.h>

namespace Bedrock {
namespace API {

// Global state
static SDK::ClientInstance* g_clientInstance = nullptr;

// Initialize API (called by DllMain)
void initialize() {
    // TODO: Get ClientInstance from game
    // This will be done via signature scanning
}

SDK::LocalPlayer* getLocalPlayer() {
    if (!g_clientInstance) return nullptr;
    return g_clientInstance->getLocalPlayer();
}

SDK::Level* getLevel() {
    if (!g_clientInstance) return nullptr;
    return g_clientInstance->getLevel();
}

bool isInGame() {
    return getLocalPlayer() != nullptr && getLevel() != nullptr;
}

// Rendering functions (will be implemented with DirectX)
void drawText(const std::string& text, float x, float y, const Color& color, float scale) {
    // TODO: Implement with DirectX text rendering
}

void drawRect(float x, float y, float width, float height, const Color& color, bool filled) {
    // TODO: Implement with DirectX primitive rendering
}

void drawLine(float x1, float y1, float x2, float y2, const Color& color, float thickness) {
    // TODO: Implement with DirectX line rendering
}

Vec2<float> getScreenSize() {
    if (!g_clientInstance) return Vec2<float>(1920, 1080);
    
    auto guiData = g_clientInstance->getGuiData();
    if (!guiData) return Vec2<float>(1920, 1080);
    
    return guiData->getScreenSize();
}

Vec2<float> getMousePos() {
    if (!g_clientInstance) return Vec2<float>(0, 0);
    
    auto guiData = g_clientInstance->getGuiData();
    if (!guiData) return Vec2<float>(0, 0);
    
    return guiData->getMousePos();
}

bool isKeyDown(int key) {
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

bool isMouseButtonDown(int button) {
    // 0=left, 1=right, 2=middle
    int vk = (button == 0) ? VK_LBUTTON : (button == 1) ? VK_RBUTTON : VK_MBUTTON;
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

} // namespace API
} // namespace Bedrock
