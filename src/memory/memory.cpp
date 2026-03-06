#include "bedrock/memory/memory.h"
#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <sstream>

namespace Bedrock {
namespace Memory {

// Convert IDA-style pattern to bytes and mask
static bool parsePattern(const char* pattern, std::vector<uint8_t>& bytes, std::string& mask) {
    std::stringstream ss(pattern);
    std::string token;
    
    while (ss >> token) {
        if (token == "?") {
            bytes.push_back(0);
            mask += '?';
        } else {
            bytes.push_back(static_cast<uint8_t>(std::stoul(token, nullptr, 16)));
            mask += 'x';
        }
    }
    
    return !bytes.empty();
}

// Scan memory region for pattern
static uintptr_t scanRegion(uintptr_t start, size_t size, const uint8_t* pattern, const char* mask, size_t patternLen) {
    for (size_t i = 0; i < size - patternLen; i++) {
        bool found = true;
        for (size_t j = 0; j < patternLen; j++) {
            if (mask[j] != '?' && pattern[j] != *reinterpret_cast<uint8_t*>(start + i + j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return start + i;
        }
    }
    return 0;
}

uintptr_t SignatureScanner::findSignature(const char* signature, const char* mask) {
    return findSignature("Minecraft.Windows.exe", signature, mask);
}

uintptr_t SignatureScanner::findSignature(const std::string& moduleName, const char* signature, const char* mask) {
    HMODULE module = GetModuleHandleA(moduleName.c_str());
    if (!module) return 0;
    
    MODULEINFO modInfo;
    if (!GetModuleInformation(GetCurrentProcess(), module, &modInfo, sizeof(MODULEINFO))) {
        return 0;
    }
    
    size_t patternLen = mask ? strlen(mask) : strlen(signature);
    return scanRegion(reinterpret_cast<uintptr_t>(module), modInfo.SizeOfImage, 
                     reinterpret_cast<const uint8_t*>(signature), mask, patternLen);
}

uintptr_t SignatureScanner::findPattern(const char* pattern) {
    return findPattern("Minecraft.Windows.exe", pattern);
}

uintptr_t SignatureScanner::findPattern(const std::string& moduleName, const char* pattern) {
    std::vector<uint8_t> bytes;
    std::string mask;
    
    if (!parsePattern(pattern, bytes, mask)) {
        return 0;
    }
    
    return findSignature(moduleName, reinterpret_cast<const char*>(bytes.data()), mask.c_str());
}

// SignatureManager implementation
SignatureManager& SignatureManager::getInstance() {
    static SignatureManager instance;
    return instance;
}

void SignatureManager::addSignature(const std::string& name, const char* signature) {
    SigData data;
    data.signature = signature;
    data.address = 0;
    signatures_[name] = data;
}

void SignatureManager::addOffset(const std::string& name, int offset) {
    offsets_[name] = offset;
}

uintptr_t SignatureManager::getSignatureAddress(const std::string& name) {
    auto it = signatures_.find(name);
    if (it == signatures_.end()) return 0;
    
    // Scan if not already scanned
    if (it->second.address == 0) {
        it->second.address = SignatureScanner::findPattern(it->second.signature.c_str());
    }
    
    return it->second.address;
}

int SignatureManager::getOffset(const std::string& name) {
    auto it = offsets_.find(name);
    return (it != offsets_.end()) ? it->second : 0;
}

void SignatureManager::scanAll() {
    for (auto& [name, data] : signatures_) {
        if (data.address == 0) {
            data.address = SignatureScanner::findPattern(data.signature.c_str());
        }
    }
}

void SignatureManager::clear() {
    signatures_.clear();
    offsets_.clear();
}

} // namespace Memory
} // namespace Bedrock
