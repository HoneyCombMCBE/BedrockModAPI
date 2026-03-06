# BedrockModAPI Roadmap

## Version 1.0.0 (Current - Foundation)

**Status**: In Progress

### Completed ✓
- [x] Project structure and build system
- [x] Core API design
- [x] Event system
- [x] Mod loader infrastructure
- [x] Memory management (signature scanning)
- [x] Hook infrastructure interfaces
- [x] Basic SDK headers (Actor, Player, Level)
- [x] Documentation (Getting Started, API Reference, FAQ)
- [x] Example mods

### In Progress 🔄
- [ ] DirectX rendering implementation
- [ ] Complete SDK implementations
- [ ] MinHook integration
- [ ] Kiero integration
- [ ] Signature database for 1.21.11X

### Remaining for 1.0.0
- [ ] Full DirectX text/primitive rendering
- [ ] ClientInstance implementation
- [ ] Actor/Player/Level implementations
- [ ] Version detection system
- [ ] Error handling and logging system
- [ ] Build and release pipeline

**Target**: Q2 2026

---

## Version 1.1.0 (Enhanced SDK)

**Focus**: Expand game access and improve stability

### Planned Features
- [ ] Network packet support (send/receive)
- [ ] Item and inventory management
- [ ] Block manipulation
- [ ] Entity spawning and manipulation
- [ ] World modification APIs
- [ ] Biome and dimension access
- [ ] More event types (attack, damage, chat)
- [ ] Configuration system for mods
- [ ] Hot-reload support

**Target**: Q3 2026

---

## Version 1.2.0 (Multi-Version Support)

**Focus**: Support multiple Minecraft versions

### Planned Features
- [ ] Automatic version detection
- [ ] Signature database for 1.21.10X
- [ ] Signature database for 1.21.20X
- [ ] Version-specific SDK implementations
- [ ] Fallback mechanisms for missing signatures
- [ ] Version compatibility warnings

**Target**: Q4 2026

---

## Version 2.0.0 (Advanced Features)

**Focus**: Advanced modding capabilities

### Planned Features
- [ ] Scripting support (Lua/Python)
- [ ] Mod dependency system
- [ ] Mod configuration GUI
- [ ] Performance profiling tools
- [ ] Mod marketplace integration
- [ ] Advanced rendering (shaders, custom models)
- [ ] Audio API
- [ ] Multiplayer sync helpers
- [ ] Mod update system

**Target**: 2027

---

## Future Considerations

### Community Requests
- Cross-platform support (if Bedrock comes to other platforms)
- Visual mod editor
- Mod templates and generators
- Integration with popular mod frameworks
- Cloud mod sync

### Technical Improvements
- Better memory safety
- Async API for heavy operations
- Mod sandboxing
- Performance optimizations
- Better debugging tools

---

## How to Contribute

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on contributing to these roadmap items.

### Priority Areas
1. **DirectX Rendering** - Critical for 1.0.0
2. **SDK Implementations** - Core functionality
3. **Version Support** - Expand compatibility
4. **Documentation** - Always needs improvement
5. **Example Mods** - Help new developers

---

## Version Support Policy

- **Latest version**: Full support, active development
- **Previous version**: Bug fixes only
- **Older versions**: Community support

---

## Release Schedule

- **Major versions** (X.0.0): Every 6-12 months
- **Minor versions** (1.X.0): Every 2-3 months
- **Patch versions** (1.0.X): As needed for critical bugs

---

## Feedback

Have suggestions for the roadmap? Open a GitHub Discussion or Issue!

Last updated: March 6, 2026
