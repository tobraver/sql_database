cmake_minimum_required(VERSION 3.1.0)

project(sql_database_example)

# target
add_executable(sql_database_example example.cpp)

# -l
target_link_libraries(sql_database_example PRIVATE sql_database)