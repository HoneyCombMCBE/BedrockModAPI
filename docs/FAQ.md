# Frequently Asked Questions

## General

### What is BedrockModAPI?

BedrockModAPI is a modding API for Minecraft Bedrock Edition on Windows. It provides a clean C++ interface for creating mods that can hook into game events, access game internals, and render custom UI.

### How is this different from Flarial?

Flarial is a full client with built-in modules. BedrockModAPI is just an API - it provides the infrastructure for you to create your own mods as separate DLLs. It's more focused on being a development platform than an end-user client.

### Is this safe to use?

BedrockModAPI uses the same techniques as other Minecraft mods (memory hooking, signature scanning). However, using any mod carries risk:
- **Single-player**: Generally safe
- **Multiplayer**: May violate server rules, use at your own risk
- **Realms**: Not recommended

### What Minecraft versions are supported?

Currently: Minecraft Bedrock 1.21.11X

More versions will be added over time. Check the README for the latest list.

## Installation

### How do I install BedrockModAPI?

1. Download `BedrockModAPI.dll` from releases
2. Inject it into Minecraft using a DLL injector
3. Place mod DLLs in the `mods/` folder next to Minecraft executable

### What DLL injector should I use?

Popular options:
- Extreme Injector
- Process Hacker
- Xenos Injector

### Where do I put mods?

Create a `mods/` folder in the same directory as `Minecraft.Windows.exe`, then place mod DLLs there.

### Why aren't my mods loading?

Check:
1. `BedrockModAPI.dll` is injected first
2. Mod DLLs are in the correct `mods/` folder
3. Mods are compiled for the correct architecture (x64)
4. Check console output for error messages

## Development

### How do I create a mod?

See the [Getting Started Guide](getting-started.md) for a complete tutorial.

Basic steps:
1. Create a class inheriting from `Bedrock::Mod`
2. Override event hooks (`onTick`, `onRender`, etc.)
3. Use `BEDROCK_MOD(YourClass)` macro
4. Compile as a DLL

### What IDE should I use?

Visual Studio 2022 is recommended. Visual Studio Code with CMake Tools also works.

### Can I use other languages?

The API is C++, but you could create bindings for other languages. The C API boundary makes this feasible.

### How do I debug my mod?

1. Build in Debug configuration
2. Attach Visual Studio debugger to Minecraft process
3. Set breakpoints in your mod code
4. Use `log()` function for console output

### Where do log messages go?

Use a tool like DebugView++ to see `OutputDebugString` messages, or redirect to a file.

## API Usage

### How do I access the player?

```cpp
auto player = API::getLocalPlayer();
if (player) {
    // Use player
}
```

Always check for `nullptr` - player may not exist in menus.

### How do I draw on screen?

```cpp
void onRender() override {
    API::drawText("Hello!", 10, 10, Color::White());
    API::drawRect(50, 50, 100, 100, Color::Red(), true);
}
```

### How do I detect key presses?

```cpp
void onKeyPress(int key, bool isDown) override {
    if (key == VK_SPACE && isDown) {
        log("Space pressed!");
    }
}
```

Or check in `onTick`:
```cpp
if (API::isKeyDown(VK_SHIFT)) {
    // Shift is held
}
```

### How do I modify player movement?

```cpp
void onTick() override {
    auto player = API::getLocalPlayer();
    if (player) {
        auto vel = player->getVelocity();
        vel.y += 0.1f;  // Add upward velocity
        player->setVelocity(vel);
    }
}
```

### Can I send packets?

Not yet implemented in the current version. This will be added in a future update.

## Troubleshooting

### Minecraft crashes on startup

- Ensure you're using the correct Minecraft version
- Check that all dependencies are present
- Try with no mods first to isolate the issue
- Check for conflicting injected DLLs

### Mod compiles but doesn't load

- Verify `CreateMod` and `DestroyMod` exports exist
- Check that `BEDROCK_MOD` macro is used
- Ensure mod is compiled as a DLL (not EXE)
- Check for missing dependencies (MSVC runtime, etc.)

### Drawing functions don't work

DirectX rendering is not yet fully implemented. This is a known limitation that will be fixed in a future update.

### Can't find player/level

Make sure you're in a world, not in the menu. Check `API::isInGame()` first.

### Signatures not found

The game version may have changed. Signatures need to be updated for each Minecraft version.

## Contributing

### How can I contribute?

See [CONTRIBUTING.md](../CONTRIBUTING.md) for guidelines.

Areas that need help:
- DirectX rendering implementation
- More SDK classes
- Version support
- Documentation improvements
- Example mods

### I found a bug, where do I report it?

Open an issue on GitHub with:
- Minecraft version
- API version
- Steps to reproduce
- Error messages/crash logs

### Can I add support for a new Minecraft version?

Yes! You'll need to:
1. Find new signatures for that version
2. Update offsets if they changed
3. Test all SDK functions
4. Submit a pull request

## Legal

### Is this legal?

Modding Minecraft Bedrock is a gray area. This API is for educational purposes. Use at your own risk.

### Can I sell mods made with this API?

The API is MIT licensed, so yes. However, check Minecraft's EULA regarding commercial use.

### Can I use this in my own project?

Yes, the MIT license allows commercial and non-commercial use.

## Getting Help

### Where can I get help?

- Read the documentation in `docs/`
- Check example mods in `examples/`
- Open a GitHub Discussion
- Join our Discord (coming soon)

### The documentation doesn't cover X

Open an issue requesting documentation for that topic, or submit a pull request adding it!
