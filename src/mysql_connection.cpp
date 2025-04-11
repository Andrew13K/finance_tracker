#include "../include/mysql_connection.hpp"
#include <mysql/mysql.h>
#include <iostream>
#include <string>

using namespace std;

MySQLConnection::MySQLConnection(): conn(NULL), connected(false){
    const string& host = getenv("DB_HOST");
    const string& user = getenv("DB_USER");
    const string& password = getenv("DB_PASSWORD");
    const string& database = getenv("DB_NAME");
    int port = stoi(getenv("DB_PORT"));

    conn = mysql_init(NULL);
    if(conn == NULL)
        cerr<<"MySQL initialization failed"<<endl;
}    

MySQLConnection::~MySQLConnection(){
    disconnect();
}

bool MySQLConnection::connect()
{
    if(connected) return true;

    if(mysql_real_connect(conn,host.c_str(), user.c_str(),password.c_str(),database.c_str(),
        port, NULL,0)==NULL)
    {
        cerr<<"Connection error: "<<mysql_error(conn)<<endl;
        return false;
    }
    connected = true;
    cout<<"Connected to MySQL database: "<<database<<endl;
    return true;
}

void MySQLConnection::disconnect()
{
    if(connected && conn)
    {
        mysql_close(conn);
        connected = false;
        cout<<"Disconnected from MySQL database"<<endl;
    }
}
