#include <gtest/gtest.h>
#include <unordered_map>
#include <string>


#include "core/PrismId.h"

namespace prismTest {

TEST(PrismIdTests, idTests) {
    prism::PrismId id1;
    prism::PrismId id2;
    prism::PrismId id3;
    prism::PrismId id4;

    ASSERT_TRUE(id1 == 1);
    ASSERT_TRUE(id2 == 2);
    ASSERT_TRUE(id3 == 3);
    ASSERT_TRUE(id4 == 4);
    ASSERT_TRUE(id1 == id1);
    ASSERT_TRUE(id1 != 2);
    ASSERT_TRUE(id1 != id2);
    ASSERT_FALSE(id4 != 4);
    ASSERT_FALSE(id1 == id2);

    prism::PrismId id15 = 15;
    ASSERT_TRUE(id15 == 15);
    ASSERT_TRUE(id15 != id1);
    ASSERT_FALSE(id15 == 1);

    prism::PrismId id5(5);
    ASSERT_TRUE(id5 == 5);
    ASSERT_TRUE(id5 != id1);
    ASSERT_FALSE(id5 == 1);

    prism::PrismId id5Copy(id5);
    ASSERT_TRUE(id5Copy == 5);
    ASSERT_TRUE(id5Copy == id5);
    ASSERT_TRUE(id5Copy != id1);
    ASSERT_FALSE(id5Copy == 1);

    prism::PrismId id5Copy2 = id5;
    ASSERT_TRUE(id5Copy2 == 5);
    ASSERT_TRUE(id5Copy2 == id5);
    ASSERT_TRUE(id5Copy2 == id5Copy);
    ASSERT_TRUE(id5Copy2 != id1);
    ASSERT_FALSE(id5Copy2 == 1);

    id5Copy2 = 90;
    ASSERT_TRUE(id5Copy2 == 90);
    ASSERT_FALSE(id5Copy2 == id5);
    ASSERT_FALSE(id5Copy2 == id5Copy);
    ASSERT_TRUE(id5Copy2 != id1);
    ASSERT_FALSE(id5Copy2 == 1);

}


TEST(PrismIdTests, hashTests) {
    prism::PrismId id101{101};
    prism::PrismId id101Copy{101};

    std::uint32_t value1 = 1;
    std::uint32_t value2 = 2;
    std::uint32_t value3 = 3;

    std::unordered_map<prism::PrismId, std::uint32_t> map;

    map.emplace(id101, value1);
    ASSERT_EQ(map[id101], value1);
    map.emplace(id101, value2);
    ASSERT_NE(map[id101], value2);
    ASSERT_EQ(map[id101], value1); // emplace inserts new element if key is unique
    map[id101Copy] = value2;
    ASSERT_EQ(map[id101Copy], value2);
    ASSERT_EQ(map[id101Copy], map[id101]);
    map[id101Copy] = value1;
    ASSERT_EQ(map[id101Copy], value1);
    ASSERT_EQ(map[id101Copy], map[id101]);

    prism::PrismId id102{102};
    map.emplace(id102, value3);
    ASSERT_EQ(map[id102], value3);
    ASSERT_EQ(map[id101], value1);
    ASSERT_EQ(map.size(), 2);

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}