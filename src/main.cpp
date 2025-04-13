#include "../include/utils.hpp"
#include "../include/mysql_connection.hpp"
#include "../include/app.hpp"
#include "../include/frame.hpp"
#include <iostream>

using namespace std;

wxIMPLEMENT_APP(App);

bool App::OnInit(){
    loadEnvFile();
    MySQLConnection db;

    if(!db.connect())
        return 1;
    cout << "Programm is running!"<<endl;

    MainFrame* mainFrame = new MainFrame("Hello GUIIII");
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();
    
    return true;
}
