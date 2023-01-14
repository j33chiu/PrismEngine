add_executable(PrismHashTests "")
target_sources(PrismHashTests PRIVATE
    PrismHashTest.cpp
)
target_link_libraries(PrismHashTests PUBLIC GTest::GTest PUBLIC prism)
add_test(PrismHashTests PrismHashTests)