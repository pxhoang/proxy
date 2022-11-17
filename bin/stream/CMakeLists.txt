file(GLOB_RECURSE SRC *.cpp)
add_executable(stream ${SRC})
target_link_libraries(stream PRIVATE lib1)