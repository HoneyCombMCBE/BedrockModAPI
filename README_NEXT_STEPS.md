# Next Steps to Complete BedrockModAPI

This document outlines what needs to be done to make BedrockModAPI fully functional.

## Current Status

✅ **COMPLETED:**
- Project structure and build system
- Core API design and interfaces
- Event system
- Mod loader infrastructure
- Memory management (signature scanning framework)
- Hook infrastructure (interfaces)
- SDK headers (Actor, Player, Level, ClientInstance)
- Comprehensive documentation
- Example mods
- All foundation code

## What's Missing

### 1. Dependencies (CRITICAL)

**MinHook** - Function hooking library
```bash
cd lib
git clone https://github.com/TsudaKageyu/minhook.git
cd minhook && mkdir build && cd build
cmake .. && cmake --build . --config Release
```

**Kiero** - DirectX hooking
```bash
cd lib
git clone https://github.com/Rebzzel/kiero.git
```

**libhat** - Memory utilities (optional)
```bash
cd lib
git clone https://github.com/BasedInc/libhat.git
```

### 2. Implement Hook System (HIGH PRIORITY)

File: `src/hooks/hook.cpp`

**Tasks:**
- [ ] Integrate MinHook in `HookManager::initialize()`
- [ ] Implement `createHook()`, `enableHook()`, etc.
- [ ] Integrate Kiero in `DirectXHooks::initialize()`
- [ ] Hook `IDXGISwapChain::Present`
- [ ] Hook `IDXGISwapChain::ResizeBuffers`
- [ ] Store D3D11 device/context/swapchain
- [ ] Implement callback system for Present/Resize

**Reference:** `dll-oss/src/Client/Hook/Hooks/Render/DirectX/`

### 3. Implement DirectX Rendering (HIGH PRIORITY)

File: `src/core/rendering.cpp` (new file)

**Tasks:**
- [ ] Initialize DirectX resources (fonts, render targets)
- [ ] Implement `API::drawText()` using DirectWrite
- [ ] Implement `API::drawRect()` using D3D11 primitives
- [ ] Implement `API::drawLine()` using D3D11 primitives
- [ ] Handle window resize events
- [ ] Clean up resources on shutdown

**Reference:** `dll-oss/src/SDK/Client/Render/`

### 4. Implement SDK Classes (HIGH PRIORITY)

Extract implementations from Flarial:

**Actor** (`src/sdk/actor.cpp`)
- [ ] `getPosition()` - Use offset + signature
- [ ] `getVelocity()` - Component access
- [ ] `setPosition()`, `setVelocity()`
- [ ] `getHealth()`, `setHealth()`
- [ ] Flag getters/setters

**Player** (`src/sdk/player.cpp`)
- [ ] `getPlayerName()` - Use offset
- [ ] `getInventory()` - Use offset
- [ ] `getGamemode()` - Use offset

**LocalPlayer** (`src/sdk/localplayer.cpp`)
- [ ] `applyTurnDelta()` - Hook or direct call

**Level** (`src/sdk/level.cpp`)
- [ ] `getPlayers()` - Use signature
- [ ] `getRuntimeActorList()` - Use signature
- [ ] `getWorldName()` - Use offset

**ClientInstance** (`src/sdk/clientinstance.cpp`)
- [ ] `get()` - Find via signature
- [ ] `getLocalPlayer()` - Use offset
- [ ] `getLevel()` - Use offset
- [ ] `getGuiData()` - Use offset
- [ ] FOV getters

**Reference:** `dll-oss/src/SDK/Client/`

### 5. Add Signatures and Offsets (HIGH PRIORITY)

**Signatures** (`src/memory/signatures/v1_21_11.cpp` - new file)

Copy from `dll-oss/src/Utils/Memory/Game/Sig/SigInit.cpp`:
```cpp
void Signatures_1_21_11::initialize() {
    ADD_SIG("ClientInstance::getLocalPlayer", "...");
    ADD_SIG("Actor::getPosition", "...");
    // ... copy all relevant signatures
}
```

**Offsets** (`src/memory/offsets/v1_21_11.cpp` - new file)

Copy from `dll-oss/src/Utils/Memory/Game/Offset/OffsetInit.cpp`:
```cpp
void Offsets_1_21_11::initialize() {
    ADD_OFFSET("Player::playerName", 0xC18);
    ADD_OFFSET("Player::playerInventory", 0x5B8);
    // ... copy all relevant offsets
}
```

### 6. Implement Version Detection (MEDIUM PRIORITY)

File: `src/memory/version.cpp` (new file)

**Tasks:**
- [ ] Detect Minecraft version from executable
- [ ] Load appropriate signatures/offsets
- [ ] Fallback to manual version specification
- [ ] Log detected version

### 7. Implement Game Hooks (MEDIUM PRIORITY)

File: `src/hooks/game_hooks.cpp` (new file)

**Tasks:**
- [ ] Hook tick function → trigger `onTick()` events
- [ ] Hook input functions → trigger `onKeyPress()`, `onMouseMove()` events
- [ ] Hook packet send/receive → trigger packet events
- [ ] Store ClientInstance pointer when found

**Reference:** `dll-oss/src/Client/Hook/Hooks/`

### 8. Implement Mod Loader Integration (MEDIUM PRIORITY)

File: `src/core/loader.cpp`

**Tasks:**
- [ ] Call `scanAll()` on SignatureManager
- [ ] Find and store ClientInstance
- [ ] Set up game hooks
- [ ] Initialize DirectX hooks
- [ ] Call mod lifecycle hooks at appropriate times

### 9. Testing (HIGH PRIORITY)

**Tasks:**
- [ ] Test with Minecraft 1.21.11X
- [ ] Verify all example mods work
- [ ] Test mod loading/unloading
- [ ] Test hot-reload (enable/disable)
- [ ] Check for memory leaks
- [ ] Performance testing

### 10. Additional Features (LOW PRIORITY)

- [ ] Configuration system for mods
- [ ] Logging to file
- [ ] Error reporting system
- [ ] More example mods
- [ ] Mod dependency system

## Implementation Order

**Week 1: Core Functionality**
1. Add dependencies (MinHook, Kiero)
2. Implement hook system
3. Implement DirectX rendering
4. Test rendering with simple example

**Week 2: SDK Implementation**
5. Add signatures and offsets for 1.21.11X
6. Implement Actor/Player/Level classes
7. Implement ClientInstance
8. Test SDK access with example mods

**Week 3: Integration**
9. Implement game hooks (tick, input)
10. Integrate mod loader with hooks
11. Test complete flow
12. Fix bugs

**Week 4: Polish**
13. Performance optimization
14. Error handling
15. Additional example mods
16. Final testing

## Quick Start Guide

To start implementing:

1. **Add dependencies first** - Nothing works without MinHook/Kiero
2. **Start with hooks** - Get DirectX Present hook working
3. **Implement rendering** - Get `drawText()` working
4. **Add one signature** - Get ClientInstance pointer
5. **Implement one SDK class** - Get LocalPlayer working
6. **Test with example mod** - Verify coordinate display works
7. **Expand from there** - Add more signatures/SDK classes

## Testing Strategy

1. **Unit test each component** - Test signature scanning, hooks, etc.
2. **Integration test** - Test mod loading and lifecycle
3. **Real-world test** - Test with Minecraft
4. **Example mods** - Use as integration tests

## Resources

- **Flarial Source**: `dll-oss/` folder (reference implementation)
- **MinHook Docs**: https://github.com/TsudaKageyu/minhook
- **Kiero Docs**: https://github.com/Rebzzel/kiero
- **DirectX Docs**: Microsoft DirectX documentation
- **IDA Pro**: For finding new signatures

## Estimated Time

- **Minimal viable product**: 2-3 weeks
- **Full v1.0.0 release**: 4-6 weeks
- **With all features**: 8-12 weeks

## Questions?

See the main documentation in `docs/` or open a GitHub issue.

---

**The foundation is complete. Now it's time to fill in the implementations!**
