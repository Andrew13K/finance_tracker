#include "../include/mysql_connection.hpp"
#include <mysql/mysql.h>
#include <iostream>
#include <string>

using namespace std;

MySQLConnection::MySQLConnection(): conn(NULL), connected(false){
    const char* host_env = getenv("DB_HOST");
    const char* user_env = getenv("DB_USER");
    const char* password_env = getenv("DB_PASSWORD");
    const char* database_env = getenv("DB_NAME");
    int port_env = stoi(getenv("DB_PORT"));

    host = host_env ? host_env : "localhost";
    user = user_env ? user_env : "root";
    password = password_env ? password_env : "your_password";
    database = database_env ? database_env : "manage_spendings";
    port = port_env ? port_env : 3360;

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

    if(mysql_real_connect(conn, host, user, password, database,
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

bool MySQLConnection::executeQuery(const string& query)
{
    if(!connected)
    {
        cerr<<"Database is not connected"<<endl;
        return false;
    }
    if(mysql_query(conn, query.c_str()) != 0)
    {
        cerr<<"Error during query execution: "<<mysql_error(conn)<<endl;
        return false;
    }
    cout<<"Query executed correctly"<<endl;
    return true;
}
