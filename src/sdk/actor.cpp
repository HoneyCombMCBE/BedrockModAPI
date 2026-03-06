#include "bedrock/sdk/actor.h"
#include "bedrock/memory/memory.h"

namespace Bedrock {
namespace SDK {

Vec3<float>* Actor::getPosition() {
    auto stateVec = getStateVectorComponent();
    if (!stateVec) return nullptr;
    return &stateVec->pos;
}

Vec3<float> Actor::getVelocity() {
    auto stateVec = getStateVectorComponent();
    if (!stateVec) return Vec3<float>(0, 0, 0);
    return stateVec->velocity;
}

void Actor::setPosition(const Vec3<float>& pos) {
    auto stateVec = getStateVectorComponent();
    if (stateVec) {
        stateVec->pos = pos;
    }
}

void Actor::setVelocity(const Vec3<float>& vel) {
    auto stateVec = getStateVectorComponent();
    if (stateVec) {
        stateVec->velocity = vel;
    }
}

Vec2<float> Actor::getRotation() {
    auto rotComp = getActorRotationComponent();
    if (!rotComp) return Vec2<float>(0, 0);
    return Vec2<float>(rotComp->pitch, rotComp->yaw);
}

void Actor::setRotation(const Vec2<float>& rot) {
    auto rotComp = getActorRotationComponent();
    if (rotComp) {
        rotComp->pitch = rot.x;
        rotComp->yaw = rot.y;
    }
}

bool Actor::getFlag(ActorFlag flag) {
    auto flagComp = getActorDataFlagComponent();
    if (!flagComp) return false;
    return flagComp->getFlag(static_cast<int>(flag));
}

void Actor::setFlag(ActorFlag flag, bool value) {
    auto flagComp = getActorDataFlagComponent();
    if (flagComp) {
        flagComp->setFlag(static_cast<int>(flag), value);
    }
}

bool Actor::isOnGround() {
    // Check OnGroundFlagComponent
    return getFlag(ActorFlag::OnGround);
}

bool Actor::isInWater() {
    return getFlag(ActorFlag::Swimming);
}

bool Actor::isInLava() {
    return getFlag(ActorFlag::OnFire);
}

float Actor::getHealth() {
    auto attrComp = getAttributesComponent();
    if (!attrComp) return 0.0f;
    
    auto healthAttr = attrComp->getAttribute(GET_OFFSET("Attribute::Health"));
    if (!healthAttr) return 0.0f;
    
    return Memory::Utils::memberAt<float>(healthAttr, GET_OFFSET("AttributeInstance::Value"));
}

float Actor::getMaxHealth() {
    auto attrComp = getAttributesComponent();
    if (!attrComp) return 0.0f;
    
    auto healthAttr = attrComp->getAttribute(GET_OFFSET("Attribute::Health"));
    if (!healthAttr) return 0.0f;
    
    return healthAttr->getMaxValue();
}

void Actor::setHealth(float health) {
    auto attrComp = getAttributesComponent();
    if (!attrComp) return;
    
    auto healthAttr = attrComp->getAttribute(GET_OFFSET("Attribute::Health"));
    if (!healthAttr) return;
    
    Memory::Utils::memberAt<float>(healthAttr, GET_OFFSET("AttributeInstance::Value")) = health;
}

std::string* Actor::getNametag() {
    return Memory::Utils::memberAt<std::string*>(this, GET_OFFSET("Actor::nametag"));
}

void Actor::setNametag(const std::string& name) {
    auto nametagPtr = getNametag();
    if (nametagPtr) {
        *nametagPtr = name;
    }
}

Level* Actor::getLevel() {
    return Memory::Utils::memberAt<Level*>(this, GET_OFFSET("Actor::level"));
}

bool Actor::isValid() {
    return this != nullptr && getLevel() != nullptr;
}

// Component getters
StateVectorComponent* Actor::getStateVectorComponent() {
    // Use signature to get component
    static auto getComponentFn = reinterpret_cast<StateVectorComponent*(*)(Actor*)>(GET_SIG("Actor::getStateVectorComponent"));
    if (getComponentFn) {
        return getComponentFn(this);
    }
    return nullptr;
}

ActorRotationComponent* Actor::getActorRotationComponent() {
    static auto getComponentFn = reinterpret_cast<ActorRotationComponent*(*)(Actor*)>(GET_SIG("Actor::getActorRotationComponent"));
    if (getComponentFn) {
        return getComponentFn(this);
    }
    return nullptr;
}

ActorDataFlagComponent* Actor::getActorDataFlagComponent() {
    static auto getComponentFn = reinterpret_cast<ActorDataFlagComponent*(*)(Actor*)>(GET_SIG("Actor::getActorDataFlagComponent"));
    if (getComponentFn) {
        return getComponentFn(this);
    }
    return nullptr;
}

AttributesComponent* Actor::getAttributesComponent() {
    static auto getComponentFn = reinterpret_cast<AttributesComponent*(*)(Actor*)>(GET_SIG("Actor::getAttributesComponent"));
    if (getComponentFn) {
        return getComponentFn(this);
    }
    return nullptr;
}

// Player implementation
std::string& Player::getPlayerName() {
    return Memory::Utils::memberAt<std::string>(this, GET_OFFSET("Player::playerName"));
}

PlayerInventory* Player::getInventory() {
    return Memory::Utils::memberAt<PlayerInventory*>(this, GET_OFFSET("Player::playerInventory"));
}

ItemStack* Player::getSelectedItem() {
    auto inv = getInventory();
    if (!inv) return nullptr;
    return inv->getSelectedItem();
}

Gamemode* Player::getGamemode() {
    return Memory::Utils::memberAt<Gamemode*>(this, GET_OFFSET("Player::gamemode"));
}

float Player::getHunger() {
    auto attrComp = getAttributesComponent();
    if (!attrComp) return 0.0f;
    
    auto hungerAttr = attrComp->getAttribute(GET_OFFSET("Attribute::Hunger"));
    if (!hungerAttr) return 0.0f;
    
    return Memory::Utils::memberAt<float>(hungerAttr, GET_OFFSET("AttributeInstance::Value"));
}

float Player::getSaturation() {
    auto attrComp = getAttributesComponent();
    if (!attrComp) return 0.0f;
    
    auto saturationAttr = attrComp->getAttribute(GET_OFFSET("Attribute::Saturation"));
    if (!saturationAttr) return 0.0f;
    
    return Memory::Utils::memberAt<float>(saturationAttr, GET_OFFSET("AttributeInstance::Value"));
}

// LocalPlayer implementation
void LocalPlayer::applyTurnDelta(Vec2<float>* delta) {
    static auto applyTurnDeltaFn = reinterpret_cast<void(*)(LocalPlayer*, Vec2<float>*)>(GET_SIG("LocalPlayer::applyTurnDelta"));
    if (applyTurnDeltaFn) {
        applyTurnDeltaFn(this, delta);
    }
}

MoveInputComponent* LocalPlayer::getMoveInput() {
    static auto getMoveInputFn = reinterpret_cast<MoveInputComponent*(*)(LocalPlayer*)>(GET_SIG("LocalPlayer::getMoveInput"));
    if (getMoveInputFn) {
        return getMoveInputFn(this);
    }
    return nullptr;
}

} // namespace SDK
} // namespace Bedrock
