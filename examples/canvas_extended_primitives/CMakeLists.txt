cmake_minimum_required(VERSION 2.8.11)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
	string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
	if(flag_already_set EQUAL -1)
		check_cxx_compiler_flag("${flag}" flag_supported)
		if(flag_supported)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
		endif()
		unset(flag_supported CACHE)
	endif()
endfunction()

project(canvas_extended_example)

set(CMAKE_CXX_STANDARD 17)
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-pedantic")
enable_cxx_compiler_flag_if_supported("-Werror")

add_executable(sgfx_canvas_extended main.cpp)

find_package(glfw3)
find_package(GLEW)
find_package(OpenGL)

add_subdirectory(../../sgfx build)
target_link_libraries(sgfx_canvas_extended sgfx glfw GLEW GL)

install(TARGETS sgfx_canvas_extended DESTINATION bin)
