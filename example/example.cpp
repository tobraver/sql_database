#include <iostream>
#include "../sql_database.h"

int main(int argc, char const *argv[])
{
    sql_database::sqlite::open("database.db");

    std::string sql = R"(create table if not exists "t_user" ( "id" int, "name" text, "age" int ))";
    int ret = sql_database::sqlite::exec(sql);
    std::string error = sql_database::sqlite::error_msg();
    printf("create result: %d, %s\n", ret, error.c_str());

    // sql = R"(insert into "t_user" values( '1', 'wz1', '1' ); insert into "t_user" values( '2', 'wz2', '2' );)";
    // ret = sql_database::sqlite::exec(sql);
    // error = sql_database::sqlite::error_msg();
    // printf("insert result: %d, %s\n", ret, error.c_str());

    sql = R"(select * from t_user;)";
    sql_database::result_t result;
    ret = sql_database::sqlite::query(sql, result);
    error = sql_database::sqlite::error_msg();

    printf("select result: %d, %s\n", ret, error.c_str());
    for(auto it: result.name)
    {
        printf("%s ", it.c_str());
    }
    printf("\n");

    for(auto value : result.value)
    {
        for(auto it : value)
        {
            printf("%s ", it.c_str());
        }
    printf("\n");
    }
    
    sql_database::sqlite::close();
    return 0;
}



