add_executable(MathTests "")

target_sources(MathTests PRIVATE
	MathTest.cpp
)

target_link_libraries(MathTests PUBLIC GTest::GTest PUBLIC prism)
add_test(MathTests MathTests)