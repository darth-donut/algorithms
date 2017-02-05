# project definition
cmake_minimum_required(VERSION 3.5)
project(trie)

# configuration
set(HDRS Trie.h Node.h)

# compiler options
set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-Werror -Wpedantic -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# exe
set(SOURCE_FILES main.cpp Trie.cc ${HDRS})
add_executable(ctrie ${SOURCE_FILES})

# lib
set(HDR Trie.cc ${HDRS})
add_library(trie SHARED ${HDR})


# installation instructions
install(TARGETS trie DESTINATION /home/jiahong/Templates)
install(FILES ${HDRS}  DESTINATION /home/jiahong/Templates/include)
