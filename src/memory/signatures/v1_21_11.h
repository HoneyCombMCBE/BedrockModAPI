#pragma once

#include "../SignatureAndOffsetManager.hpp"

namespace Bedrock {
namespace Memory {
namespace Signatures {

// Minecraft 1.21.11X Signatures
class Signatures_1_21_11 {
public:
    static void initialize() {
        // Rendering
        ADD_SIG("ScreenView::setupAndRender", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 89 55");
        ADD_SIG("Tessellator::begin", "48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 80 B9 ? ? ? ? ? 45 0F B6 D9");
        ADD_SIG("Tessellator::vertex", "4C 8B DC 55 57 49 8D 6B ? 48 81 EC ? ? ? ? 45 0F 29 4B");
        ADD_SIG("mce::TextureGroup::getTexture", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F9 44 88 4C 24");
        ADD_SIG("LevelRenderer::renderLevel", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E8 4C 8B E2 4C 8B F9");
        ADD_SIG("ItemInHandRenderer::renderItem", "E8 ?? ?? ?? ?? 90 48 8B 4C 24 58 48 85 C9 74 2A");
        ADD_SIG("Font::drawTransformed", "48 8b c4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8d 6c 24 ? 48 81 ec ? ? ? ? 0f 29 70 ? 0f 29 78 ? 44 0f 29 40 ? 44 0f 29 48 ? 44 0f 29 90 ? ? ? ? 44 0f 29 98 ? ? ? ? 44 0f 29 a0 ? ? ? ? 44 0f 28 e3");
        ADD_SIG("ItemRenderer::renderGuiItemNew", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8d 6c 24 ? 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 45 ? 44 89 4d ? 49 8b f8 4c 8b ea");
        ADD_SIG("ItemRenderer::render", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 89 4C 24 ? 49 8B D8 4C 8B E2 48 89 54 24 ? 48 8B F9 44 0F B6 BD ? ? ? ? 45 0F B6 F7 4C 8B 6A 28 0F 57 C0 33 C0 0F 11 85 ? ? ? ? 0F 11 85 ? ? ? ? 48 89 85 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 90 41 0F B6 C7 24 40 80 BB ? ? ? ? ? 0F 84 ? ? ? ? 84 C0 74 09 48 8D B7 ? ? ? ? EB 13 45 84 FF");
        ADD_SIG("HudMobEffectsRenderer::render", "48 8b c4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8d a8 ? ? ? ? 48 81 ec ? ? ? ? 0f 29 70 ? 0f 29 78 ? 44 0f 29 40 ? 44 0f 29 48 ? 44 0f 29 90 ? ? ? ? 44 0f 29 98 ? ? ? ? 44 0f 29 a0 ? ? ? ? 44 0f 29 a8 ? ? ? ? 44 0f 29 b0 ? ? ? ? 44 0f 29 b8 ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 85 ? ? ? ? 49 8b f9");
        ADD_SIG("LevelRendererPlayer::renderOutlineSelection", "E8 ? ? ? ? EB ? 0F B6 44 24 ? 88 44 24 ? C6 44 24");
        ADD_SIG("ActorShaderManager::setupShaderParameter", "40 55 53 56 57 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 44 0F 29 8C 24");
        ADD_SIG("HurtColor", "E8 ? ? ? ? 44 0F 11 44 24 ? 4C 8D 4C 24");
        ADD_SIG("blockHighlightColor", "66 0F 6F 05 ? ? ? ? ? ? ? C6 40 ? ? 45 33 C9");
        ADD_SIG("MinimalViewBobbing", "FF 15 ? ? ? ? 80 7C 24 ? ? 0F 84 ? ? ? ? F3 0F 10 4C 24 ? 0F 29 B4 24");
        
        // Actor/Player
        ADD_SIG("Actor::baseTick", "48 8D 05 ?? ?? ?? ?? 48 89 01 48 8D 05 ?? ?? ?? ?? 48 89 81 88 0A 00 00 48 8B 91 E8 12 00 00");
        ADD_SIG("Actor::canSee", "e8 ? ? ? ? 84 c0 74 ? f6 83 ? ? ? ? ? 74 ? 8b 43");
        ADD_SIG("Actor::getMobEffectsComponent", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 8B F9 48 8B CA");
        ADD_SIG("Actor::getRenderPositionComponent", "48 83 EC ? 4C 8B 41 ? 41 BA ? ? ? ? 48 8B 41 ? 4C 8B 49 ? 49 2B C0 48 C1 F8 ? 48 FF C8 49 23 C2 49 8B 04 C0 48 83 F8 ? 74 ? 0F 1F 00 48 C1 E0 ? 49 03 C1 44 39 50 ? 74 ? 48 8B 00 48 83 F8 ? 75 ? 48 8B 41 ? 48 89 1C 24 48 3B 41 ? 0F 84 ? ? ? ? 4C 8B 40 ? 4D 85 C0 0F 84 ? ? ? ? 8B 02 8B D0 4D 8B 50 ? 81 E2 ? ? ? ? 49 8B 48 ? 44 8B CA 49 2B CA 49 C1 E9 ? 48 C1 F9 ? 4C 3B C9 73 ? 4A 8D 1C CD ? ? ? ? 4E 8B 0C 13 4D 85 C9 74 ? 8B CA 81 E1 ? ? ? ? 4D 8D 1C 89 4D 85 DB 74 ? 25 ? ? ? ? 41 33 03 3D ? ? ? ? 73 ? 49 8B 04 1A 81 E2 ? ? ? ? 8B 0C 90 49 8B 40 ? 81 E1 ? ? ? ? 8B D1 48 C1 EA ? 83 E1 ? 48 8B 04 D0 48 8D 0C 49 48 8D 04 88 48 8B 1C 24 48 83 C4 ? C3 48 8B 1C 24 33 C0 48 83 C4 ? C3 CC CC CC CC CC 48 83 EC ? 4C 8B 41 ? 4C 8B D1 48 8B 41 ? 4C 8B 49 ? 49 2B C0 8B 12 48 C1 F8 ? 48 FF C8 25 ? ? ? ? 49 8B 0C C0 48 83 F9 ? 74 ? 66 90 48 C1 E1 ? 42 81 7C 09 ? ? ? ? ? 4A 8D 04 09 74 ? 48 8B 08 48 83 F9 ? 75 ? 49 8B 42 ? 48 89 1C 24 49 3B 42 ? 0F 84 ? ? ? ? 4C 8B 40 ? 4D 85 C0 0F 84 ? ? ? ? 4D 8B 50 ? 8B CA 49 8B 40 ? 81 E1 ? ? ? ? 49 2B C2 44 8B C9 49 C1 E9 ? 48 C1 F8 ? 4C 3B C8 73 ? 4A 8D 1C CD ? ? ? ? 4E 8B 0C 13 4D 85 C9 74 ? 8B C1 25 ? ? ? ? 4D 8D 1C 81 4D 85 DB 74 ? 81 E2 ? ? ? ? 41 33 13 81 FA ? ? ? ? 73 ? 49 8B 40 ? 81 E1 ? ? ? ? 41 8B 14 89 81 E2 ? ? ? ? 8B CA 48 C1 E9 ? 83 E2 ? 48 8B 04 C8 48 8D 04 D0");
        ADD_SIG("LocalPlayer::applyTurnDelta", "48 8B C4 48 89 58 10 48 89 70 18 55 57 41 54 41 56 41 57 48 8D 68 C8 48 81 EC 10 01 00 00 0F 29 70 C8 0F 29 78 B8");
        ADD_SIG("ThirdPersonNametag", "0F 84 0A 05 00 00 49 8B 04 24");
        
        // Level
        ADD_SIG("Level::getRuntimeActorList", "48 89 5C 24 ? 55 56 57 48 83 EC ? 48 8B F2 48 89 54 24 ? 33 D2");
        ADD_SIG("BaseAttributeMap_getInstance", "4C 8B D1 44 0F B6 CA 49 BB ? ? ? ? ? ? ? ? 48 B8 ? ? ? ? ? ? ? ? 4C 33 C8 8B C2 4D 0F AF CB C1 E8 ? 44 0F B6 C0 8B C2 4D 33 C8 C1 E8 ? 4D 8B 42 ? 4D 0F AF CB 0F B6 C8 4C 33 C9 8B C2 49 8B 4A ? 4D 0F AF CB 48 C1 E8 ? 4C 33 C8 4D 0F AF CB 49 23 C9 48 C1 E1 ? 49 03 4A ? 48 8B 41 ? 49 3B C0 74 ? 48 8B 09 3B 50 ? 74 ? 48 3B C1 74 ? 48 8B 40 ? 3B 50 ? 75 ? EB ? 33 C0 48 85 C0 48 8D 15 ? ? ? ? 49 0F 44 C0 49 3B C0 48 8D 48 ? 48 0F 45 D1 48 8B C2 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24");
        
        // ClientInstance
        ADD_SIG("ClientInstance::grabMouse", "48 8B 80 ? ? ? ? FF 15 ? ? ? ? 48 8B 8F ? ? ? ? E8 ? ? ? ? 33 D2");
        ADD_SIG("ClientInstance::getScreenName", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B EA 48 8B 01 48 8D 54 24 ? 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 8B 48 ? 48 8B 01 48 8B D5 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 C7 44 24 ? ? ? ? ? 48 8B 7C 24 ? 33 DB 48 89 5C 24 ? BE ? ? ? ? 48 85 FF 74 ? 8B C6 F0 0F C1 47 ? 83 F8 ? 75 ? 48 8B 07 48 8B CF 48 8B 00 FF 15 ? ? ? ? 8B C6 F0 0F C1 47 ? 83 F8 ? 75 ? 48 8B 07 48 8B CF 48 8B 40 ? FF 15 ? ? ? ? 48 8B 5C 24 ? 48 C7 44 24 ? ? ? ? ? 48 85 DB 74 ? 8B C6 F0 0F C1 43 ? 83 F8 ? 75 ? 48 8B 03 48 8B CB 48 8B 00 FF 15 ? ? ? ? F0 0F C1 73 ? 83 FE ? 75 ? 48 8B 03 48 8B CB 48 8B 40 ? FF 15 ? ? ? ? 48 8B C5 48 8B 5C 24 ? 48 8B 6C 24 ? 48 8B 74 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC 48 89 5C 24 ? 48 89 6C 24");
        ADD_SIG("ClientInstance::_updateScreenSizeVariables", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 68 ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 0F 28 FB");
        
        // Network
        ADD_SIG("MinecraftPackets::createPacket", "48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 60 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 58 48 8B F9 48 89 4C 24 38");
        ADD_SIG("RakPeer::GetAveragePing", "48 8B C4 48 81 EC 58 01 00 00 0F 10 4A 10 4C 8B 1A 4C 3B 1D ?? ?? ?? ?? 48 89 58 08 48 8B D9 0F 29 70 E8 0F 29 78 D8 0F 10 7A 20 0F 11 4C 24 10 74 46 44 8B 49 14");
        ADD_SIG("RaknetTick", "4C 8B DC 49 89 5B 10 49 89 6B 18 56 57 41 56 48 81 EC 40 02 00 00");
        
        // UI
        ADD_SIG("ChatScreenController::tick", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B E9 48 89 4D");
        ADD_SIG("ContainerScreenController::_onContainerSlotHovered", "48 89 5C 24 10 48 89 6C 24 18 48 89 7C 24 20 41 56 48 83 EC 20 45 33 F6 41 8B E8");
        ADD_SIG("ContainerScreenController::_handleTakeAll", "E8 ? ? ? ? 48 8B 46 ? C6 80 ? ? ? ? ? 48 8B 7E");
        ADD_SIG("GuiData::displayClientMessage", "40 55 53 56 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 41 0F B6 F9");
        
        // Items
        ADD_SIG("ItemStack::getMaxDamage", "48 8B 41 08 48 85 C0 74 19");
        ADD_SIG("ItemStack::getDamageValue", "48 83 EC 38 48 8B 41 08 48 85 C0");
        ADD_SIG("ItemStack::isEnchanted", "48 83 EC 38 48 8B 49 10 48 85 C9 74 4B");
        
        // Options
        ADD_SIG("Options::getSensitivity", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B F8");
        ADD_SIG("Options::getGamma", "48 83 EC 28 48 8B 01 48 8D 54 24 30 41 B8 34 00 00 00");
        
        // Misc
        ADD_SIG("glm_rotateRef", "E8 ?? ?? ?? ?? 48 8B D0 8B 08 89 0B 8B 48 04 89 4B 04 8B 48 08 89 4B 08 8B 48 0C 89 4B 0C 8B 48 10 89 4B 10 8B 40 14 89 43 14 8B 42 18 89 43 18 8B 42 1C 89 43 1C 8B 42 20 89 43 20 8B 42 24 89 43 24 8B 42 28 89 43 28 8B 42 2C 89 43 2C 8B 42 30 89 43 30 8B 42 34 89 43 34 8B 42 38 89 43 38 8B 42 3C 89 43 3C 48 83 C4 70");
        ADD_SIG("CameraYaw2", "F3 0F 11 08 F3 0F 11 40 04 48 8D BB 28 02 00 00");
        ADD_SIG("FluxSwing", "E8 ? ? ? ? F3 0F 10 35 ? ? ? ? F3 0F 10 25");
        ADD_SIG("SwingAngle", "F3 44 0F 59 35 ?? ?? ?? ?? 4C 8D 4C 24 30");
        ADD_SIG("MeshHelpers::renderMeshImmediately", "E8 ? ? ? ? C6 46 ? ? F3 41 0F 10 5F");
        ADD_SIG("MeshHelpers::renderMeshImmediately2", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 49 8B F9 4D 8B F8");
        ADD_SIG("ResourcePackManager::_composeFullStack", "48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 50 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 40 48 8B E9 40 B6 01");
        ADD_SIG("AppPlatform::readAssetFile", "48 89 5C 24 ? 48 89 74 24 ? 55 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B D9 48 89 4C 24");
        ADD_SIG("SoundEngine::play", "40 53 55 56 57 41 56 41 57 48 81 EC C8 00 00 00 0F 29 B4 24 B0 00 00 00");
        ADD_SIG("Json::Value::ToStyledString", "E8 ? ? ? ? 90 0F 57 C9 F3 0F 7F 4D ? 48 8B 47");
        ADD_SIG("Json::Reader::Reader", "48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B F9 33 F6 48 89 31 48 89 71 ? 48 89 71 ? 48 89 71 ? 48 89 71 ? B9");
        ADD_SIG("Json::Reader::Parse", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 48 83 7A ? ? 41 0F B6 F1");
    }
};

} // namespace Signatures
} // namespace Memory
} // namespace Bedrock
