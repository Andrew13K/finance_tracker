#include "../include/frame_dashboard.hpp"
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

    welcomeText = new wxStaticText(panel, wxID_ANY, welcomeMessage);
    wxFont font = welcomeText->GetFont();
    font.SetPointSize(18);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    welcomeText->SetFont(font);

    vbox->Add(welcomeText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 30);

    vbox->AddStretchSpacer(1);

    wxPanel* navPanel = new wxPanel(panel, wxID_ANY);
    navPanel->SetBackgroundColour(wxColour(240, 240, 240)); // light gray bg like Telegram
    
    // Add a border line on top
    navPanel->SetBackgroundStyle(wxBG_STYLE_PAINT);
    navPanel->Bind(wxEVT_PAINT, [](wxPaintEvent& evt) {
        wxPaintDC dc(static_cast<wxPanel*>(evt.GetEventObject()));
        wxSize size = dc.GetSize();
        dc.SetPen(wxPen(wxColour(200, 200, 200))); // Light gray line
        dc.DrawLine(0, 0, size.GetWidth(), 0); // top border
    });
    
    wxBoxSizer* navSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxButton* btnProfile = new wxButton(navPanel, wxID_ANY, "Profile");
    wxButton* btnHistory = new wxButton(navPanel, wxID_ANY, "History");
    wxButton* btnFriends = new wxButton(navPanel, wxID_ANY, "Friends");
    
    // Stretch evenly between buttons - using proportion 1 for each button
    navSizer->Add(btnProfile, 1, wxEXPAND | wxALL, 5);
    navSizer->Add(new wxStaticLine(navPanel, wxID_ANY, wxDefaultPosition, wxSize(1, -1), wxLI_VERTICAL), 
                 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    navSizer->Add(btnHistory, 1, wxEXPAND | wxALL, 5);
    navSizer->Add(new wxStaticLine(navPanel, wxID_ANY, wxDefaultPosition, wxSize(1, -1), wxLI_VERTICAL), 
                 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    navSizer->Add(btnFriends, 1, wxEXPAND | wxALL, 5);
    
    navPanel->SetSizer(navSizer);
    
    // Add the nav panel with wxEXPAND flag to stretch it horizontally
    vbox->Add(navPanel, 0, wxEXPAND);
    
    panel->SetSizer(vbox);
    
    Center();
    this->Bind(wxEVT_CLOSE_WINDOW, &DashboardFrame::OnClose, this);
}

void DashboardFrame::OnClose(wxCloseEvent& evt) {
    Destroy();
    wxTheApp->ExitMainLoop();
}

DashboardFrame::~DashboardFrame(){

}