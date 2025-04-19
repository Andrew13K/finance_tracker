#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "mysql_connection.hpp"
#include <wx/wx.h>

class LoginFrame: public wxFrame {
    public:
        LoginFrame(const wxString& title, MySQLConnection& db);
        void OnLoginClick(wxCommandEvent& evt);
        void HandleUserLogin();
    private:
        wxTextCtrl* usernameInput;
        wxTextCtrl* passwordInput;
        MySQLConnection& db;
};

#endif