# Changelog

All notable changes to BedrockModAPI will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Initial project structure
- Core API design with `Bedrock::Mod` base class
- Event system (Tick, Render, KeyPress, MouseMove, MouseClick)
- SDK headers for Actor, Player, LocalPlayer, Level, ClientInstance
- Memory management system with signature scanning
- Hook infrastructure interfaces (HookManager, DirectXHooks)
- Mod loader with automatic DLL loading from `mods/` folder
- Comprehensive documentation:
  - Getting Started guide
  - Complete API Reference
  - FAQ
  - Contributing guidelines
  - Roadmap
- Example mods:
  - Coordinate Display
  - Speed Boost
- CMake build system
- MIT License

### In Progress
- DirectX rendering implementation
- Complete SDK implementations
- MinHook integration
- Kiero integration
- Signature database for Minecraft 1.21.11X

## [1.0.0] - TBD

### Planned
- First stable release
- Full DirectX rendering support
- Complete SDK implementations
- Working example mods
- Support for Minecraft Bedrock 1.21.11X

---

## Release Notes Format

### Added
- New features

### Changed
- Changes to existing functionality

### Deprecated
- Soon-to-be removed features

### Removed
- Removed features

### Fixed
- Bug fixes

### Security
- Security fixes
