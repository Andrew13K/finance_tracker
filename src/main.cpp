#include "../include/utils.hpp"
#include "../include/mysql_connection.hpp"
#include <iostream>

using namespace std;

int main()
{
    loadEnvFile();
    MySQLConnection db;

    if(!db.connect())
        return 1;
    cout << "Programm is running!"<<endl;
    return 0;
}