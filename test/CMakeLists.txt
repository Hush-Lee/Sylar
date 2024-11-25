	include(FetchContent)

	FetchContent_Declare(
	  googletest
	  GIT_REPOSITORY https://github.com/google/googletest.git
	  GIT_TAG v1.15.2
	)
	FetchContent_GetProperties(googletest)

	add_executable(cpp_test "")

	target_sources(cpp_test
		PRIVATE
		test.cpp
	)
	target_link_libraries(cpp_test
		PRIVATE
	)
