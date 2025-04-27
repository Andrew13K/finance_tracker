#include "../include/frame_dashboard.hpp"
#include "../include/mysql_connection.hpp"
#include "../include/frame_start.hpp"
#include <wx/wx.h>
#include <string>
#include <iostream>

using namespace std;

DashboardFrame::DashboardFrame(const wxString& title, const wxString& name, MySQLConnection& dbRef)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)), db(dbRef){
    
    panel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    contentPanel = new wxPanel(panel, wxID_ANY);
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);
    contentPanel->SetSizer(contentSizer);

    wxStaticText* welcomeText = new wxStaticText(contentPanel, wxID_ANY, "Hello " + name + "!");
    wxFont font = welcomeText->GetFont();
    font.SetPointSize(18);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    welcomeText->SetFont(font);
    contentSizer->Add(welcomeText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 30);

    vbox->Add(contentPanel, 1, wxEXPAND);

    wxPanel* navPanel = new wxPanel(panel, wxID_ANY);
    navPanel->SetBackgroundColour(wxColour(240, 240, 240));
    
    navPanel->SetBackgroundStyle(wxBG_STYLE_PAINT);
    navPanel->Bind(wxEVT_PAINT, [](wxPaintEvent& evt) {
        wxPaintDC dc(static_cast<wxPanel*>(evt.GetEventObject()));
        wxSize size = dc.GetSize();
        dc.SetPen(wxPen(wxColour(200, 200, 200)));
        dc.DrawLine(0, 0, size.GetWidth(), 0);
    });
    
    wxBoxSizer* navSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxButton* btnProfile = new wxButton(navPanel, 1001, "Profile");
    wxButton* btnHistory = new wxButton(navPanel, 1002, "History");
    wxButton* btnFriends = new wxButton(navPanel, 1003, "Friends");
    
    navSizer->Add(btnProfile, 1, wxEXPAND | wxALL, 5);
    navSizer->Add(new wxStaticLine(navPanel, wxID_ANY, wxDefaultPosition, wxSize(1, -1), wxLI_VERTICAL), 
                 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    navSizer->Add(btnHistory, 1, wxEXPAND | wxALL, 5);
    navSizer->Add(new wxStaticLine(navPanel, wxID_ANY, wxDefaultPosition, wxSize(1, -1), wxLI_VERTICAL), 
                 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    navSizer->Add(btnFriends, 1, wxEXPAND | wxALL, 5);
    
    navPanel->SetSizer(navSizer);
    
    vbox->Add(navPanel, 0, wxEXPAND);
    
    panel->SetSizer(vbox);
    Center();

    btnProfile->Bind(wxEVT_BUTTON, &DashboardFrame::OnProfileClicked, this);
    btnHistory->Bind(wxEVT_BUTTON, &DashboardFrame::OnHistoryClicked, this);
    btnFriends->Bind(wxEVT_BUTTON, &DashboardFrame::OnFriendsClicked, this);

    this->Bind(wxEVT_CLOSE_WINDOW, &DashboardFrame::OnClose, this);
}

void DashboardFrame::OnClose(wxCloseEvent& evt) {
    Destroy();
    wxTheApp->ExitMainLoop();
}

DashboardFrame::~DashboardFrame(){}

void DashboardFrame::OnProfileClicked(wxCommandEvent& event) {
    wxBoxSizer* sizer = (wxBoxSizer*)contentPanel->GetSizer();
    sizer->Clear(true);

    wxStaticText* txt = new wxStaticText(contentPanel, wxID_ANY, "Profile View");
    sizer->Add(txt, 0, wxALIGN_CENTER | wxTOP, 20);

    wxButton* btnLogout = new wxButton(contentPanel, wxID_ANY, "Logout");
    sizer->Add(btnLogout, 0, wxALIGN_CENTER | wxTOP, 20);

    btnLogout->Bind(wxEVT_BUTTON, &DashboardFrame::OnLogoutClicked, this);

    sizer->Layout();
    contentPanel->Layout();
    contentPanel->Refresh();
}

void DashboardFrame::OnHistoryClicked(wxCommandEvent& event) {
    wxBoxSizer* sizer = (wxBoxSizer*)contentPanel->GetSizer();
    sizer->Clear(true);

    wxStaticText* txt = new wxStaticText(contentPanel, wxID_ANY, "Transaction History");
    sizer->Add(txt, 0, wxALIGN_CENTER | wxTOP, 20);

    sizer->Layout();
    contentPanel->Layout();
    contentPanel->Refresh();
}

void DashboardFrame::OnFriendsClicked(wxCommandEvent& event) {
    wxBoxSizer* sizer = (wxBoxSizer*)contentPanel->GetSizer();
    sizer->Clear(true);
    
    wxStaticText* txt = new wxStaticText(contentPanel, wxID_ANY, "Friends List");
    sizer->Add(txt, 0, wxALIGN_CENTER | wxTOP, 20);

    sizer->Layout();
    contentPanel->Layout();
    contentPanel->Refresh();
}

void DashboardFrame::OnLogoutClicked(wxCommandEvent& event) {
    if (db.logout()) {
        StartFrame* startFrame = new StartFrame("Start Finance App", db);
        startFrame->Show(true);
        startFrame->Center();
        
        wxTheApp->SetTopWindow(startFrame);

        Destroy();
    }
}