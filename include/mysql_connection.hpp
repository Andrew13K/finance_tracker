#ifndef MY_SQL_CONNECTION_HPP
#define MY_SQL_CONNECTION_HPP

#include <string>
#include <mysql/mysql.h>

using namespace std;

class MySQLConnection{
    private:
        MYSQL* conn;
        const char* host;
        const char* user;
        const char* password;
        const char* database;
        int port;
        bool connected;
    public:
        MySQLConnection();
        ~MySQLConnection();

        bool connect();
        void disconnect();
        bool executeQuery(const string& query);
        bool registration(const string& nickname, const string& name, 
                    const string& password, const string& email);
        bool login(const string& username, const string& password);
};

#endif