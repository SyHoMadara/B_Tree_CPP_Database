#include <regex>
#include <utility>
#include "iostream"
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
    regex first_regex(R"(CREATE TABLE (\w+) (\(.+)\))"), r(R"([\w\d/]+)");
    smatch m;
    regex_search(command, m, first_regex);
    string table_name = m[1].str();
    auto parameters = sql::extract_parameters(m[2].str());

//    sregex_iterator it2(ss.begin(), ss.end(), first_regex);
//    result.push_back(hash_code(it2->str(), (it2++)->str()));
    vector<NODE_HASH_TYPE> p;
    for(string ss: parameters){
        cout << ss << '\n';
        sregex_iterator it2(ss.begin(), ss.end(), r);
        p.push_back(hash_code(it2->str(), (it2++)->str()));
    }
    for(auto itit: p){
        cout << itit.first << " " << itit.second << endl;
    }

}

void sql::update(const string &command) {

}

void sql::insert(const string &command) {
    // INSERT INTO {table name} VALUES (field1,field2,...)
    regex r(R"(INSERT INTO (\w+) VALUES (\(.+)\))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();
    auto parameters = sql::extract_parameters(m[2].str());

}

void sql::select(const string &command) {

}


string sql::conlong2str(long long a, const int base_convert, const char base_char) {
    string s;
    while (a) {
        s += (char) (base_char + a % base_convert);
        a /= base_convert;
    }
    return s;
}

string sql::conlong2str(long long a) {
    return conlong2str(a, 'z' - 'a', 'a');
}


long long sql::constr2long(string s, const int base_convert, const char base_char) {
    long long a = 0;
    long long i = 1;
    for (auto it = s.begin(); it != s.end(); it++, i *= base_convert) {
        a += i * (*it - base_char);
    }
    return a;
}

long long sql::constr2long(string s) {
    return constr2long(s, 'z' - 'a', 'a');
}

string sql::conlong2time(long long a) {
    return conlong2str(a, 'z' - '/', '/');
}

long long sql::contime2long(string s) {
    return constr2long(std::move(s), 'z' - '/', '/');
}

NODE_HASH_TYPE sql::hash_code(const string &s2, const string &s1) {
    NODE_HASH_TYPE result;
    if (s2 == "int") {
        result.first = stoll(s1);
        result.second = 0;
    } else if (s2 == "string") {
        result.first = constr2long(s1);
        result.second = 1;
    } else if (s2 == "time") {
        result.first = contime2long(s1);
        result.second = 2;
    }
    return result;
}

vector<string> sql::extract_parameters(const string &par) {
    // remove parenthesis from end and begin.
    string clear_par;
    regex par_regex(R"([\w/\d ]+)");
    for (char it : par) {
        if (it == '(' || it == ')')continue;
        clear_par += it;
    }
    // extract parameters.
    vector<string> result;
    for (sregex_iterator it(clear_par.begin(), clear_par.end(), par_regex), it_end; it != it_end; it++) {
        result.push_back(it->str());
    }
    return result;
}




//sql& sql::get_sql() {
//    if(sql::SQL == nullptr) sql::SQL = new sql();
//    return *sql::SQL;
//}

