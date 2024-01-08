add_executable(PrismFileTests "")
target_sources(PrismFileTests PRIVATE
    PrismFileTest.cpp
)
target_link_libraries(PrismFileTests PUBLIC GTest::GTest PUBLIC prism)
add_test(PrismFileTests PrismFileTests)