#include "sql.h"

vector<string> sql::tokenize(string &str) {
    vector<string> strs;
    stringstream ss(str);
    string s;
    while (ss >> s)strs.push_back(s);
    return strs;
}

pair<int, vector<string>> *sql::find_command(string &command) {
    vector<string> command_split = tokenize(command);
    for (int i = 0; i < commands.size(); i++)
        if (command_split[0] == commands[i])
            return new pair<int, vector<string>>(i, command_split);
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

void sql::remove(const vector<string>& vector) {

}

void sql::create(const vector<string>& vector) {

}

void sql::update(const vector<string>& vector) {

}

void sql::insert(const vector<string>& vector) {

}

void sql::select(const vector<string>& vector) {

}

sql::sql(){}

sql& sql::get_sql() {
    if(sql::SQL == nullptr) sql::SQL = new sql();
    return *sql::SQL;
}
