# cmake/project config
cmake_minimum_required(VERSION 3.5)
project(trie)

# C++ compiler standard
set(CMAKE_CXX_STANDARD 11)
# Compiler options
set(FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${FLAGS})

# boost test
#find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

# Trie sources/headers
set(TRIE_HDR src/Node.h src/Trie.h)


# tests
#[[
set(TEST_SOURCE_FILES test/Trie_test.cpp src/Node.h src/Trie.h)
add_executable(trie_test ${TEST_SOURCE_FILES})
target_link_libraries(trie_test ${Boost_FILESYSTEM_LIBRARY}
                                ${Boost_SYSTEM_LIBRARY}
                                ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
]]

# manual testing (main driver)
add_executable(main src/main.cc ${TRIE_HDR})

# installs Trie and Node.h to specified location
install(FILES ${TRIE_HDR} DESTINATION /usr/local/include/ds/trie)
