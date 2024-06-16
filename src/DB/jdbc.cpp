#include <jdbc.hpp>

static string DbServer = "127.0.0.1:3306/chat";
static string DbUserName = "root";
static string DbPassword = "123456";
static sql::Driver *_driver = get_driver_instance();

// 初始化数据库连接
MySQL::MySQL()
{
    try
    {
        _conn = _driver->connect(DbServer, DbUserName, DbPassword);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        LOG_INFO << "数据库连接错误,服务断开";
        exit(1);
    }
}
// 释放数据库连接资源
MySQL::~MySQL()
{
    _conn->close();
    delete _conn;
}


void MySQL::DbExcuteSql(string sql)
{

    sql::Statement *sta = _conn->createStatement();
    try
    {
        sta->execute(sql);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        LOG_INFO << sql + "  数据库操作失败";
    }
}

void MySQL::DbUpdate(const string sql)
{

    sql::Statement *sta = _conn->createStatement();
    try
    {
        sta->executeUpdate(sql);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        LOG_INFO << sql + "  更新失败";
    }
    sta->close();
}

shared_ptr<QueryResultSet> MySQL::DbQuery(string sql)
{
    sql::Statement *sta = _conn->createStatement();
    sql::ResultSet *res;
    try
    {
        res = sta->executeQuery(sql);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        LOG_INFO << sql + "  查询失败";
    }
    shared_ptr<QueryResultSet> result=make_shared<QueryResultSet>(sta,res);
    return result;
}


//****************************************

QueryResultSet::QueryResultSet(sql::Statement *sta = nullptr, sql::ResultSet *res = nullptr)
    : _sta(sta), _res(res)
{
}

QueryResultSet::~QueryResultSet()
{


    _sta->close();
    _res->close();
}

sql::ResultSet *QueryResultSet::getRealResultSetPtr()
{
    return _res;
}
