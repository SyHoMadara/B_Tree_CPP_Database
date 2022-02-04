#include "sql.h"

vector<string> sql::tokenize(string &str) {
    vector<string> strs;
    stringstream ss(str);
    string s;
    while (ss >> s)strs.push_back(s);
    return strs;
}

pair<int, vector<string>> *sql::findCommand(string command) {
    vector<string> command_split = tokenize(command);
    for (int i = 0; i < commands.size(); i++)
        if (command_split[0] == commands[i])
            return new pair<int, vector<string>>(i, command_split);
    return nullptr;
}
