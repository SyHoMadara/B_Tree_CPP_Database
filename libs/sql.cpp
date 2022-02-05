#include "sql.h"

sql::sql(){
    commands = {"CREATE", "DELETE", "UPDATE", "INSERT", "SElECT"};
}

vector<string> sql::tokenize(string &str) {
    vector<string> strs;
    stringstream ss(str);
    string s;
    while (ss >> s)strs.push_back(s);
    return strs;
}

pair<int, string> *sql::find_command(string &command) {
    for (int i = 0; i < commands.size(); i++)
        if (command == commands[i])
            return new pair<int, string>(i, command);
    return nullptr;
}

void sql::command_handler(string command) {
    // const vector<string> commands = {"CREATE", "DELETE", "UPDATE", "INSERT", "SElECT"};
    auto p = find_command(command);
    switch (p->first) {
        case 0:
            sql::create(p->second);
            break;
        case 1:
            sql::remove(p->second);
            break;
        case 2:
            sql::update(p->second);
            break;
        case 3:
            sql::insert(p->second);
            break;
        case 4:
            sql::select(p->second);
            break;
    }
}

void sql::remove(const string &command) {

}

void sql::create(const string &command) {

}

void sql::update(const string &command) {

}

void sql::insert(const string &command) {

}

void sql::select(const string &command) {

}


sql& sql::get_sql() {
    if(sql::SQL == nullptr) sql::SQL = new sql();
    return *sql::SQL;
}
