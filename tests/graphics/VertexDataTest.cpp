#include <gtest/gtest.h>

#include "graphics/Vertex.h"

namespace prismTest {

TEST(VertexDataContainerTests, containerTests) {
    prism::VertexDescriptor description;
    description.addVertexComponent(3, prism::VertexAttributeType::FLOAT);
    description.addVertexComponent(4, prism::VertexAttributeType::FLOAT);

    prism::VertexContainer container(description);

    prism::Vertex v(description);
    v.addData(prism::pml::vec3(1.0f, 1.1f, 1.2f));
    v.addData(prism::pml::vec4(0.9f, 0.8f, 0.7f, 1.0f));

    container.addVertex(v);
    ASSERT_EQ(container.getNumVertices(), 1);

    container.addRawData(prism::pml::vec3(2.0f, 2.1f, 2.2f));
    container.addRawData(prism::pml::vec4(0.8f, 0.7f, 0.6f, 1.0f));
    ASSERT_EQ(container.getNumVertices(), 2);

    container.addRawData(prism::pml::vec3(3.0f, 3.1f, 3.2f));
    container.addRawData(prism::pml::vec4(0.7f, 0.6f, 0.5f, 1.0f));
    ASSERT_EQ(container.getNumVertices(), 3);
}

TEST(VertexDataContainerTests, containerApplicationTests) {
    // test application in engine with vertex data

    prism::VertexDescriptor description;
    description.addVertexComponent(3, prism::VertexAttributeType::FLOAT);
    description.addVertexComponent(4, prism::VertexAttributeType::FLOAT);

    prism::Vertex v(description);
    v.addData(prism::pml::vec3(1.1f, 1.2f, 1.3f));
    v.addData(prism::pml::vec4(0.1f, 0.2f, 0.3f, 0.4f));

    prism::VertexContainer container(description);
    container.addVertex(v);

    prism::VertexDescriptor description2;
    description.addVertexComponent(3, prism::VertexAttributeType::FLOAT);
    description.addVertexComponent(4, prism::VertexAttributeType::FLOAT);

    prism::VertexContainer container2(description2);
    container2.addRawData(prism::pml::vec3(1.1f, 1.2f, 1.3f));
    container2.addRawData(prism::pml::vec4(0.1f, 0.2f, 0.3f, 0.4f));

    auto containerData = container.getBytes();
    auto container2Data = container2.getBytes();

    ASSERT_EQ(containerData.size(), container2Data.size());

    for (int i = 0; i < containerData.size(); i++) {
        ASSERT_EQ(containerData[i], container2Data[i]);
    }

    struct {
        prism::pml::vec3 pos = prism::pml::vec3(1.1f, 1.2f, 1.3f);
        prism::pml::vec4 col = prism::pml::vec4(0.1f, 0.2f, 0.3f, 0.4f);
    } testData;

    void* testDataPtr = &testData;
    std::uint8_t* castedtestDataPtr = static_cast<std::uint8_t*>(testDataPtr);

    for (int i = 0; i < containerData.size(); i++) {
        ASSERT_EQ(containerData[i], castedtestDataPtr[i]);        
    }
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}