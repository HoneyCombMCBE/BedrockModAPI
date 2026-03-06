#include "bedrock/api.h"
#include "bedrock/hooks/hook.h"
#include "bedrock/memory/memory.h"
#include <Windows.h>
#include <vector>
#include <memory>

namespace Bedrock {

// Mod loader
class ModLoader {
public:
    static ModLoader& getInstance() {
        static ModLoader instance;
        return instance;
    }
    
    bool initialize() {
        log("BedrockModAPI initializing...");
        
        // Initialize subsystems
        if (!Memory::SignatureManager::getInstance().scanAll()) {
            logError("Failed to scan signatures");
            return false;
        }
        
        if (!Hooks::HookManager::getInstance().initialize()) {
            logError("Failed to initialize hook manager");
            return false;
        }
        
        if (!Hooks::DirectXHooks::getInstance().initialize()) {
            logError("Failed to initialize DirectX hooks");
            return false;
        }
        
        // Load mods from mods/ directory
        loadMods();
        
        log("BedrockModAPI initialized successfully!");
        return true;
    }
    
    void shutdown() {
        log("BedrockModAPI shutting down...");
        
        // Shutdown all mods
        for (auto& mod : mods_) {
            mod->onShutdown();
        }
        mods_.clear();
        
        // Shutdown subsystems
        Hooks::DirectXHooks::getInstance().shutdown();
        Hooks::HookManager::getInstance().shutdown();
        
        log("BedrockModAPI shut down");
    }
    
    void loadMods() {
        // TODO: Scan mods/ directory for DLLs
        // Load each DLL and call CreateMod() export
        log("Loading mods from mods/ directory...");
        
        WIN32_FIND_DATAA findData;
        HANDLE hFind = FindFirstFileA("mods\\*.dll", &findData);
        
        if (hFind == INVALID_HANDLE_VALUE) {
            log("No mods found in mods/ directory");
            return;
        }
        
        do {
            std::string modPath = "mods\\";
            modPath += findData.cFileName;
            
            if (!loadMod(modPath)) {
                logError("Failed to load mod: " + modPath);
            }
        } while (FindNextFileA(hFind, &findData));
        
        FindClose(hFind);
        
        log("Loaded " + std::to_string(mods_.size()) + " mods");
    }
    
    bool loadMod(const std::string& path) {
        HMODULE hMod = LoadLibraryA(path.c_str());
        if (!hMod) {
            return false;
        }
        
        // Get CreateMod export
        typedef Mod* (*CreateModFunc)();
        auto createMod = reinterpret_cast<CreateModFunc>(GetProcAddress(hMod, "CreateMod"));
        
        if (!createMod) {
            FreeLibrary(hMod);
            return false;
        }
        
        // Create mod instance
        Mod* mod = createMod();
        if (!mod) {
            FreeLibrary(hMod);
            return false;
        }
        
        // Initialize mod
        mod->onInitialize();
        
        mods_.push_back(std::unique_ptr<Mod>(mod));
        log("Loaded mod: " + mod->getName() + " v" + mod->getVersion());
        
        return true;
    }
    
    void tick() {
        for (auto& mod : mods_) {
            if (mod->isEnabled()) {
                mod->onTick();
            }
        }
    }
    
    void render() {
        for (auto& mod : mods_) {
            if (mod->isEnabled()) {
                mod->onRender();
            }
        }
    }
    
    void onKeyPress(int key, bool isDown) {
        for (auto& mod : mods_) {
            if (mod->isEnabled()) {
                mod->onKeyPress(key, isDown);
            }
        }
    }
    
    void onMouseMove(float x, float y) {
        for (auto& mod : mods_) {
            if (mod->isEnabled()) {
                mod->onMouseMove(x, y);
            }
        }
    }
    
    void onMouseClick(int button, bool isDown) {
        for (auto& mod : mods_) {
            if (mod->isEnabled()) {
                mod->onMouseClick(button, isDown);
            }
        }
    }
    
private:
    ModLoader() = default;
    
    void log(const std::string& msg) {
        OutputDebugStringA(("[BedrockModAPI] " + msg + "\n").c_str());
    }
    
    void logError(const std::string& msg) {
        OutputDebugStringA(("[BedrockModAPI ERROR] " + msg + "\n").c_str());
    }
    
    std::vector<std::unique_ptr<Mod>> mods_;
};

} // namespace Bedrock

// DLL entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        
        // Initialize on separate thread
        CreateThread(nullptr, 0, [](LPVOID) -> DWORD {
            Bedrock::ModLoader::getInstance().initialize();
            return 0;
        }, nullptr, 0, nullptr);
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        Bedrock::ModLoader::getInstance().shutdown();
    }
    
    return TRUE;
}
