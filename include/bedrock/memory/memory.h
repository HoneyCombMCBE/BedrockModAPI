#pragma once

#include "../api.h"
#include <cstdint>
#include <string>
#include <unordered_map>

namespace Bedrock {
namespace Memory {

// Signature scanner
class BEDROCK_API SignatureScanner {
public:
    // Scan for pattern in module
    static uintptr_t findSignature(const char* signature, const char* mask = nullptr);
    static uintptr_t findSignature(const std::string& moduleName, const char* signature, const char* mask = nullptr);
    
    // Scan with IDA-style pattern (e.g., "48 89 5C 24 ? 57 48 83 EC")
    static uintptr_t findPattern(const char* pattern);
    static uintptr_t findPattern(const std::string& moduleName, const char* pattern);
};

// Signature and offset manager
class BEDROCK_API SignatureManager {
public:
    static SignatureManager& getInstance();
    
    // Register signatures
    void addSignature(const std::string& name, const char* signature);
    void addOffset(const std::string& name, int offset);
    
    // Get addresses
    uintptr_t getSignatureAddress(const std::string& name);
    int getOffset(const std::string& name);
    
    // Scan all registered signatures
    void scanAll();
    
    // Clear all
    void clear();
    
private:
    SignatureManager() = default;
    
    struct SigData {
        std::string signature;
        uintptr_t address = 0;
    };
    
    std::unordered_map<std::string, SigData> signatures_;
    std::unordered_map<std::string, int> offsets_;
};

// Helper macros
#define ADD_SIG(name, sig) \
    Bedrock::Memory::SignatureManager::getInstance().addSignature(name, sig)

#define GET_SIG(name) \
    Bedrock::Memory::SignatureManager::getInstance().getSignatureAddress(name)

#define ADD_OFFSET(name, offset) \
    Bedrock::Memory::SignatureManager::getInstance().addOffset(name, offset)

#define GET_OFFSET(name) \
    Bedrock::Memory::SignatureManager::getInstance().getOffset(name)

// Memory utilities
namespace Utils {
    // Read/write memory
    template<typename T>
    inline T read(uintptr_t address) {
        return *reinterpret_cast<T*>(address);
    }
    
    template<typename T>
    inline void write(uintptr_t address, T value) {
        *reinterpret_cast<T*>(address) = value;
    }
    
    // Get member at offset (like libhat)
    template<typename T>
    inline T& memberAt(void* instance, int offset) {
        return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(instance) + offset);
    }
}

} // namespace Memory
} // namespace Bedrock
