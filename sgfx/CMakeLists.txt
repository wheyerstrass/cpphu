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

project(libsgfx)

set(CMAKE_CXX_STANDARD 17)
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-pedantic")
enable_cxx_compiler_flag_if_supported("-Werror")

add_library(sgfx STATIC src/canvas.cpp src/primitives.cpp src/window.cpp)
target_include_directories(sgfx PUBLIC include)

install(TARGETS sgfx DESTINATION lib)
install(DIRECTORY include/sgfx DESTINATION include)
