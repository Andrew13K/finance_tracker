#include "../include/frame.hpp"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title){
    wxPanel* panel = new wxPanel(this);
    
    wxButton* button = new wxButton(panel, wxID_ANY, "Click", wxPoint(150,50), wxSize(100,35));
    wxCheckBox* checkBox = new wxCheckBox(panel, wxID_ANY, "CheckBox", wxPoint(550,55));
    wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Some random test/text", wxPoint(120,150));
}
