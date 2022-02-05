#include <regex>
#include "sql.h"


sql::sql() {
    commands = {"CREATE TABLE", "DELETE FROM", "UPDATE", "INSERT INTO", "SElECT"};
    for (auto &command : commands) command += "(.+)";
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
        if (regex_match(command, regex(commands[i])))
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
    //CREATE TABLE {table name} (column1 type,column2 type,...)


}

void sql::update(const string &command) {

}

void sql::insert(const string &command) {

}

void sql::select(const string &command) {

}

string sql::conlong2str(long long a){

}

long long sql::constr2long(string s){

}

string sql::contime2str(long long a){

}

long long sql::constr2time(string s){

}

NODE_HASH_TYPE sql::hash_code(const string& s1, const string& s2){
    NODE_HASH_TYPE result;
    if(s2=="int"){
        result.first = stoi(s1);
        result.second = 0;
    } else if(s2=="string"){
        result.first = constr2long(s1);
        result.second = 1;
    } else if(s2=="time"){
        result.first = constr2time(s1);
        result.second = 2;
    }
    return result;
}

vector<NODE_HASH_TYPE> sql::extract_parameters(const string &par) {
    string clear_par;
    regex par_regex(R"([\w\d]+ [\w]+)"), r(R"([\w\d]+)");
    for (auto it = par.begin() + 1; it != par.end() - 1; it++)
        clear_par += *it;
    vector<NODE_HASH_TYPE> result;
    for(sregex_iterator it(clear_par.begin(), clear_par.end(), par_regex), it_end; it!=it_end; it++){
        string ss = it->str();
        sregex_iterator it2(ss.begin(), ss.end(), r);
        result.push_back(hash_code(it->str(), (++it)->str()));
    }
    return result;
}




//sql& sql::get_sql() {
//    if(sql::SQL == nullptr) sql::SQL = new sql();
//    return *sql::SQL;
//}

