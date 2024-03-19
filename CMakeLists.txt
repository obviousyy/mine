cmake_minimum_required(VERSION 3.21)
project(mine)

set(CMAKE_CXX_STANDARD 14)

include_directories(D:/App/easyx/include)
link_directories(D:/App/easyx/lib64)
link_libraries(libeasyx.a)

add_executable(mine WIN32 main.cpp mine.cpp mine.hpp choose.cpp choose.hpp time.cpp time.hpp mine_map.cpp mine_map.hpp)

add_compile_options ( -O3)
