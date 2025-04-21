#ifndef DASH_HPP
#define DASH_HPP

#include "mysql_connection.hpp"
#include <wx/wx.h>

class DashboardFrame: public wxFrame {
    public:
        DashboardFrame(const wxString& title, const wxString& name, MySQLConnection& db);
        ~DashboardFrame();
        void OnClose(wxCloseEvent& evt);
    private:
        wxPanel* panel;
        MySQLConnection& db;
        wxStaticText* welcomeText;
};

#endif