#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

using namespace std;

void loadEnvFile(const string& filepath = ".env");
string hashPassword(const string& password);
bool verifyPassword(const string& password, const string& hash);

#endif