#ifndef APP_HPP
#define APP_HPP

#include <wx/wx.h>
#include "mysql_connection.hpp"

class App : public wxApp{
    public:
        bool OnInit();
        ~App();
    private:
        MySQLConnection* db;
};

#endif