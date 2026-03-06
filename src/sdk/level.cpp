#include "bedrock/sdk/level.h"
#include "bedrock/memory/memory.h"

namespace Bedrock {
namespace SDK {

std::vector<Player*> Level::getPlayers() {
    std::vector<Player*> players;
    
    // Get player map
    auto playerMapOffset = GET_OFFSET("Level::getPlayerMap");
    auto playerMap = Memory::Utils::memberAt<void*>(this, playerMapOffset);
    
    if (!playerMap) return players;
    
    // TODO: Iterate through player map
    // This requires understanding the internal map structure
    
    return players;
}

std::vector<Actor*> Level::getRuntimeActorList() {
    std::vector<Actor*> actors;
    
    static auto getRuntimeActorListFn = reinterpret_cast<void(*)(Level*, std::vector<Actor*>&)>(GET_SIG("Level::getRuntimeActorList"));
    if (getRuntimeActorListFn) {
        getRuntimeActorListFn(this, actors);
    }
    
    return actors;
}

std::string Level::getWorldName() {
    auto levelData = Memory::Utils::memberAt<void*>(this, GET_OFFSET("Level::LevelData"));
    if (!levelData) return "";
    
    auto worldName = Memory::Utils::memberAt<std::string>(levelData, GET_OFFSET("LevelData::worldName"));
    return worldName;
}

BlockSource* Level::getBlockSource() {
    // This is typically obtained through ClientInstance
    return nullptr;
}

HitResult* Level::getHitResult() {
    return Memory::Utils::memberAt<HitResult*>(this, GET_OFFSET("Level::hitResult"));
}

// BlockSource implementation
Block* BlockSource::getBlock(const Vec3<int>& pos) {
    // TODO: Implement block access
    // This requires calling the getBlock function with position
    return nullptr;
}

Biome* BlockSource::getBiome(const Vec3<int>& pos) {
    static auto getBiomeFn = reinterpret_cast<Biome*(*)(BlockSource*, const Vec3<int>&)>(GET_SIG("BlockSource::getBiome"));
    if (getBiomeFn) {
        return getBiomeFn(this, pos);
    }
    return nullptr;
}

} // namespace SDK
} // namespace Bedrock
