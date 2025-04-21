#ifndef GUI_HPP
#define GUI_HPP

#include "mysql_connection.hpp"
#include <wx/wx.h>

class RegisterFrame : public wxFrame{
    public:
        RegisterFrame(const wxString& title, MySQLConnection& db);
        void OnRegisterClick(wxCommandEvent& evt);
        void HandleUserRegistration();
        void OnClose(wxCloseEvent& evt);
    private:
        wxTextCtrl* usernameInput;
        wxTextCtrl* nameInput;
        wxTextCtrl* passwordInput;
        wxTextCtrl* emailInput;
        MySQLConnection db;
};

#endif //GUI_HPP