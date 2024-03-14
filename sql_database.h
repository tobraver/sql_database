#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace sql_database
{

struct result_t
{
    std::vector<std::string> name; // column name
    std::vector<std::vector<std::string>> value; // multi row value
};

namespace sqlite
{

int open(const std::string& file);
int close(void);
int exec(const std::string& sql);
int query(const std::string& sql, result_t& result);
std::string error_msg(void);

}  // end of sql_database

} // end of sql_database
