#include "graphics/MeshManager.h"

#include <functional>
#include <string>

#include "util/PrismHash.h"

namespace prism {

MeshManager::MeshManager()
    : loadedMeshes()
{}

const Mesh* MeshManager::generateQuad(
    const pml::vec4& colour,
    const pml::vec3& topLeft,
    const pml::vec3& topRight,
    const pml::vec3& bottomRight,
    const pml::vec3& bottomLeft) 
{
    // generate id
    std::size_t meshId = prism::hash("__quad__", colour, topLeft, topRight, bottomRight, bottomLeft);

    if (loadedMeshes.find(meshId) != loadedMeshes.end()) {
        return loadedMeshes[meshId].mesh.get();
    }

    // create vertices and indices
    VertexDataDebug v1, v2, v3, v4;
    v1.pos = topLeft;
    v1.colour = colour;
    v2.pos = topRight;
    v2.colour = colour;
    v3.pos = bottomRight;
    v3.colour = colour;
    v4.pos = bottomLeft;
    v4.colour = colour;

    VertexDataAttributes vertexDataAttr = getVertexDataAttributes(v1);
    std::unique_ptr<VertexContainer> container = std::make_unique<VertexContainer>(vertexDataAttr);

    container->addVertex(&v1);
    container->addVertex(&v2);
    container->addVertex(&v3);
    container->addVertex(&v4);

    std::vector<std::uint32_t> indices {
        0, 1, 2, 0, 2, 3
    };

    std::unique_ptr<Mesh> quadMesh = createUniqueMesh(std::move(container), indices);
    loadedMeshes[meshId] = {meshId, std::move(quadMesh)};
    return loadedMeshes[meshId].mesh.get();
}

const Mesh* MeshManager::generateTriangle(
    const pml::vec4& colour,
    const pml::vec3& a,
    const pml::vec3& b,
    const pml::vec3& c) 
{
    // generate id
    std::size_t meshId = prism::hash("__triangle__", colour, a, b, c);

    if (loadedMeshes.find(meshId) != loadedMeshes.end()) {
        return loadedMeshes[meshId].mesh.get();
    }
    
    // create vertices and indices
    VertexDataDebug v1, v2, v3;
    v1.pos = a;
    v1.colour = colour;
    v2.pos = b;
    v2.colour = colour;
    v3.pos = c;
    v3.colour = colour;

    VertexDataAttributes vertexDataAttr = getVertexDataAttributes(v1);
    std::unique_ptr<VertexContainer> container = std::make_unique<VertexContainer>(vertexDataAttr);

    container->addVertex(&v1);
    container->addVertex(&v2);
    container->addVertex(&v3);

    std::vector<std::uint32_t> indices {
        0, 1, 2
    };

    std::unique_ptr<Mesh> quadMesh = createUniqueMesh(std::move(container), indices);
    loadedMeshes[meshId] = {meshId, std::move(quadMesh)};
    return loadedMeshes[meshId].mesh.get();
}

const Mesh* MeshManager::generateCube(
    const pml::vec4& colour,
    const pml::FLOAT dimension) 
{
    // generate id
    std::size_t meshId = prism::hash("__cube__", colour, dimension);

    if (loadedMeshes.find(meshId) != loadedMeshes.end()) {
        return loadedMeshes[meshId].mesh.get();
    }

    // create vertices and indices
    VertexDataDebug v1, v2, v3, v4, v5, v6, v7, v8;
    v1.pos = pml::vec3(0.0f, 0.0f, 0.0f);
    v1.colour = colour;
    v2.pos = pml::vec3(dimension, 0.0f, 0.0f);
    v2.colour = colour;
    v3.pos = pml::vec3(dimension, 0.0f, dimension);
    v3.colour = colour;
    v4.pos = pml::vec3(0.0f, 0.0f, dimension);
    v4.colour = colour;

    v5.pos = pml::vec3(0.0f, dimension, 0.0f);
    v5.colour = colour;
    v6.pos = pml::vec3(dimension, dimension, 0.0f);
    v6.colour = colour;
    v7.pos = pml::vec3(dimension, dimension, dimension);
    v7.colour = colour;
    v8.pos = pml::vec3(0.0f, dimension, dimension);
    v8.colour = colour;


    VertexDataAttributes vertexDataAttr = getVertexDataAttributes(v1);
    std::unique_ptr<VertexContainer> container = std::make_unique<VertexContainer>(vertexDataAttr);

    container->addVertex(&v1);
    container->addVertex(&v2);
    container->addVertex(&v3);
    container->addVertex(&v4);
    container->addVertex(&v5);
    container->addVertex(&v6);
    container->addVertex(&v7);
    container->addVertex(&v8);

    std::vector<std::uint32_t> indices {
        0, 2, 1, 0, 3, 2, 
        4, 5, 6, 4, 6, 7, 
        6, 5, 1, 6, 1, 2,
        4, 7, 3, 4, 3, 0,
        7, 6, 2, 7, 2, 3, 
        4, 1, 5, 4, 0, 1
    };

    std::unique_ptr<Mesh> quadMesh = createUniqueMesh(std::move(container), indices);
    loadedMeshes[meshId] = {meshId, std::move(quadMesh)};
    return loadedMeshes[meshId].mesh.get();
}

const Mesh* MeshManager::createMesh(
    std::unique_ptr<VertexContainer> vertexContainer, 
    const std::vector<std::uint32_t>& indices)
{
    assert(indices.size() >= 2);
    // generate hash
    std::size_t meshId = prism::hash(vertexContainer->getVertexAttr().vertexDataId, vertexContainer->getNumVertices(), indices.size());
    
    if (loadedMeshes.find(meshId) != loadedMeshes.end()) {
        return loadedMeshes[meshId].mesh.get();
    }

    std::unique_ptr<Mesh> mesh = createUniqueMesh(std::move(vertexContainer), indices);
    loadedMeshes[meshId] = {meshId, std::move(mesh)};
    return loadedMeshes[meshId].mesh.get();
}

}