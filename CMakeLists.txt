cmake_minimum_required(VERSION 3.1.0)

project(sql_database)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC_LIST sql_database.cpp)

# target
add_library(${PROJECT_NAME} ${SRC_LIST})

# -I
target_include_directories(${PROJECT_NAME} PUBLIC . ${CMAKE_CURRENT_LIST_DIR}/third/SQLiteCpp)

# -L
target_link_directories(${PROJECT_NAME} PUBLIC )

# -l
target_link_libraries(${PROJECT_NAME} PRIVATE SQLiteCpp)

# SQLiteCpp
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third/SQLiteCpp)

# example
add_subdirectory(example)