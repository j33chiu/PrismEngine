#pragma once

#include <string>
#include <algorithm>

#include "core/math/pml.h"

/**
 * NOTE: std::hash<T>()(t) and prism::hash(T t) will NOT return the same value, as prism::hash implements an additional seed to be hashed
 * std::hash<T>()(t) would work as expected
 * prism::hash(T t) effectively works as std::hash<int>()(seed) -> combine with std::hash<T>()(t)
*/

namespace {
/**
 * NOTE: combineHash does not give the same results for combineHash(a, b, c) and combineHash(v),
 * where v = vec<3, float>{a, b, c};
*/
// hash based on boost::hash_combine
template<typename First, typename... Rest> 
void combineHash(std::size_t& seed, const First& first, const Rest&... rest) {
    std::hash<First> hasher;
    seed ^= hasher(first) + 0x9e3779b97f4a7c55 + (seed << 6) + (seed >> 2);
    (combineHash(seed, rest), ...);
}

}

namespace prism {

template <class... Args>
std::size_t hash(Args... args) {
    std::size_t seed = 0u;
    combineHash(seed, args...);
    return seed;
}

}

namespace std {

// override hash for pml::vec objects
template<int L, typename T>
struct hash<prism::pml::vec<L, T>> {
    size_t operator()(const prism::pml::vec<L, T>& v) const {
        std::hash<T> hasher;
        std::size_t seed = 0u;
        for(int i = 0; i < L; i++) {
            seed ^= hasher(v[i]) + 0x9e3779b97f4a7c55 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

// // override hash for prism::EventType objects
// template<>
// struct hash<prism::EventType> {
//     std::size_t operator()(const prism::EventType& eventType) const {
//         std::uint8_t intValue = static_cast<std::uint8_t>(eventType);
//         return std::hash<std::uint8_t>()(intValue);
//     }
// };

// // override hash for prism::EventState objects
// template<>
// struct hash<prism::EventState> {
//     std::size_t operator()(const prism::EventState& eventState) const {
//         std::uint8_t intValue = static_cast<std::uint8_t>(eventState);
//         return std::hash<std::uint8_t>()(intValue);
//     }
// };

// // override hash for prism::MouseButton objects
// template<>
// struct hash<prism::MouseButton> {
//     std::size_t operator()(const prism::MouseButton& mouseButton) const {
//         std::uint8_t intValue = static_cast<std::uint8_t>(mouseButton);
//         return std::hash<std::uint8_t>()(intValue);
//     }
// };

// // override hash for prism::KeyId objects
// template<>
// struct hash<prism::KeyId> {
//     std::size_t operator()(const prism::KeyId& keyId) const {
//         std::uint32_t intValue = static_cast<std::uint32_t>(keyId);
//         return std::hash<std::uint32_t>()(intValue);
//     }
// };

// // override hash for prism::Event objects
// template<>
// struct hash<prism::Event> {
//     std::size_t operator()(const prism::Event& event) const {
//         std::size_t hashResult;
//         switch(event.getEventType()) {
//         case prism::EventType::KEY:
//             if (event.getKeyEvent().has_value())
//                 hashResult = prism::hash(event.getEventType(), event.getKeyEvent().value().key, event.getKeyEvent().value().keyState);
//             else 
//                 hashResult = prism::hash(event.getEventType());
//             break;
//         case prism::EventType::MOUSE_BUTTON:
//             if (event.getMouseButtonEvent().has_value())
//                 hashResult = prism::hash(event.getEventType(), event.getMouseButtonEvent().value().buttonId, event.getMouseButtonEvent().value().state);
//             else
//                 hashResult = prism::hash(event.getEventType());
//             break;
//         case prism::EventType::MOUSE_SCROLL:
//             if (event.getMouseScrollEvent().has_value())
//                 hashResult = prism::hash(event.getEventType(), event.getMouseScrollEvent().value().state);
//             else 
//                 hashResult = prism::hash(event.getEventType());
//             break;
//         case prism::EventType::EXIT:
//         case prism::EventType::FOCUS:
//         case prism::EventType::MOUSE:
//         case prism::EventType::MOUSE_MOVE:
//         case prism::EventType::NONE:
//         default:
//             hashResult = prism::hash(event.getEventType());
//             break;
//         }

//         return hashResult;
//     }
// };

}