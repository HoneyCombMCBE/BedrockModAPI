# BedrockModAPI

A clean, well-documented modding API for Minecraft Bedrock Edition on Windows.

## Features

- **Clean C++ API** - Modern C++20 interface for mod development
- **Event System** - Hook into game events (render, tick, input, network)
- **SDK Access** - Direct access to game internals (Player, Level, Entities)
- **DirectX Hooking** - Render custom UI and overlays
- **Version Management** - Automatic signature/offset handling per game version
- **Mod Isolation** - Each mod runs independently

## Quick Start

### Building the API

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Creating Your First Mod

```cpp
#include <bedrock/mod.h>

class MyMod : public Bedrock::Mod {
public:
    MyMod() : Mod("MyMod", "1.0.0") {}
    
    void onInitialize() override {
        // Called when mod loads
        log("MyMod initialized!");
    }
    
    void onTick() override {
        // Called every game tick
        auto player = getLocalPlayer();
        if (player) {
            auto pos = player->getPosition();
            // Do something with player position
        }
    }
    
    void onRender() override {
        // Called every frame
        drawText("Hello from MyMod!", 10, 10);
    }
};

BEDROCK_MOD(MyMod)
```

### Building Your Mod

```cmake
cmake_minimum_required(VERSION 3.24.0)
project(MyMod)

find_package(BedrockModAPI REQUIRED)

add_library(MyMod SHARED mymod.cpp)
target_link_libraries(MyMod BedrockModAPI::BedrockModAPI)
```

## Documentation

- [Getting Started Guide](docs/getting-started.md)
- [API Reference](docs/api-reference.md)
- [Event System](docs/events.md)
- [SDK Documentation](docs/sdk.md)
- [Examples](examples/)

## Architecture

```
BedrockModAPI/
├── core/          # Event system, mod loader
├── sdk/           # Minecraft game structures
├── memory/        # Signature scanning, offsets
├── hooks/         # Function hooking (MinHook, DirectX)
└── examples/      # Example mods
```

## Supported Versions

- Minecraft Bedrock 1.21.11X (current)
- More versions coming soon

## License

MIT License - See LICENSE file for details

## Contributing

Contributions welcome! Please read CONTRIBUTING.md first.

## Credits

- Built with knowledge from [Flarial Client](https://github.com/flarialmc/dll-oss)
- Uses [MinHook](https://github.com/TsudaKageyu/minhook) for function hooking
- Uses [Kiero](https://github.com/Rebzzel/kiero) for DirectX hooking
