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


void containerHelperFunc(const prism::BaseVertexContainer& genericCont, const void* testPtr, std::string vertexDataId) {
    ASSERT_EQ(genericCont.getNumVertices(), 4);
    ASSERT_EQ(genericCont.getDataSize(), sizeof(prism::VertexDataDebug) * 4);
    ASSERT_EQ(genericCont.getVerticesAddress(), testPtr);
    ASSERT_EQ(genericCont.getVertexDataAttributes().vertexDataId, vertexDataId);

    prism::VertexDataDebug v1{
        .pos = prism::pml::vec3(1.0f, 1.1f, 1.2f),
        .colour = prism::pml::vec4(0.9f, 0.8f, 0.7f, 1.0f)
    };

    //prism::BaseVertexContainer copy(genericCont);

    const prism::VertexContainer<prism::VertexDataDebug>& casted = static_cast<const prism::VertexContainer<prism::VertexDataDebug>&>(genericCont);
    prism::VertexContainer<prism::VertexDataDebug> copyCasted(casted);
    ASSERT_EQ(copyCasted.getNumVertices(), 4);
    ASSERT_EQ(copyCasted.getDataSize(), sizeof(prism::VertexDataDebug) * 4);
    // can't check copy's address since it is a new object
    ASSERT_EQ(copyCasted.getVertexDataAttributes().vertexDataId, vertexDataId);
}

TEST(VertexDataContainerTests, containerTests) {
    prism::VertexDataDebug v1{
        .pos = prism::pml::vec3(1.0f, 1.1f, 1.2f),
        .colour = prism::pml::vec4(0.9f, 0.8f, 0.7f, 1.0f)
    };
    prism::VertexDataAttributes vAttr = prism::getVertexDataAttributes(v1);

    prism::VertexContainer<prism::VertexDataDebug> cont1(vAttr);

    cont1.addVertex(v1);

    {
        prism::VertexDataDebug v2{
            .pos = prism::pml::vec3(2.0f, 2.1f, 2.2f),
            .colour = prism::pml::vec4(0.8f, 0.7f, 0.6f, 1.0f)
        };
        prism::VertexDataDebug v3{
            .pos = prism::pml::vec3(3.0f, 3.1f, 3.2f),
            .colour = prism::pml::vec4(0.7f, 0.6f, 0.5f, 1.0f)
        };
        cont1.addVertex(v2);
        cont1.addVertex(v3);
    }

    const std::vector<prism::VertexDataDebug>& vertices = cont1.getVertices();



    ASSERT_EQ(vertices.size(), 3);

    prism::VertexDataDebug v4{
        .pos = prism::pml::vec3(4.0f, 4.1f, 4.2f),
        .colour = prism::pml::vec4(0.6f, 0.5f, 0.4f, 1.0f)
    };
    cont1.addVertex(v4);

    ASSERT_EQ(vertices.size(), 4);
    ASSERT_EQ(vertices.data(), cont1.getVerticesAddress());

    containerHelperFunc(std::move(cont1), vertices.data(), vAttr.vertexDataId);

    ASSERT_EQ(cont1.getNumVertices(), 4);

}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}