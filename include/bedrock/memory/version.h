#pragma once

#include <string>

namespace Bedrock {
namespace Memory {

// Version detection
class VersionDetector {
public:
    enum class MinecraftVersion {
        Unknown,
        V1_21_11X,
        V1_21_10X,
        V1_21_9X,
        V1_21_8X,
        V1_21_7X,
        V1_21_6X,
        V1_21_5X
    };
    
    static MinecraftVersion detectVersion();
    static std::string getVersionString(MinecraftVersion version);
    static void loadSignaturesAndOffsets(MinecraftVersion version);
};

} // namespace Memory
} // namespace Bedrock
