#include "bedrock/sdk/clientinstance.h"
#include "bedrock/memory/memory.h"

namespace Bedrock {
namespace SDK {

// Global ClientInstance pointer
static ClientInstance* g_clientInstance = nullptr;

ClientInstance* ClientInstance::get() {
    if (!g_clientInstance) {
        // Find ClientInstance via signature
        static auto getClientInstanceFn = reinterpret_cast<ClientInstance*(*)()>(GET_SIG("ClientInstance::get"));
        if (getClientInstanceFn) {
            g_clientInstance = getClientInstanceFn();
        }
    }
    return g_clientInstance;
}

LocalPlayer* ClientInstance::getLocalPlayer() {
    static auto getLocalPlayerFn = reinterpret_cast<LocalPlayer*(*)(ClientInstance*)>(GET_SIG("ClientInstance::getLocalPlayer"));
    if (getLocalPlayerFn) {
        return getLocalPlayerFn(this);
    }
    return nullptr;
}

Level* ClientInstance::getLevel() {
    auto player = getLocalPlayer();
    if (!player) return nullptr;
    return player->getLevel();
}

BlockSource* ClientInstance::getBlockSource() {
    static auto getBlockSourceFn = reinterpret_cast<BlockSource*(*)(ClientInstance*)>(GET_SIG("ClientInstance::getBlockSource"));
    if (getBlockSourceFn) {
        return getBlockSourceFn(this);
    }
    return nullptr;
}

GuiData* ClientInstance::getGuiData() {
    return Memory::Utils::memberAt<GuiData*>(this, GET_OFFSET("ClientInstance::guiData"));
}

MinecraftGame* ClientInstance::getMinecraftGame() {
    return Memory::Utils::memberAt<MinecraftGame*>(this, GET_OFFSET("ClientInstance::minecraftGame"));
}

std::string ClientInstance::getScreenName() {
    static auto getScreenNameFn = reinterpret_cast<void(*)(ClientInstance*, std::string*)>(GET_SIG("ClientInstance::getScreenName"));
    if (getScreenNameFn) {
        std::string screenName;
        getScreenNameFn(this, &screenName);
        return screenName;
    }
    return "";
}

std::string ClientInstance::getTopScreenName() {
    auto instance = get();
    if (!instance) return "";
    return instance->getScreenName();
}

Vec2<float> ClientInstance::getFov() {
    return Vec2<float>(getFovX(), getFovY());
}

float ClientInstance::getFovX() {
    return Memory::Utils::memberAt<float>(this, GET_OFFSET("ClientInstance::getFovX"));
}

float ClientInstance::getFovY() {
    return Memory::Utils::memberAt<float>(this, GET_OFFSET("ClientInstance::getFovY"));
}

void ClientInstance::grabMouse() {
    static auto grabMouseFn = reinterpret_cast<void(*)(ClientInstance*)>(GET_SIG("ClientInstance::grabMouse"));
    if (grabMouseFn) {
        grabMouseFn(this);
    }
}

void ClientInstance::releaseMouse() {
    static auto releaseMouseFn = reinterpret_cast<void(*)(ClientInstance*)>(GET_SIG("ClientInstance::releaseMouse"));
    if (releaseMouseFn) {
        releaseMouseFn(this);
    }
}

LevelRender* ClientInstance::getLevelRender() {
    return Memory::Utils::memberAt<LevelRender*>(this, GET_OFFSET("ClientInstance::levelRender"));
}

// GuiData implementation
Vec2<float> GuiData::getScreenSize() {
    return Memory::Utils::memberAt<Vec2<float>>(this, GET_OFFSET("GuiData::ScreenSize"));
}

Vec2<float> GuiData::getScreenSizeScaled() {
    return Memory::Utils::memberAt<Vec2<float>>(this, GET_OFFSET("GuiData::ScreenSizeScaled"));
}

float GuiData::getGuiScale() {
    return Memory::Utils::memberAt<float>(this, GET_OFFSET("GuiData::GuiScale"));
}

Vec2<float> GuiData::getMousePos() {
    // Mouse position is typically stored in GuiData
    // TODO: Find exact offset
    return Vec2<float>(0, 0);
}

void GuiData::displayClientMessage(const std::string& message) {
    static auto displayMessageFn = reinterpret_cast<void(*)(GuiData*, const std::string&)>(GET_SIG("GuiData::displayClientMessage"));
    if (displayMessageFn) {
        displayMessageFn(this, message);
    }
}

// MinecraftGame implementation
TextureGroup* MinecraftGame::getTextureGroup() {
    return Memory::Utils::memberAt<TextureGroup*>(this, GET_OFFSET("MinecraftGame::textureGroup"));
}

bool MinecraftGame::isMouseGrabbed() {
    return Memory::Utils::memberAt<bool>(this, GET_OFFSET("MinecraftGame::mouseGrabbed"));
}

} // namespace SDK
} // namespace Bedrock
