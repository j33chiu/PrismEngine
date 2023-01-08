# add each test

add_subdirectory("math")

add_executable(AutoResourceTests "")

target_sources(AutoResourceTests PRIVATE
	AutoResourceTest.cpp
)

target_link_libraries(AutoResourceTests PUBLIC GTest::GTest PUBLIC prism)
add_test(AutoResourceTests AutoResourceTests)

target_link_libraries(MathTests PUBLIC GTest::GTest PUBLIC prism)
add_test(MathTests MathTests)