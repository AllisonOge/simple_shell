cmake_minimum_required(VERSION 3.11)
project(myshell C)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_C_COMPILER "/usr/bin/gcc")

# set C flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra -Werror -O")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG} -Wall -pedantic -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# set the C standard
set(CMAKE_C_STANDARD 90)

enable_testing()

# add_subdirectory(test)

include_directories(include)
file(GLOB_RECURSE SRC main.c 
	hsh.c)
add_executable(myshell ${SRC})

add_custom_target(
	copy-compile-commands ALL
	${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_BINARY_DIR}/compile_commands.json
	${CMAKE_CURRENT_LIST_DIR}
)

