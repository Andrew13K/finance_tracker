#ifndef START_HPP
#define START_HPP

#include "mysql_connection.hpp"
#include <wx/wx.h>

class StartFrame: public wxFrame {
    public:
        StartFrame(const wxString& title, MySQLConnection& dbConn);
        ~StartFrame();
    private:
        MySQLConnection& db;
        void OnRegisterClick(wxCommandEvent& evt);
        void OnLoginClick(wxCommandEvent& evt);
};

#endif