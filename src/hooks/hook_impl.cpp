#include "bedrock/hooks/hook.h"
#include <MinHook.h>
#include <unordered_map>
#include <vector>

namespace Bedrock {
namespace Hooks {

// Hook storage
struct HookData {
    void* target;
    void* detour;
    void* original;
    bool enabled;
};

static std::unordered_map<void*, HookData> g_hooks;

HookManager& HookManager::getInstance() {
    static HookManager instance;
    return instance;
}

bool HookManager::initialize() {
    if (initialized_) return true;
    
    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        return false;
    }
    
    initialized_ = true;
    return true;
}

void HookManager::shutdown() {
    if (!initialized_) return;
    
    // Disable all hooks
    disableAll();
    
    // Remove all hooks
    for (auto& [target, data] : g_hooks) {
        MH_RemoveHook(target);
    }
    g_hooks.clear();
    
    MH_Uninitialize();
    initialized_ = false;
}

bool HookManager::createHook(void* target, void* detour, void** original) {
    if (!initialized_) return false;
    if (!target || !detour) return false;
    
    MH_STATUS status = MH_CreateHook(target, detour, original);
    if (status != MH_OK) {
        return false;
    }
    
    HookData data;
    data.target = target;
    data.detour = detour;
    data.original = original ? *original : nullptr;
    data.enabled = false;
    
    g_hooks[target] = data;
    return true;
}

bool HookManager::enableHook(void* target) {
    if (!initialized_) return false;
    
    auto it = g_hooks.find(target);
    if (it == g_hooks.end()) return false;
    
    MH_STATUS status = MH_EnableHook(target);
    if (status != MH_OK) {
        return false;
    }
    
    it->second.enabled = true;
    return true;
}

bool HookManager::disableHook(void* target) {
    if (!initialized_) return false;
    
    auto it = g_hooks.find(target);
    if (it == g_hooks.end()) return false;
    
    MH_STATUS status = MH_DisableHook(target);
    if (status != MH_OK) {
        return false;
    }
    
    it->second.enabled = false;
    return true;
}

bool HookManager::removeHook(void* target) {
    if (!initialized_) return false;
    
    auto it = g_hooks.find(target);
    if (it == g_hooks.end()) return false;
    
    if (it->second.enabled) {
        disableHook(target);
    }
    
    MH_STATUS status = MH_RemoveHook(target);
    if (status != MH_OK) {
        return false;
    }
    
    g_hooks.erase(it);
    return true;
}

bool HookManager::enableAll() {
    if (!initialized_) return false;
    
    MH_STATUS status = MH_EnableHook(MH_ALL_HOOKS);
    if (status != MH_OK) {
        return false;
    }
    
    for (auto& [target, data] : g_hooks) {
        data.enabled = true;
    }
    
    return true;
}

bool HookManager::disableAll() {
    if (!initialized_) return false;
    
    MH_STATUS status = MH_DisableHook(MH_ALL_HOOKS);
    if (status != MH_OK) {
        return false;
    }
    
    for (auto& [target, data] : g_hooks) {
        data.enabled = false;
    }
    
    return true;
}

// DirectX hooks implementation
static std::unordered_map<std::string, DirectXHooks::PresentCallback> g_presentCallbacks;
static std::unordered_map<std::string, DirectXHooks::ResizeCallback> g_resizeCallbacks;

static void* g_d3d11Device = nullptr;
static void* g_d3d11Context = nullptr;
static void* g_swapChain = nullptr;

// Present hook
typedef HRESULT(__stdcall* PresentFn)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
static PresentFn g_originalPresent = nullptr;

HRESULT __stdcall PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
    // Call all registered callbacks
    for (auto& [name, callback] : g_presentCallbacks) {
        callback(swapChain);
    }
    
    // Call original
    return g_originalPresent(swapChain, syncInterval, flags);
}

// ResizeBuffers hook
typedef HRESULT(__stdcall* ResizeBuffersFn)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
static ResizeBuffersFn g_originalResizeBuffers = nullptr;

HRESULT __stdcall ResizeBuffersHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
    // Call all registered callbacks
    for (auto& [name, callback] : g_resizeCallbacks) {
        callback(swapChain, width, height);
    }
    
    // Call original
    return g_originalResizeBuffers(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

DirectXHooks& DirectXHooks::getInstance() {
    static DirectXHooks instance;
    return instance;
}

bool DirectXHooks::initialize() {
    if (initialized_) return true;
    
    // Initialize Kiero
    if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success) {
        return false;
    }
    
    // Hook Present (index 8)
    if (kiero::bind(8, (void**)&g_originalPresent, (void*)PresentHook) != kiero::Status::Success) {
        return false;
    }
    
    // Hook ResizeBuffers (index 13)
    if (kiero::bind(13, (void**)&g_originalResizeBuffers, (void*)ResizeBuffersHook) != kiero::Status::Success) {
        return false;
    }
    
    // Get D3D11 device and context
    // This will be set on first Present call
    
    initialized_ = true;
    return true;
}

void DirectXHooks::shutdown() {
    if (!initialized_) return;
    
    g_presentCallbacks.clear();
    g_resizeCallbacks.clear();
    
    kiero::shutdown();
    
    initialized_ = false;
}

void DirectXHooks::addPresentCallback(const std::string& name, PresentCallback callback) {
    g_presentCallbacks[name] = callback;
}

void DirectXHooks::addResizeCallback(const std::string& name, ResizeCallback callback) {
    g_resizeCallbacks[name] = callback;
}

void DirectXHooks::removePresentCallback(const std::string& name) {
    g_presentCallbacks.erase(name);
}

void DirectXHooks::removeResizeCallback(const std::string& name) {
    g_resizeCallbacks.erase(name);
}

void* DirectXHooks::getDevice() {
    if (!g_d3d11Device && g_swapChain) {
        IDXGISwapChain* swapChain = static_cast<IDXGISwapChain*>(g_swapChain);
        swapChain->GetDevice(__uuidof(ID3D11Device), &g_d3d11Device);
    }
    return g_d3d11Device;
}

void* DirectXHooks::getContext() {
    if (!g_d3d11Context && g_d3d11Device) {
        ID3D11Device* device = static_cast<ID3D11Device*>(g_d3d11Device);
        device->GetImmediateContext((ID3D11DeviceContext**)&g_d3d11Context);
    }
    return g_d3d11Context;
}

void* DirectXHooks::getSwapChain() {
    return g_swapChain;
}

} // namespace Hooks
} // namespace Bedrock
