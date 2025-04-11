#include "../include/utils.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void loadEnvFile(const string& filepath)
{
    ifstream file(filepath);
    if(!file.is_open())
    {
        cerr << "Could not open the .env file: "<<filepath<<endl;
        return;
    }

    string line;
    while(getline(file,line))
    {
        if(line.empty() || line[0] == '#') continue;

        size_t pos = line.find('=');
        if(pos == string::npos) continue;

        string key = line.substr(0,pos);
        string value = line.substr(pos+1);

        key.erase(0, key.find_first_not_of( "\t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of( "\t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        setenv(key.c_str(),value.c_str(),1);
    }
}