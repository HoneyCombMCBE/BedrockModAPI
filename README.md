# BedrockModAPI

A clean, well-documented modding API for Minecraft Bedrock Edition on Windows.

## 🌟 Features

- **Clean C++ API** - Modern C++20 interface for mod development
- **Event System** - Hook into game events (render, tick, input, network)
- **SDK Access** - Direct access to game internals (Player, Level, Entities)
- **DirectX Hooking** - Render custom UI and overlays
- **Version Management** - Automatic signature/offset handling per game version
- **Mod Isolation** - Each mod runs independently

## 🚀 Quick Start

### Building the API

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Creating Your First Mod

```cpp
#include <bedrock/api.h>

class MyMod : public Bedrock::Mod {
public:
    MyMod() : Mod("MyMod", "1.0.0") {}
    
    void onInitialize() override {
        log("MyMod initialized!");
    }
    
    void onTick() override {
        auto player = API::getLocalPlayer();
        if (player) {
            auto pos = player->getPosition();
            // Do something with player position
        }
    }
    
    void onRender() override {
        API::drawText("Hello from MyMod!", 10, 10, Color::Green());
    }
};

BEDROCK_MOD(MyMod)
```

### Building Your Mod

```cmake
cmake_minimum_required(VERSION 3.24.0)
project(MyMod)

set(CMAKE_CXX_STANDARD 20)

find_package(BedrockModAPI REQUIRED)

add_library(MyMod SHARED mymod.cpp)
target_link_libraries(MyMod BedrockModAPI::BedrockModAPI)
```

## 📚 Documentation

- **[Getting Started Guide](docs/getting-started.md)** - Complete tutorial from zero to first mod
- **[API Reference](docs/api-reference.md)** - Full API documentation
- **[Quick Reference](docs/quick-reference.md)** - Common tasks and code snippets
- **[Finding Signatures & Offsets](docs/finding-signatures-offsets.md)** - Reverse engineering guide
- **[FAQ](docs/FAQ.md)** - Frequently asked questions
- **[Examples](examples/)** - Working example mods

## 🏗️ Architecture

```
BedrockModAPI/
├── core/          # Event system, mod loader
├── sdk/           # Minecraft game structures
├── memory/        # Signature scanning, offsets
├── hooks/         # Function hooking (MinHook, DirectX)
└── examples/      # Example mods
```

## 📦 Project Status

**Current Version**: 1.0.0-alpha  
**Status**: Foundation Complete ✅

### Completed
- ✅ Complete API design (C++20)
- ✅ Event system
- ✅ Mod loader infrastructure
- ✅ Memory management framework
- ✅ Hook infrastructure interfaces
- ✅ SDK headers
- ✅ Comprehensive documentation (3,800+ lines)
- ✅ Working example mods

### In Progress
- ⏳ DirectX rendering implementation
- ⏳ SDK class implementations
- ⏳ Signature/offset database for 1.21.11X

See [README_NEXT_STEPS.md](README_NEXT_STEPS.md) for detailed implementation roadmap.

## 🎯 Supported Versions

- Minecraft Bedrock 1.21.11X (in progress)
- More versions coming soon

## 📖 Example Mods

### Coordinate Display
Shows player coordinates on screen with a clean UI.

### Speed Boost
Multiplies player movement speed when holding shift.

See [examples/](examples/) for complete source code.

## 🤝 Contributing

Contributions welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) first.

**Priority Areas:**
- DirectX rendering implementation
- SDK class implementations
- More example mods
- Version support (1.21.10X, 1.21.20X)
- Documentation improvements

## 📄 License

MIT License - See [LICENSE](LICENSE) file for details.

## 🙏 Credits

- Built with knowledge from [Flarial Client](https://github.com/flarialmc/dll-oss)
- Uses [MinHook](https://github.com/TsudaKageyu/minhook) for function hooking
- Uses [Kiero](https://github.com/Rebzzel/kiero) for DirectX hooking

## 📞 Contact

- **GitHub**: [HoneyCombMCBE/BedrockModAPI](https://github.com/HoneyCombMCBE/BedrockModAPI)
- **Issues**: [GitHub Issues](https://github.com/HoneyCombMCBE/BedrockModAPI/issues)
- **Email**: contact@cloudwaddie.com

## ⭐ Star Us!

If you find this project useful, please consider giving it a star on GitHub!

---

**Built with ❤️ for the Minecraft Bedrock modding community**
