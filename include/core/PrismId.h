#pragma once

#include <atomic>

namespace prism {

class PrismId {

public:
    PrismId();
    PrismId(std::uint32_t newId);

    // copying and moving of the ID is explicily allowed, make sure you know what you're doing

    bool operator==(const PrismId& prismId) const;
    bool operator!=(const PrismId& prismId) const;
    bool operator==(std::uint32_t id) const;
    bool operator!=(std::uint32_t id) const;
    bool operator<(const PrismId& prismId) const;
    bool operator>(const PrismId& prismId) const;
    PrismId& operator=(std::uint32_t newId);

    std::uint32_t getId() const;


private:
    static std::atomic<std::uint32_t> uid;

    std::uint32_t id;

};

}

namespace std {
// override hashing of PrismId objects
template<>
struct hash<prism::PrismId> {
    std::size_t operator()(const prism::PrismId& prismId) const {
        return std::hash<std::uint32_t>()(prismId.getId());
    }
};

}