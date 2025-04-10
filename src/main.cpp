#include <iostream>
#include <mysql/mysql.h>
#include <string>

class MySQLConnection{
    private:
        MYSQL* conn;
        std::string host;
        std::string user;
        std::string password;
        std::string database;
        int port;
        bool connected;

};

int main()
{

    return 0;
}