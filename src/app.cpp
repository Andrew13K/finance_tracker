#include "../include/utils.hpp"
#include "../include/mysql_connection.hpp"
#include "../include/app.hpp"
#include "../include/registration_frame.hpp"
#include <iostream>

using namespace std;

bool App::OnInit(){
    loadEnvFile();
    db = new MySQLConnection();

    if(!db->connect())
        return 1;
    cout << "Programm is running!"<<endl;

    const string create_db_query ="CREATE DATABASE IF NOT EXISTS manage_spendings";
    if(db->executeQuery(create_db_query))
        cout<<"Database created successfully!"<<endl;

    if(executeSQLFromFile(*db, "queries/user/create_table.sql"))
        cout<<"User table created successfully!"<<endl; 

    if(executeSQLFromFile(*db, "queries/category/create_table.sql"))
        cout<<"Category table created successfully!"<<endl;

    if(executeSQLFromFile(*db, "queries/spendings/create_table.sql"))
        cout<<"Spendings table created successfully!"<<endl;

    if(executeSQLFromFile(*db, "queries/friendship_request/create_table.sql"))
        cout<<"Friendship table created successfully!"<<endl;

    if(executeSQLFromFile(*db, "queries/friends/create_table.sql"))
        cout<<"Friends table created successfully!"<<endl;

    if(executeSQLFromFile(*db, "queries/visibility/create_table.sql"))
        cout<<"Visibility table created successfully!"<<endl;                                     

    MainFrame* mainFrame = new MainFrame("Finance Maganer", *db);
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show(true);
    SetTopWindow(mainFrame);

    cout<<"Gui created in the center"<<endl;
    return true;
}

App::~App(){
    delete db;
}