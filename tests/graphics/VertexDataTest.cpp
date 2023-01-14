#include <gtest/gtest.h>

#include "graphics/Vertex.h"

namespace prismTest {

TEST(VertexDataTests, sizeOfVertexTests) {
    std::size_t floatPosSize = sizeof(prism::pml::vec3);
    std::size_t floatNormSize = sizeof(prism::pml::vec3);
    std::size_t floatColSize = sizeof(prism::pml::vec4);
    std::size_t floatTexUVSize = sizeof(prism::pml::vec2);
    std::size_t floatVertexSize = sizeof(prism::VertexDataFloat);
    ASSERT_EQ(floatVertexSize, 48);
    ASSERT_EQ(floatVertexSize, floatPosSize + floatNormSize + floatColSize + floatTexUVSize);

    std::size_t uint8VertexSize = sizeof(prism::VertexDataEfficient);
    ASSERT_EQ(uint8VertexSize, 9);

    prism::VertexDataFloat f{};
    prism::VertexDataEfficient e{};

    ASSERT_EQ(sizeof(f), floatVertexSize);
    ASSERT_EQ(sizeof(e), uint8VertexSize);

}

TEST(VertexDataTests, attributeInfoTests) {
    prism::VertexDataFloat f{};
    prism::VertexDataAttributes fattr = prism::getVertexDataAttributes(f);
    ASSERT_STREQ(fattr.vertexDataId.c_str(), "vertexDataFloat");
    ASSERT_EQ(fattr.attributes.size(), 4);
    ASSERT_EQ(fattr.componentLengths.size(), 4);
    ASSERT_EQ(fattr.componentTypes.size(), 4);

    prism::VertexDataEfficient e{};
    prism::VertexDataAttributes eattr = prism::getVertexDataAttributes(e);
    ASSERT_STREQ(eattr.vertexDataId.c_str(), "vertexDataEfficient");
    ASSERT_EQ(eattr.attributes.size(), 4);
    ASSERT_EQ(eattr.componentLengths.size(), 4);
    ASSERT_EQ(eattr.componentTypes.size(), 4);


}

TEST(VertexDataContainerTests, containerTests) {
    prism::VertexDataDebug v{
        .pos = prism::pml::vec3(1.0f, 1.1f, 1.2f),
        .colour = prism::pml::vec4(0.9f, 0.8f, 0.7f, 1.0f)
    };
    prism::VertexDataAttributes vAttr = prism::getVertexDataAttributes(v);
    prism::VertexContainer cont(vAttr);

    cont.addVertex(&v);

    v.pos = prism::pml::vec3(2.0f, 2.1f, 2.2f);
    v.colour = prism::pml::vec4(0.8f, 0.7f, 0.6f, 1.0f);

    cont.addVertex(&v);
    
    v.pos = prism::pml::vec3(3.0f, 3.1f, 3.2f);
    v.colour = prism::pml::vec4(0.7f, 0.6f, 0.5f, 1.0f);

    cont.addVertex(&v);

    ASSERT_EQ(cont.getNumVertices(), 3);
}

TEST(VertexDataContainerTests, containerApplicationTests) {
    // test application in engine with vertex data
    prism::VertexDataDebug v1 {
        .pos = prism::pml::vec3(1.1f, 1.2f, 1.3f),
        .colour = prism::pml::vec4(0.1f, 0.2f, 0.3f, 0.4f)
    };

    prism::VertexDataAttributes attr = prism::getVertexDataAttributes(v1);
    prism::VertexContainer container(attr);
    void* vertexPtr = &v1;
    container.addVertex(vertexPtr);

    std::vector<std::uint8_t> casted = container.getBytesCopy();
    std::uint8_t* castedPtr = casted.data();
    std::uint8_t* actual = static_cast<std::uint8_t*>(vertexPtr);
    // check each byte
    ASSERT_EQ(casted.size(), 28);
    for (int i = 0; i < 28; i++) {
        ASSERT_EQ(castedPtr[i], actual[i]);
    }

}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}