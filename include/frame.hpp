#ifndef GUI_HPP
#define GUI_HPP

#include "mysql_connection.hpp"
#include <wx/wx.h>

class MainFrame : public wxFrame{
    public:
        MainFrame(const wxString& title, MySQLConnection& db);
        void OnRegisterClick(wxCommandEvent& evt);
        void HandleUserRegistration();
        wxTextCtrl* usernameInput;
        wxTextCtrl* nameInput;
        wxTextCtrl* passwordInput;
        wxTextCtrl* emailInput;
    private:
        MySQLConnection db;
};

#endif //GUI_HPP