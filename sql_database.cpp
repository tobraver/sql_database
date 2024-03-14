#include <mutex>

#include "sql_database.h"

#include "SQLiteCpp/SQLiteCpp.h"

namespace sql_database
{

namespace sqlite
{

/**
 * @brief sqlite desc
*/
struct desc_t
{
    bool is_open = false;
    std::mutex  mutex;
    std::string file;
    std::string error;
    SQLite::Database* db;
};

/**
 * @brief golbal sqlite desc
*/
desc_t g_sqlite_desc;

/**
 * @brief open database
*/
int open(const std::string& file)
{
    int ret = -1;
    
    std::lock_guard<std::mutex> lock(g_sqlite_desc.mutex);

    try
    {
        std::cout << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << std::endl;
        std::cout << "SQliteC++ version " << SQLITECPP_VERSION << std::endl;

        g_sqlite_desc.file = file;
        g_sqlite_desc.db = new SQLite::Database(file, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        g_sqlite_desc.error = g_sqlite_desc.db->getErrorMsg();
        ret = g_sqlite_desc.db->getErrorCode();
    }
    catch (std::exception& e)
    {
        g_sqlite_desc.error = e.what();
        // std::cout << "SQLITE EXCEPTION: " << e.what() << std::endl;
    }
    return ret;
}

/**
 * @brief close database
*/
int close(void)
{
    std::lock_guard<std::mutex> lock(g_sqlite_desc.mutex);

    try
    {
        if(g_sqlite_desc.db)
        {
            delete g_sqlite_desc.db;
        }
    }
    catch (std::exception& e)
    {
        g_sqlite_desc.error = e.what();
        // std::cout << "SQLITE EXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}

int exec(const std::string& sql)
{
    int ret = -1;
    std::lock_guard<std::mutex> lock(g_sqlite_desc.mutex);
    try
    {
        ret = g_sqlite_desc.db->tryExec(sql);
        g_sqlite_desc.error = g_sqlite_desc.db->getErrorMsg();
    }
    catch (std::exception& e)
    {
        g_sqlite_desc.error = e.what();
        // std::cout << "SQLITE EXCEPTION: " << e.what() << std::endl;
    }
    return ret;
}

// SELECT
int exec(const std::string& sql, result_t& result)
{
    int ret = -1;
    std::lock_guard<std::mutex> lock(g_sqlite_desc.mutex);
    try
    {
        SQLite::Statement query(*g_sqlite_desc.db, sql);

        while (query.executeStep())
        {
            std::vector<std::string> val;
            for(int i=0; i<query.getColumnCount(); i++)
            {
                val.push_back(query.getColumn(i));
            }
            result.value.push_back(val);
            
            if(result.name.empty())
            {
                for(int i=0; i<query.getColumnCount(); i++)
                {
                    result.name.push_back(query.getColumnName(i));
                }
            }
        }

        ret = 0;
        g_sqlite_desc.error = "not an error";
    }
    catch (std::exception& e)
    {
        ret = g_sqlite_desc.db->getErrorCode();
        g_sqlite_desc.error = e.what();
        // std::cout << "SQLITE EXCEPTION: " << e.what() << std::endl;
    }
    return ret;
}

std::string error_msg(void)
{
    std::lock_guard<std::mutex> lock(g_sqlite_desc.mutex);
    return g_sqlite_desc.error;
}

}  // end of sql_database

} // end of sql_database

