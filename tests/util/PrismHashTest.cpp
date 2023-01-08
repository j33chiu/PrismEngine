#include <gtest/gtest.h>

#include "util/PrismHash.h"
#include "core/math/pml.h"

namespace prismTest {

TEST(PrismHashTests, hashTests) {
    std::hash<int> intHasher;
    std::hash<float> floatHasher;
    

    std::size_t hash1 = prism::hash(10, 1, 1111.0f);

    std::tuple<int, int, float> t1{10, 1, 1111.0f};
    std::size_t hash2 = std::apply(prism::hash<int, int, float>, t1);

    std::size_t hash3 = 0u;
    hash3 ^= intHasher(10) + 0x9e3779b97f4a7c55 + (hash3 << 6) + (hash3 >> 2);
    hash3 ^= intHasher(1) + 0x9e3779b97f4a7c55 + (hash3 << 6) + (hash3 >> 2);
    hash3 ^= floatHasher(1111.0f) + 0x9e3779b97f4a7c55 + (hash3 << 6) + (hash3 >> 2);
    

    ASSERT_EQ(hash1, hash3);
    ASSERT_EQ(hash2, hash3);


    // expected behaviour when hashing pml::vec objects:
    prism::pml::vec4 v1(1.0f, 1.0f, 1.23f, -4.5f);
    prism::pml::vec4 v2(91.0f, -1.0f, 4.56f, -80.1f);
    
    std::size_t hash4 = prism::hash(v1, v2); 

    // it is not the combination of the 8 float values, but rather 1 hash for each pml::vec, then they are combined
    std::size_t hash5 = 0u;
    hash5 ^= floatHasher(1.0f) + 0x9e3779b97f4a7c55 + (hash5 << 6) + (hash5 >> 2);
    hash5 ^= floatHasher(1.0f) + 0x9e3779b97f4a7c55 + (hash5 << 6) + (hash5 >> 2);
    hash5 ^= floatHasher(1.23f) + 0x9e3779b97f4a7c55 + (hash5 << 6) + (hash5 >> 2);
    hash5 ^= floatHasher(-4.5f) + 0x9e3779b97f4a7c55 + (hash5 << 6) + (hash5 >> 2);
    std::size_t hash6 = 0u;
    hash6 ^= floatHasher(91.0f) + 0x9e3779b97f4a7c55 + (hash6 << 6) + (hash6 >> 2);
    hash6 ^= floatHasher(-1.0f) + 0x9e3779b97f4a7c55 + (hash6 << 6) + (hash6 >> 2);
    hash6 ^= floatHasher(4.56f) + 0x9e3779b97f4a7c55 + (hash6 << 6) + (hash6 >> 2);
    hash6 ^= floatHasher(-80.1f) + 0x9e3779b97f4a7c55 + (hash6 << 6) + (hash6 >> 2);
    std::size_t hash7 = 0u;
    hash7 ^= hash5 + 0x9e3779b97f4a7c55 + (hash7 << 6) + (hash7 >> 2);
    hash7 ^= hash6 + 0x9e3779b97f4a7c55 + (hash7 << 6) + (hash7 >> 2);

    ASSERT_EQ(hash4, hash7);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}