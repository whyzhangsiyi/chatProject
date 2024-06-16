#ifndef JDBC_HPP
#define JDBC_HPP
// 数据库配置信息
#include <namespace.hpp>
#include <string>
#include <Logging.h>
// mysql连接器头文件
#include <driver.h>
#include <connection.h>
#include <prepared_statement.h>
#include <statement.h>
#include <resultset.h>
#include <memory>

using namespace sql;
class  QueryResultSet;

// 数据库操作类
class MySQL
{

public:
    MySQL();

    void DbUpdate(string sql);
    void DbExcuteSql(string sql);
    shared_ptr<QueryResultSet> DbQuery(string sql);
    ~MySQL();

private:
    // 连接数据库
private:
    sql::Connection *_conn;
};








class QueryResultSet
{
public:
    QueryResultSet(sql::Statement *sta, sql::ResultSet *res);
    ~QueryResultSet();

    sql::ResultSet *getRealResultSetPtr();

private:
    sql::Statement *_sta;
    sql::ResultSet *_res;
};


#endif