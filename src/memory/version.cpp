#include "bedrock/memory/version.h"
#include "bedrock/memory/memory.h"
#include "signatures/v1_21_11.h"
#include "offsets/v1_21_11.h"
#include <Windows.h>

namespace Bedrock {
namespace Memory {

VersionDetector::MinecraftVersion VersionDetector::detectVersion() {
    // Get Minecraft.Windows.exe version info
    HMODULE hModule = GetModuleHandleA("Minecraft.Windows.exe");
    if (!hModule) {
        return MinecraftVersion::Unknown;
    }
    
    char filename[MAX_PATH];
    GetModuleFileNameA(hModule, filename, MAX_PATH);
    
    DWORD handle;
    DWORD size = GetFileVersionInfoSizeA(filename, &handle);
    if (size == 0) {
        return MinecraftVersion::Unknown;
    }
    
    std::vector<BYTE> buffer(size);
    if (!GetFileVersionInfoA(filename, handle, size, buffer.data())) {
        return MinecraftVersion::Unknown;
    }
    
    VS_FIXEDFILEINFO* fileInfo = nullptr;
    UINT len = 0;
    if (!VerQueryValueA(buffer.data(), "\\", (LPVOID*)&fileInfo, &len)) {
        return MinecraftVersion::Unknown;
    }
    
    DWORD major = HIWORD(fileInfo->dwFileVersionMS);
    DWORD minor = LOWORD(fileInfo->dwFileVersionMS);
    DWORD build = HIWORD(fileInfo->dwFileVersionLS);
    
    // Detect version based on version numbers
    if (major == 1 && minor == 21) {
        if (build >= 110 && build < 120) {
            return MinecraftVersion::V1_21_11X;
        } else if (build >= 100 && build < 110) {
            return MinecraftVersion::V1_21_10X;
        } else if (build >= 90 && build < 100) {
            return MinecraftVersion::V1_21_9X;
        } else if (build >= 80 && build < 90) {
            return MinecraftVersion::V1_21_8X;
        } else if (build >= 70 && build < 80) {
            return MinecraftVersion::V1_21_7X;
        } else if (build >= 60 && build < 70) {
            return MinecraftVersion::V1_21_6X;
        } else if (build >= 50 && build < 60) {
            return MinecraftVersion::V1_21_5X;
        }
    }
    
    return MinecraftVersion::Unknown;
}

std::string VersionDetector::getVersionString(MinecraftVersion version) {
    switch (version) {
        case MinecraftVersion::V1_21_11X: return "1.21.11X";
        case MinecraftVersion::V1_21_10X: return "1.21.10X";
        case MinecraftVersion::V1_21_9X: return "1.21.9X";
        case MinecraftVersion::V1_21_8X: return "1.21.8X";
        case MinecraftVersion::V1_21_7X: return "1.21.7X";
        case MinecraftVersion::V1_21_6X: return "1.21.6X";
        case MinecraftVersion::V1_21_5X: return "1.21.5X";
        default: return "Unknown";
    }
}

void VersionDetector::loadSignaturesAndOffsets(MinecraftVersion version) {
    switch (version) {
        case MinecraftVersion::V1_21_11X:
            Signatures::Signatures_1_21_11::initialize();
            Offsets::Offsets_1_21_11::initialize();
            break;
        // TODO: Add other versions
        default:
            // Try 1.21.11X as fallback
            Signatures::Signatures_1_21_11::initialize();
            Offsets::Offsets_1_21_11::initialize();
            break;
    }
}

} // namespace Memory
} // namespace Bedrock
