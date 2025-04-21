#include "../include/mysql_connection.hpp"
#include "../include/utils.hpp"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sodium.h>
#include <sstream>

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
    return true;
}

bool MySQLConnection::registration(const string& nickname, const string& name, 
                            const string& password, const string& email){
    if(!connected) {
        cerr << "Database is not connected" << endl;
        return false;
    }
    
    string hashedPassword = hashPassword(password);

    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        cerr << "Could not initialize statement" << endl;
        return false;
    }
    
    const char *query = "INSERT INTO User (nickname, name, password, email) VALUES (?, ?, ?, ?)";
    
    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        cerr << "Failed to prepare statement: " << mysql_stmt_error(stmt) << endl;
        mysql_stmt_close(stmt);
        return false;
    }
    
    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));
    
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)nickname.c_str();
    bind[0].buffer_length = nickname.length();
    
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (void*)name.c_str();
    bind[1].buffer_length = name.length();
    
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (void*)hashedPassword.c_str();
    bind[2].buffer_length = hashedPassword.length();
    
    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (void*)email.c_str();
    bind[3].buffer_length = email.length();
    
    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        cerr << "Failed to bind parameters: " << mysql_stmt_error(stmt) << endl;
        mysql_stmt_close(stmt);
        return false;
    }
    
    if (mysql_stmt_execute(stmt) != 0) {
        cerr << "Registration failed: " << mysql_stmt_error(stmt) << endl;
        mysql_stmt_close(stmt);
        return false;
    }
    
    mysql_stmt_close(stmt);
    cout << "User successfully registered!" << endl;
    return true;
}

bool MySQLConnection::login(const string& username, const string& password){
    if(!connected) {
        cerr << "Database is not connected" << endl;
        return false;
    }

    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        cerr << "Could not initialize statement" << endl;
        return false;
    }
    
    const char *query = "SELECT password FROM User WHERE nickname = ?";
    
    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        cerr << "Failed to prepare statement: " << mysql_stmt_error(stmt) << endl;
        mysql_stmt_close(stmt);
        return false;
    }
    
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)username.c_str();
    bind[0].buffer_length = username.length();
    
    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        cerr << "Failed to bind parameters: " << mysql_stmt_error(stmt) << endl;
        mysql_stmt_close(stmt);
        return false;
    }
    
    if (mysql_stmt_execute(stmt) != 0) {
        cerr << "Query execution failed: " << mysql_stmt_error(stmt) << endl;
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND result[1];
    memset(result, 0, sizeof(result));

    char hash_buffer[crypto_pwhash_STRBYTES];
    unsigned long hash_length;
    bool is_null;

    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = hash_buffer;
    result[0].buffer_length = sizeof(hash_buffer);
    result[0].length = &hash_length;
    result[0].is_null = &is_null;    

    if (mysql_stmt_bind_result(stmt, result) != 0) {
        cerr << "Failed to bind result: " << mysql_stmt_error(stmt) << endl;
        mysql_stmt_close(stmt);
        return false;
    }
    
    if (mysql_stmt_fetch(stmt) != 0) {
        mysql_stmt_close(stmt);
        cout << "Invalid username or password." << endl;
        return false;
    }
    
    if (is_null) {
        mysql_stmt_close(stmt);
        cout << "Invalid username or password." << endl;
        return false;
    }

    string storedHash(hash_buffer, hash_length);
    mysql_stmt_close(stmt);
    
    bool success = verifyPassword(storedHash, password);
    
    if (success) {
        cout << "Successful login!" << endl;
    } else {
        cout << "Invalid username or password." << endl;
    }
    
    return success;
}