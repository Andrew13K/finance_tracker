#ifndef MY_SQL_CONNECTION_HPP
#define MY_SQL_CONNECTION_HPP

#include <string>
#include <mysql/mysql.h>

using namespace std;

class MySQLConnection{
    private:
        MYSQL* conn;
        string host;
        string user;
        string password;
        string database;
        int port;
        bool connected;
    public:
        MySQLConnection();
        ~MySQLConnection();

        bool connect();
        void disconnect();
};

#endif