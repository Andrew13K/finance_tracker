#include <iostream>
#include <mysql/mysql.h>
#include <string>

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
        MySQLConnection(
            const string& host = "localhost",
            const string& user = "username",
            const string& password = "password",
            const string& database = "db_name",
            int port = 3306
        ):host(host),user(user),password(password),database(database),
        port(port),connected(false){
            conn = mysql_init(NULL);
            if(conn == NULL)
                cerr<<"MySQL initialization failed"<<endl;
        }

        ~MySQLConnection(){
            disconnect();
        }

        void disconnect()
        {
            if(connected && conn)
            {
                mysql_close(conn);
                connected = false;
                cout<<"Disconnected from MySQL database"<<endl;
            }
        }
};

int main()
{

    return 0;
}