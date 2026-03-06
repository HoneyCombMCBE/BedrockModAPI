#pragma once

#include "../api.h"
#include <functional>

namespace Bedrock {
namespace Hooks {

// Hook manager
class BEDROCK_API HookManager {
public:
    static HookManager& getInstance();
    
    // Initialize hooking system
    bool initialize();
    void shutdown();
    
    // Create hook
    bool createHook(void* target, void* detour, void** original);
    bool enableHook(void* target);
    bool disableHook(void* target);
    bool removeHook(void* target);
    
    // Enable/disable all hooks
    bool enableAll();
    bool disableAll();
    
private:
    HookManager() = default;
    bool initialized_ = false;
};

// DirectX hook manager
class BEDROCK_API DirectXHooks {
public:
    static DirectXHooks& getInstance();
    
    // Initialize DirectX hooks
    bool initialize();
    void shutdown();
    
    // Register callbacks
    using PresentCallback = std::function<void(void* swapChain)>;
    using ResizeCallback = std::function<void(void* swapChain, uint32_t width, uint32_t height)>;
    
    void addPresentCallback(const std::string& name, PresentCallback callback);
    void addResizeCallback(const std::string& name, ResizeCallback callback);
    
    void removePresentCallback(const std::string& name);
    void removeResizeCallback(const std::string& name);
    
    // Get DirectX objects
    void* getDevice();
    void* getContext();
    void* getSwapChain();
    
private:
    DirectXHooks() = default;
    bool initialized_ = false;
};

} // namespace Hooks
} // namespace Bedrock
