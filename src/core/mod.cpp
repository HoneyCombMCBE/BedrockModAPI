#include "bedrock/api.h"
#include "bedrock/core/events.h"
#include <iostream>
#include <sstream>

namespace Bedrock {

// Mod implementation
Mod::Mod(const std::string& name, const std::string& version)
    : name_(name), version_(version), enabled_(true) {
}

void Mod::log(const std::string& message) {
    std::cout << "[" << name_ << "] " << message << std::endl;
}

void Mod::logError(const std::string& message) {
    std::cerr << "[" << name_ << " ERROR] " << message << std::endl;
}

void Mod::logWarning(const std::string& message) {
    std::cout << "[" << name_ << " WARNING] " << message << std::endl;
}

void Mod::setEnabled(bool enabled) {
    if (enabled_ == enabled) return;
    
    enabled_ = enabled;
    if (enabled_) {
        onEnable();
    } else {
        onDisable();
    }
}

} // namespace Bedrock
