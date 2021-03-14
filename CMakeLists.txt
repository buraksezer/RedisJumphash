cmake_minimum_required(VERSION 3.17)
project(RedisJumphash C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules)

find_package(XXHASH REQUIRED)
INCLUDE_DIRECTORIES("${XXHASH_INCLUDES}")

add_library(RedisJumphash SHARED jumphash.c redismodule.h)
target_link_libraries(RedisJumphash ${XXHASH_LIBRARIES})