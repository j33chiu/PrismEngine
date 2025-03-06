#include "core/PrismId.h"

#include <logger/Logger.h>

namespace prism {

std::atomic<std::uint32_t> PrismId::uid = 0;

PrismId::PrismId() {
    id = ++uid;
}

PrismId::PrismId(std::uint32_t newId) {
    id = newId;
    Logger::warn("PrismId::PrismId", "setting a custom PrismId value is not recommended");
}

bool PrismId::operator==(const PrismId& prismId) const {
    return prismId.id == id;
}

bool PrismId::operator!=(const PrismId& prismId) const {
    return prismId.id != id;
}

bool PrismId::operator==(std::uint32_t id) const {
    return this->id == id;
}

bool PrismId::operator!=(std::uint32_t id) const {
    return this->id != id;
}

bool PrismId::operator<(const PrismId& prismId) const {
    return this->id < id;
}

bool PrismId::operator>(const PrismId& prismId) const {
    return this->id > id;
}

PrismId& PrismId::operator=(std::uint32_t newId) {
    id = newId;
    return *this;
}

std::uint32_t PrismId::getId() const {
    return id;
}

}