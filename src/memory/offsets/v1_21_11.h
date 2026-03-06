#pragma once

#include "../SignatureAndOffsetManager.hpp"

namespace Bedrock {
namespace Memory {
namespace Offsets {

// Minecraft 1.21.11X Offsets
class Offsets_1_21_11 {
public:
    static void initialize() {
        // Player offsets
        ADD_OFFSET("Player::playerName", 0xC18);
        ADD_OFFSET("Player::playerInventory", 0x5B8);
        ADD_OFFSET("Player::gamemode", 0xA78);
        
        // ClientInstance offsets
        ADD_OFFSET("ClientInstance::camera", 0x288);
        ADD_OFFSET("ClientInstance::guiData", 0x578);
        ADD_OFFSET("ClientInstance::getFovX", 0xF88);
        ADD_OFFSET("ClientInstance::getFovY", 0xF9C);
        ADD_OFFSET("ClientInstance::viewMatrix", 0x348);
        ADD_OFFSET("ClientInstance::minecraftGame", 0x0); // TODO: Find actual offset
        
        // MinecraftGame offsets
        ADD_OFFSET("MinecraftGame::textureGroup", 0x778);
        ADD_OFFSET("MinecraftGame::mouseGrabbed", 0x1B8);
        
        // Level offsets
        ADD_OFFSET("Level::hitResult", 0x1E8);
        ADD_OFFSET("Level::getPlayerMap", 0x4E8);
        ADD_OFFSET("Level::worldFolderName", 0x258);
        ADD_OFFSET("Level::LevelData", 0x90);
        
        // LevelData offsets
        ADD_OFFSET("LevelData::worldName", 0x298);
        
        // LevelRender offsets
        ADD_OFFSET("LevelRender::getLevelRendererPlayer", 0x3E8);
        ADD_OFFSET("LevelRendererPlayer::cameraPos", 0x6A0);
        
        // Actor offsets
        ADD_OFFSET("Actor::baseTickVft", 29);
        ADD_OFFSET("Actor::hurtTime", 0x19C);
        ADD_OFFSET("Actor::level", 0x1D8);
        ADD_OFFSET("Actor::categories", 0x210);
        
        // Attribute offsets
        ADD_OFFSET("Attribute::Health", 6);
        ADD_OFFSET("Attribute::Hunger", 1);
        ADD_OFFSET("Attribute::Saturation", 2);
        ADD_OFFSET("AttributeInstance::Value", 0x7C);
        
        // ItemActor offsets
        ADD_OFFSET("ItemActor::stack", 0x3B0);
        
        // ScreenContext offsets
        ADD_OFFSET("ScreenContext::tessellator", 0xB8);
        
        // GuiData offsets
        ADD_OFFSET("GuiData::ScreenSize", 0x40);
        ADD_OFFSET("GuiData::ScreenSizeScaled", 0x50);
        ADD_OFFSET("GuiData::GuiScale", 0x5C);
        ADD_OFFSET("GuiData::screenResRounded", 0x48);
        ADD_OFFSET("GuiData::sliderAmount", 0x5C);
        ADD_OFFSET("GuiData::scalingMultiplier", 0x60);
        ADD_OFFSET("GuiData::GuiMessages", 0x150);
        
        // MoveInputComponent offsets
        ADD_OFFSET("MoveInputComponent::forward", 0xD);
        ADD_OFFSET("MoveInputComponent::backward", 0xE);
        ADD_OFFSET("MoveInputComponent::left", 0xF);
        ADD_OFFSET("MoveInputComponent::right", 0x10);
        ADD_OFFSET("MoveInputComponent::sneaking", 0x28);
        ADD_OFFSET("MoveInputComponent::jumping", 0x2F);
        ADD_OFFSET("MoveInputComponent::sprinting", 0x30);
        
        // Block offsets
        ADD_OFFSET("Block::blockLegacy", 0x78);
        ADD_OFFSET("BlockLegacy::name", 0x98);
        ADD_OFFSET("BlockLegacy::namespace", 0xC0);
        
        // Item offsets
        ADD_OFFSET("Item::AtlasTextureFile", 0xB0);
        ADD_OFFSET("Item::Namespace", 0x100);
        ADD_OFFSET("Item::name", 0xD8);
        
        // Network offsets
        ADD_OFFSET("NetworkSystem::remoteConnectorComposite", 0xF0);
        ADD_OFFSET("RaknetConnector::JoinedIp", 0x3E0);
        ADD_OFFSET("RaknetConnector::RawIp", 0x3C0);
        ADD_OFFSET("RaknetConnector::port", 0x424);
        ADD_OFFSET("RaknetConnector::getPeer", 0x48);
        
        // Biome offsets
        ADD_OFFSET("Biome::temperature", 0x08);
        ADD_OFFSET("Biome::name", 0x198);
        
        // Dimension offsets
        ADD_OFFSET("Dimension::weather", 0x1C8);
        
        // Camera offsets
        ADD_OFFSET("mce::Camera::worldMatrixStack", 0x40);
        
        // UI offsets
        ADD_OFFSET("ChatScreenController::refreshChatMessages", 0xC73);
        ADD_OFFSET("ContainerScreenController::_handlePlaceAll", 57);
        ADD_OFFSET("MinecraftUIRenderContext::getTexture", 31);
        ADD_OFFSET("ClientInstance::getBlockSource", 30);
        
        // Misc offsets
        ADD_OFFSET("SwingAngle", 4);
    }
};

} // namespace Offsets
} // namespace Memory
} // namespace Bedrock
