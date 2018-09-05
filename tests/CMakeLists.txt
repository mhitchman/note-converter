project(tests)

add_executable(tests
	testMain.cpp
	test_file.cpp)

target_link_libraries(tests
	PRIVATE
	notelib
	Catch2::Catch2)

include(Catch)
catch_discover_tests(tests)
