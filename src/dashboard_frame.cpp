#include "../include/dashboard_frame.hpp"
#include "../include/mysql_connection.hpp"
#include <wx/wx.h>
#include <string>
#include <iostream>

using namespace std;

DashboardFrame::DashboardFrame(const wxString& title, const wxString& name, MySQLConnection& dbRef)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)), db(dbRef){
    panel = new wxPanel(this);

    wxString welcomeMessage = "Hello "+name+" !";

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    welcomeText = new wxStaticText(panel, wxID_ANY, welcomeMessage, wxPoint(50,50), wxDefaultSize);
    wxFont font = welcomeText->GetFont();
    font.SetPointSize(18);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    welcomeText->SetFont(font);
    Center();

    vbox->Add(welcomeText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 30);\
    panel->SetSizer(vbox);
}

DashboardFrame::~DashboardFrame(){

}