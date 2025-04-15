#include "../include/utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sodium.h>

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

string hashPassword(const string& password)
{
    if(!(sodium_init() == 0))
        throw runtime_error("Failed to initialize libsodium\n");
    char hash[crypto_generichash_KEYBYTES];
    if(crypto_pwhash_str(hash, password.c_str(),password.length(),
                        crypto_pwhash_OPSLIMIT_INTERACTIVE,crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
        throw runtime_error("Out of memory while hashing password\n");
    return string(hash);
}

bool verifyPassword(const string& hash, const string& password)
{
    return crypto_pwhash_str_verify(hash.c_str(), password.c_str(), password.length()) == 0;
}
