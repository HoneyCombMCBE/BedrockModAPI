# Version History and Signatures

This document tracks Minecraft Bedrock versions and their signature/offset status.

## Supported Versions

### 1.21.11X (Current)
**Status**: In Progress  
**Release Date**: December 2024  
**Signatures**: Partial  
**Offsets**: Partial  

#### Known Signatures
- `ScreenView::setupAndRender`
- `Tessellator::begin`
- `Tessellator::vertex`
- `Actor::baseTick`
- `MinecraftPackets::createPacket`
- More to be added...

#### Known Offsets
- `Player::playerName` - 0xC18
- `Player::playerInventory` - 0x5B8
- `Player::gamemode` - 0xA78
- `ClientInstance::guiData` - 0x578
- `ClientInstance::camera` - 0x288
- More to be added...

---

## Planned Support

### 1.21.10X
**Status**: Planned  
**Target**: Q2 2026  

### 1.21.20X
**Status**: Planned  
**Target**: Q3 2026  

---

## Version Detection

The API will automatically detect the Minecraft version and load appropriate signatures/offsets.

### Detection Methods
1. Check executable version info
2. Scan for version-specific signatures
3. Fallback to manual version specification

---

## Adding New Versions

To add support for a new Minecraft version:

1. **Find Signatures**
   - Use IDA Pro or Ghidra
   - Compare with previous version
   - Document changes

2. **Find Offsets**
   - Use ReClass.NET or similar
   - Verify with runtime testing
   - Document structure changes

3. **Update Code**
   - Add to `src/memory/signatures/`
   - Add to `src/memory/offsets/`
   - Update version detection

4. **Test**
   - Verify all SDK functions work
   - Test example mods
   - Check for crashes

5. **Document**
   - Update this file
   - Update README.md
   - Add to CHANGELOG.md

---

## Signature Format

Signatures use IDA-style patterns:
```
"48 89 5C 24 ? 57 48 83 EC"
```

Where:
- Hex bytes are exact matches
- `?` is a wildcard (any byte)

---

## Offset Format

Offsets are in hexadecimal:
```cpp
ADD_OFFSET("Player::playerName", 0xC18);
```

---

## Version-Specific Notes

### 1.21.11X
- Major rendering changes
- New packet structures
- Actor component system updated

### 1.21.10X
- Network system refactored
- Level structure changes

---

## Resources

- [Flarial Signatures](https://github.com/flarialmc/dll-oss/tree/main/src/Utils/Memory/Game/Sig)
- [Flarial Offsets](https://github.com/flarialmc/dll-oss/tree/main/src/Utils/Memory/Game/Offset)
- IDA Pro / Ghidra for reverse engineering
- ReClass.NET for structure analysis

---

Last updated: March 6, 2026
