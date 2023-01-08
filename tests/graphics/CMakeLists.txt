add_executable(VertexDataTests "")

target_sources(VertexDataTests PRIVATE
    VertexDataTest.cpp
)

target_link_libraries(VertexDataTests PUBLIC GTest::GTest PUBLIC prism)
add_test(VertexDataTests VertexDataTests)
