#pragma once

#include "../api.h"
#include <vector>

namespace Bedrock {
namespace SDK {

class Actor;
class Player;
class Block;

// Level (world) class
class BEDROCK_API Level {
public:
    virtual ~Level() = default;
    
    // Players
    std::vector<Player*> getPlayers();
    
    // Entities
    std::vector<Actor*> getRuntimeActorList();
    
    // World info
    std::string getWorldName();
    
    // Block access
    class BlockSource* getBlockSource();
    
    // Hit result (raycast)
    struct HitResult* getHitResult();
};

// Block source (chunk/block access)
class BEDROCK_API BlockSource {
public:
    // Block queries
    Block* getBlock(const Vec3<int>& pos);
    
    // Biome
    class Biome* getBiome(const Vec3<int>& pos);
};

} // namespace SDK
} // namespace Bedrock
