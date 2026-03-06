# Tutorial: Finding Signatures and Offsets for New Minecraft Versions

This guide will teach you how to find signatures and offsets when a new Minecraft Bedrock version is released.

## Prerequisites

### Required Tools
1. **IDA Pro** or **Ghidra** - Disassembler/decompiler
   - IDA Pro (paid): https://hex-rays.com/ida-pro/
   - Ghidra (free): https://ghidra-sre.org/

2. **ReClass.NET** - Memory structure viewer
   - Download: https://github.com/ReClassNET/ReClass.NET

3. **x64dbg** - Debugger (optional but helpful)
   - Download: https://x64dbg.com/

4. **Cheat Engine** - Memory scanner (optional)
   - Download: https://www.cheatengine.org/

### Recommended Knowledge
- Basic C++ understanding
- Assembly language basics (x64)
- Understanding of pointers and memory addresses

---

## Part 1: Finding Signatures

Signatures are byte patterns used to locate functions in memory at runtime.

### What is a Signature?

A signature is a pattern of bytes that uniquely identifies a function. Example:
```
48 89 5C 24 ? 57 48 83 EC ? 48 8B 05
```
- Hex bytes (48, 89, etc.) are exact matches
- `?` is a wildcard (any byte)

### Step 1: Open Minecraft in IDA Pro

1. **Locate Minecraft.Windows.exe**
   - Usually in: `C:\Program Files\WindowsApps\Microsoft.MinecraftUWP_*\Minecraft.Windows.exe`
   - You may need to take ownership of the WindowsApps folder

2. **Open in IDA Pro**
   - File → Open
   - Select `Minecraft.Windows.exe`
   - Choose "Portable Executable for AMD64 (PE)" format
   - Wait for auto-analysis to complete (can take 10-30 minutes)

### Step 2: Find Functions Using Strings

Most functions can be found by searching for unique strings they reference.

**Example: Finding ClientInstance::getLocalPlayer**

1. **Open Strings Window**
   - View → Open subviews → Strings (or press Shift+F12)

2. **Search for relevant strings**
   - Look for strings like "LocalPlayer", "ClientInstance", etc.
   - For getLocalPlayer, search for error messages or debug strings

3. **Find Cross-References**
   - Double-click a string
   - Press 'X' to see where it's referenced
   - Navigate to the function that uses it

4. **Identify the Function**
   - Look at the function prologue (beginning)
   - Common patterns:
     ```asm
     push    rbx
     sub     rsp, 20h
     mov     rbx, rcx
     ```

### Step 3: Create the Signature

1. **Select the First ~20 Bytes**
   - Click on the first instruction
   - Note the hex bytes in the left column

2. **Identify Variable Parts**
   - Addresses, offsets, and immediate values change between versions
   - Replace these with `?` wildcards

3. **Example Process**

   Original bytes:
   ```
   48 89 5C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B 05 A1 B2 C3 D4
   ```

   The `A1 B2 C3 D4` is an address (changes between versions), so:
   ```
   48 89 5C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B 05 ? ? ? ?
   ```

4. **Test Uniqueness**
   - In IDA: Edit → Search → Sequence of bytes
   - Paste your pattern
   - Should find exactly ONE match
   - If multiple matches, extend the pattern

### Step 4: Document the Signature

```cpp
// ClientInstance::getLocalPlayer
// Returns the local player instance
// Pattern: 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05
ADD_SIG("ClientInstance::getLocalPlayer", 
        "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05");
```

---

## Part 2: Finding Offsets

Offsets are the distances from the start of a class to its members.

### What is an Offset?

An offset tells you where a member variable is located within a class:
```cpp
class Player {
    // offset 0x0
    void* vtable;
    
    // offset 0x8
    int someData;
    
    // offset 0xC18
    std::string playerName;  // <-- This is what we want
};
```

### Method 1: Using ReClass.NET (Easiest)

1. **Attach to Minecraft**
   - Launch Minecraft and join a world
   - Open ReClass.NET
   - File → Attach to Process → Minecraft.Windows.exe

2. **Find a Player Instance**
   - You need a pointer to a Player object
   - Use Cheat Engine to find it:
     - Search for your player name as a string
     - Find the address
     - Trace back to find the Player object pointer

3. **Add the Address to ReClass**
   - Right-click in ReClass → Add New Class
   - Right-click the class → Change Address
   - Paste the Player pointer address

4. **Explore the Structure**
   - You'll see the memory layout
   - Look for recognizable patterns:
     - Strings (player name, etc.)
     - Floats (position, health)
     - Pointers (inventory, level)

5. **Note the Offsets**
   - The offset is shown next to each field
   - Example: `+0xC18: std::string playerName`

### Method 2: Using IDA Pro (More Accurate)

1. **Find the Class Constructor**
   - Search for strings used in initialization
   - Or find the vtable

2. **Analyze Member Access**
   - Look for patterns like:
     ```asm
     mov     rax, [rcx+0C18h]  ; rcx = this pointer
     ```
   - The `0C18h` is the offset

3. **Example: Finding Player::playerName**

   ```asm
   ; Function: Player::getPlayerName()
   mov     rax, [rcx+0C18h]    ; Load playerName (offset 0xC18)
   ret
   ```

   So `Player::playerName` is at offset `0xC18`.

### Method 3: Comparing with Previous Version

1. **Open both versions in IDA**
   - Old version (known offsets)
   - New version (unknown offsets)

2. **Find the same function in both**
   - Use strings or function names

3. **Compare the offsets**
   - Look for member accesses
   - Note any changes

4. **Example Comparison**

   **Version 1.21.10:**
   ```asm
   mov     rax, [rcx+0C08h]    ; playerName at 0xC08
   ```

   **Version 1.21.11:**
   ```asm
   mov     rax, [rcx+0C18h]    ; playerName moved to 0xC18
   ```

### Step 5: Document the Offset

```cpp
// Player::playerName
// std::string containing the player's name
// Version 1.21.11X: 0xC18
// Version 1.21.10X: 0xC08 (changed!)
ADD_OFFSET("Player::playerName", 0xC18);
```

---

## Part 3: Common Patterns and Tips

### Finding Common Functions

#### ClientInstance::getLocalPlayer
**String to search:** "LocalPlayer", "ClientInstance"
**Pattern:** Usually returns a pointer from an offset
```asm
mov     rax, [rcx+offset]
ret
```

#### Actor::getPosition
**String to search:** "Position", "Actor"
**Pattern:** Accesses StateVectorComponent
```asm
mov     rax, [rcx+offset]
lea     rax, [rax+offset2]
```

#### Level::getPlayers
**String to search:** "Player", "Level"
**Pattern:** Returns a vector or list
```asm
lea     rax, [rcx+offset]
```

### Finding Common Offsets

#### Player::playerName
**How to find:** 
- Search for your player name in memory
- Trace back to Player object
- Note the offset

#### Player::playerInventory
**How to find:**
- Look for inventory-related functions
- Find accesses to inventory pointer
- Usually near playerName offset

#### ClientInstance::guiData
**How to find:**
- Search for "GuiData" string
- Find constructor or getter
- Note the offset in ClientInstance

---

## Part 4: Verification and Testing

### Verify Signatures

1. **Create a test program**
   ```cpp
   auto addr = SignatureScanner::findPattern("48 89 5C 24 ? 57 48 83 EC");
   if (addr) {
       std::cout << "Found at: 0x" << std::hex << addr << std::endl;
   } else {
       std::cout << "Signature not found!" << std::endl;
   }
   ```

2. **Test in-game**
   - Inject your DLL
   - Check if the signature is found
   - Verify it points to the correct function

### Verify Offsets

1. **Read the value**
   ```cpp
   auto player = getLocalPlayer();
   if (player) {
       auto name = player->getPlayerName();
       std::cout << "Player name: " << name << std::endl;
   }
   ```

2. **Check if it makes sense**
   - Does the player name match?
   - Is the position reasonable?
   - Are pointers valid (not null)?

---

## Part 5: Dealing with Updates

### When Minecraft Updates

1. **Check what changed**
   - Compare file sizes
   - Check version numbers
   - Look for patch notes

2. **Test existing signatures**
   - Most signatures survive minor updates
   - Major updates usually break everything

3. **Update broken signatures**
   - Find the function again using strings
   - Create new signature
   - Test thoroughly

4. **Update offsets**
   - Check if class layouts changed
   - Use ReClass.NET to verify
   - Update offset definitions

### Version Management

Create separate files for each version:

```cpp
// src/memory/signatures/v1_21_11.cpp
void Signatures_1_21_11::initialize() {
    ADD_SIG("ClientInstance::getLocalPlayer", "...");
    // ... more signatures
}

// src/memory/offsets/v1_21_11.cpp
void Offsets_1_21_11::initialize() {
    ADD_OFFSET("Player::playerName", 0xC18);
    // ... more offsets
}
```

---

## Part 6: Advanced Techniques

### Using IDA Scripts

Automate signature generation with IDAPython:

```python
import idaapi
import idc

def generate_signature(ea, length=20):
    """Generate a signature from an address"""
    sig = []
    for i in range(length):
        byte = idc.get_wide_byte(ea + i)
        # Check if this byte is part of an address/offset
        if idc.is_off(idc.get_flags(ea + i), i):
            sig.append("?")
        else:
            sig.append(f"{byte:02X}")
    return " ".join(sig)

# Usage
ea = idc.here()  # Current cursor position
print(generate_signature(ea))
```

### Using x64dbg for Dynamic Analysis

1. **Attach to Minecraft**
2. **Set breakpoints** on functions you're interested in
3. **Inspect memory** when breakpoint hits
4. **Note register values** (rcx = this pointer)
5. **Follow pointers** to find offsets

### Using Cheat Engine

1. **Find player name** (string search)
2. **Find what accesses this address**
3. **Trace back** to find the Player object
4. **Calculate offsets** from the base

---

## Part 7: Example Workflow

Let's find `Player::getHealth()` for a new version:

### Step 1: Find the Function

1. Open IDA Pro
2. Search strings for "health", "HP", "damage"
3. Find a function that accesses health
4. Navigate to `Player::getHealth()`

### Step 2: Create Signature

```asm
; Player::getHealth()
48 89 5C 24 08    mov [rsp+8], rbx
48 89 74 24 10    mov [rsp+10h], rsi
57                push rdi
48 83 EC 20       sub rsp, 20h
48 8B F9          mov rdi, rcx
```

Signature: `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F9`

### Step 3: Find the Offset

```asm
; Inside getHealth()
mov     rax, [rdi+1234h]    ; Load health component
mov     eax, [rax+10h]      ; Load health value
```

The health is accessed via a component at offset `0x1234`.

### Step 4: Document

```cpp
// Player::getHealth
// Returns the player's current health
ADD_SIG("Player::getHealth", 
        "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F9");

// Player::healthComponent
// Pointer to the health component
ADD_OFFSET("Player::healthComponent", 0x1234);
```

### Step 5: Implement

```cpp
float Player::getHealth() {
    auto healthComp = hat::member_at<void*>(this, GET_OFFSET("Player::healthComponent"));
    if (!healthComp) return 0.0f;
    return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(healthComp) + 0x10);
}
```

---

## Part 8: Troubleshooting

### Signature Not Found
- Pattern too specific → Add more wildcards
- Pattern too generic → Make it more specific
- Function moved → Search for it again using strings

### Wrong Offset
- Class layout changed → Re-analyze with ReClass.NET
- Wrong base pointer → Verify you have the correct object
- Pointer chain changed → Check intermediate pointers

### Crashes
- Invalid pointer → Check for null before dereferencing
- Wrong offset → Verify with debugger
- Function signature changed → Re-analyze the function

---

## Resources

### Tools
- **IDA Pro**: https://hex-rays.com/ida-pro/
- **Ghidra**: https://ghidra-sre.org/
- **ReClass.NET**: https://github.com/ReClassNET/ReClass.NET
- **x64dbg**: https://x64dbg.com/
- **Cheat Engine**: https://www.cheatengine.org/

### Learning Resources
- **IDA Pro Book**: "The IDA Pro Book" by Chris Eagle
- **Reverse Engineering**: https://beginners.re/
- **x64 Assembly**: https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html

### Community
- **Flarial Discord**: Ask experienced reverse engineers
- **UnknownCheats**: Forum for game hacking
- **GuidedHacking**: Tutorials and community

---

## Quick Reference

### IDA Pro Shortcuts
- `G` - Jump to address
- `X` - Cross-references
- `N` - Rename
- `Y` - Change type
- `Space` - Switch between graph/text view
- `Shift+F12` - Strings window

### Common Signature Patterns

```cpp
// Function prologue
"48 89 5C 24 ? 57 48 83 EC"

// Virtual function call
"48 8B 01 48 8B ? FF 90"

// String reference
"48 8D 15 ? ? ? ? 48 8D 4C 24"

// Return value
"48 8B C? C3"
```

### Common Offset Locations

```cpp
// Usually near start of class
Player::vtable          // 0x0
Player::entityId        // 0x8 - 0x10

// Usually in middle
Player::position        // 0x100 - 0x300
Player::rotation        // 0x100 - 0x300

// Usually later
Player::inventory       // 0x500 - 0x800
Player::playerName      // 0xC00 - 0xD00
Player::gamemode        // 0xA00 - 0xB00
```

---

**Good luck with reverse engineering! Remember: patience and practice are key.** 🔍

*Last Updated: March 6, 2026*
