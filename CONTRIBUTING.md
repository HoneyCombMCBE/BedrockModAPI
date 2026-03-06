# Contributing to BedrockModAPI

Thank you for your interest in contributing to BedrockModAPI!

## How to Contribute

### Reporting Issues

- Use GitHub Issues to report bugs
- Include Minecraft version, API version, and steps to reproduce
- Provide crash logs if applicable

### Submitting Pull Requests

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Test thoroughly
5. Commit with clear messages (`git commit -m 'Add amazing feature'`)
6. Push to your fork (`git push origin feature/amazing-feature`)
7. Open a Pull Request

### Code Style

- Use C++20 features where appropriate
- Follow existing naming conventions:
  - Classes: `PascalCase`
  - Functions: `camelCase`
  - Variables: `camelCase`
  - Constants: `UPPER_SNAKE_CASE`
- Add comments for complex logic
- Document public API functions

### Adding New Features

When adding new features:

1. **Update documentation** - Add to relevant .md files
2. **Add examples** - Create example mod if applicable
3. **Test thoroughly** - Ensure it works with current Minecraft version
4. **Maintain compatibility** - Don't break existing mods

### Adding Minecraft Versions

To add support for a new Minecraft version:

1. Add signatures to `src/memory/signatures/`
2. Add offsets to `src/memory/offsets/`
3. Update version detection in `src/memory/version.cpp`
4. Test all SDK functions work correctly
5. Update README.md with supported version

### Project Areas

**High Priority:**
- DirectX rendering implementation
- More SDK classes (Items, Blocks, Packets)
- Version detection and management
- More example mods

**Medium Priority:**
- Performance optimizations
- Better error handling
- Mod configuration system
- Hot-reload support

**Low Priority:**
- GUI for mod management
- Mod dependency system
- Scripting language support (Lua/Python)

## Development Setup

1. Clone the repository
2. Install Visual Studio 2022 with C++ desktop development
3. Install CMake 3.24+
4. Build with CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build . --config Debug
   ```

## Testing

- Test with Minecraft Bedrock 1.21.11X
- Verify all example mods work
- Check for memory leaks
- Test mod loading/unloading

## Questions?

- Open a GitHub Discussion
- Join our Discord (coming soon)
- Email: contact@cloudwaddie.com (coming soon)

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
