#pragma once

#include "../api.h"

namespace Bedrock {
namespace Events {

// Tick event - called every game tick (~20 times per second)
class BEDROCK_API TickEvent : public Event {
public:
    EventType getType() const override { return EventType::Tick; }
};

// Render event - called every frame
class BEDROCK_API RenderEvent : public Event {
public:
    EventType getType() const override { return EventType::Render; }
    
    float deltaTime;  // Time since last frame
    RenderEvent(float dt) : deltaTime(dt) {}
};

// Key event
class BEDROCK_API KeyEvent : public Event {
public:
    EventType getType() const override { return EventType::KeyPress; }
    
    int key;
    bool isDown;
    bool isRepeat;
    
    KeyEvent(int k, bool down, bool repeat = false) 
        : key(k), isDown(down), isRepeat(repeat) {}
};

// Mouse move event
class BEDROCK_API MouseMoveEvent : public Event {
public:
    EventType getType() const override { return EventType::MouseMove; }
    
    float x, y;
    float deltaX, deltaY;
    
    MouseMoveEvent(float x, float y, float dx, float dy)
        : x(x), y(y), deltaX(dx), deltaY(dy) {}
};

// Mouse click event
class BEDROCK_API MouseClickEvent : public Event {
public:
    EventType getType() const override { return EventType::MouseClick; }
    
    int button;  // 0=left, 1=right, 2=middle
    bool isDown;
    float x, y;
    
    MouseClickEvent(int btn, bool down, float x, float y)
        : button(btn), isDown(down), x(x), y(y) {}
};

// Packet events
class BEDROCK_API PacketEvent : public Event {
public:
    void* packet;
    int packetId;
    
protected:
    PacketEvent(void* pkt, int id) : packet(pkt), packetId(id) {}
};

class BEDROCK_API PacketReceiveEvent : public PacketEvent {
public:
    EventType getType() const override { return EventType::PacketReceive; }
    PacketReceiveEvent(void* pkt, int id) : PacketEvent(pkt, id) {}
};

class BEDROCK_API PacketSendEvent : public PacketEvent {
public:
    EventType getType() const override { return EventType::PacketSend; }
    PacketSendEvent(void* pkt, int id) : PacketEvent(pkt, id) {}
};

} // namespace Events
} // namespace Bedrock
