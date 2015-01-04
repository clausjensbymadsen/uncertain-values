cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -m64 -Wall -Wextra -Wfatal-errors -pedantic -Wformat=2 -Wstrict-overflow=5 -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef -Werror -Wzero-as-null-pointer-constant -Wuseless-cast")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

project(UncertaintyTests)
include_directories("../src")
add_executable(UncertaintyTests uncertainty_gtest.cpp)
target_link_libraries(UncertaintyTests gtest_main.a)