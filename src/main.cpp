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

    string create_db_query ="CREATE DATABASE IF NOT EXISTS manage_spendings";

    string create_user_table_query = "CREATE TABLE IF NOT EXISTS User("
                                "id INT NOT NULL AUTO_INCREMENT,"
                                "nickname VARCHAR(255) NOT NULL UNIQUE,"
                                "name VARCHAR(255) NOT NULL,"
                                "password VARCHAR(255) NOT NULL,"
                                "email VARCHAR(255) NOT NULL UNIQUE,"
                                "PRIMARY KEY (id))";
    
    string create_category_table_query = "CREATE TABLE IF NOT EXISTS Category("
                                "id INT NOT NULL AUTO_INCREMENT,"
                                "name VARCHAR(30) UNIQUE NOT NULL,"
                                "PRIMARY KEY (id))";
                                
    string create_spendings_table_query = "CREATE TABLE IF NOT EXISTS Spendings("
                                "id INT NOT NULL AUTO_INCREMENT,"
                                "date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                                "category_id INT NOT NULL,"
                                "user_id INT NOT NULL,"
                                "amount DECIMAL(15,2) NOT NULL,"
                                "description TEXT,"
                                "PRIMARY KEY (id),"
                                "FOREIGN KEY (category_id) REFERENCES Category(id) ON DELETE RESTRICT,"
                                "FOREIGN KEY (user_id) REFERENCES User(id) ON DELETE CASCADE,"
                                "CHECK (amount > 0))";
                                
    string create_friendship_request_table_query = "CREATE TABLE IF NOT EXISTS Friendship_Request("
                                                    "id INT NOT NULL AUTO_INCREMENT,"
                                                    "date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                                                    "sender_id INT NOT NULL,"
                                                    "receiver_id INT NOT NULL,"
                                                    "status ENUM('pending', 'accepted', 'rejected') NOT NULL DEFAULT 'pending',"
                                                    "PRIMARY KEY (id),"
                                                    "FOREIGN KEY (sender_id) REFERENCES User(id) ON DELETE CASCADE,"
                                                    "FOREIGN KEY (receiver_id) REFERENCES User(id) ON DELETE CASCADE)";
    
    string create_friends_table_query = "CREATE TABLE IF NOT EXISTS Friends("
                                        "friend_id INT NOT NULL,"
                                        "user_id INT NOT NULL,"
                                        "PRIMARY KEY (user_id, friend_id),"
                                        "FOREIGN KEY (friend_id) REFERENCES User(id) ON DELETE CASCADE,"
                                        "FOREIGN KEY (user_id) REFERENCES User(id) ON DELETE CASCADE)"; 

    string create_visibility_table_query = "CREATE TABLE IF NOT EXISTS Visibility("
                                            "friend_id INT NOT NULL,"
                                            "user_id INT NOT NULL,"
                                            "is_visible BOOLEAN DEFAULT FALSE,"
                                            "PRIMARY KEY (user_id, friend_id),"
                                            "FOREIGN KEY (friend_id) REFERENCES User(id) ON DELETE CASCADE,"
                                            "FOREIGN KEY (user_id) REFERENCES User(id) ON DELETE CASCADE)";                                        
    
    if(db.executeQuery(create_db_query))
        cout<<"Database created successfully!"<<endl;
    
    if(db.executeQuery(create_user_table_query))
        cout<<"User table created successfully!"<<endl;

    if(db.executeQuery(create_category_table_query))
        cout<<"User table created successfully!"<<endl;
    
    if(db.executeQuery(create_spendings_table_query))
        cout<<"User table created successfully!"<<endl;

    if(db.executeQuery(create_friendship_request_table_query))
        cout<<"User table created successfully!"<<endl;

    if(db.executeQuery(create_friends_table_query))
        cout<<"User table created successfully!"<<endl;

    if(db.executeQuery(create_visibility_table_query))
        cout<<"User table created successfully!"<<endl;



    MainFrame* mainFrame = new MainFrame("Finance Maganer", db);
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();
    
    return true;
}

