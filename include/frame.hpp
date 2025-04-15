#ifndef GUI_HPP
#define GUI_HPP

#include "mysql_connection.hpp"
#include <wx/wx.h>

class MainFrame : public wxFrame{
    public:
        MainFrame(const wxString& title, MySQLConnection& db);
    private:
        MySQLConnection& dbRef;
        wxTextCtrl* usernameInput;
        wxTextCtrl* nameInput;
        wxTextCtrl* passwordInput;
        wxTextCtrl* emailInput;
        
        void OnRegisterClick(wxCommandEvent& evt);
        
};

#endif //GUI_HPP