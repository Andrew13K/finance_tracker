#ifndef DASH_HPP
#define DASH_HPP

#include <wx/statline.h>
#include <wx/wx.h>
#include "mysql_connection.hpp"

class DashboardFrame: public wxFrame {
    public:
        DashboardFrame(const wxString& title, const wxString& name, MySQLConnection& db);
        ~DashboardFrame();
    private:
        void OnClose(wxCloseEvent& evt);

        // UI Elements
        wxPanel* panel;
        wxStaticText* welcomeText;
        wxBoxSizer* navSizer;

        // Bottom nav buttons
        wxButton* btnProfile;
        wxButton* btnHistory;
        wxButton* btnFriends;

        // DB reference
        MySQLConnection& db;
};

#endif