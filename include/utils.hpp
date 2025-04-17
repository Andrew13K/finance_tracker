#ifndef UTILS_HPP
#define UTILS_HPP

#include "mysql_connection.hpp"
#include <string>

using namespace std;

void loadEnvFile(const string& filepath = ".env");
string hashPassword(const string& password);
bool verifyPassword(const string& password, const string& hash);
bool executeSQLFromFile(MySQLConnection& db, const string& filepath);

#endif