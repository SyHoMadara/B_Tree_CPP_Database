#include <regex>
#include <utility>
#include "iostream"
#include "sql.h"


sql::sql() {
    commands = {"CREATE TABLE", "DELETE FROM", "UPDATE", "INSERT INTO", "SELECT \\*", "SELECT"};
    for (auto &command : commands) command += " .+";
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
            sql::select_all(p->second);
            break;
        case 5:
            sql::select(p->second);
            break;

    }
}

void sql::remove(const string &command) {
    // DELETE FROM {table name} WHERE {condition}
    regex r(R"(DELETE FROM (\w+) WHERE (.+))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();
    // TODO not complete condition most extract

}

void sql::create(const string &command) {
    //CREATE TABLE {table name} (column1 type,column2 type,...)
    regex first_regex(R"(CREATE TABLE (\w+) (\(.+)\))"), r(R"([\w\d/]+)");
    smatch m;
    regex_search(command, m, first_regex);
    string table_name = m[1].str();
    auto parameters = sql::extract_parameters(m[2].str());
    vector<pair<string, int>> p;
    for (string ss: parameters) {
        sregex_iterator it2(ss.begin(), ss.end(), r);
        string name = it2->str();
        p.emplace_back(name, hash_code(name, (it2++)->str()).second);
    }
    tables.emplace_back(table_name, p);
}

void sql::update(const string &command) {
    // UPDATE employee SET ("Hamid",2022/8/7,50000) WHERE name=="Hamid"
    regex r(R"(UPDATE (\w+) SET \((.+)\) WHERE (.+))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();

}

void sql::insert(const string &command) {
    // INSERT INTO {table name} VALUES (field1,field2,...)
    regex r(R"(INSERT INTO (\w+) VALUES (\(.+)\))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();
    auto fields = sql::extract_parameters(m[2].str());
    for(auto &t: tables){
        if(t.name == table_name){
            t.insert(fields);
            break;
        }
    }

}

void sql::select(const string &command) {
    // SELECT (column1,column2,...) FROM {table name} WHERE condition
    regex r(R"(SELECT (\(.+)\) FROM (\w+) WHERE (.+))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[2].str();
    auto columns = sql::extract_parameters(m[1].str());
//    for (auto cc: columns) cout << cc << endl;
    string condition = m[3];
    for(auto &t: tables){
        if(table_name==t.name){
            t.select(columns, condition);
        }
    }

}

void sql::select_all(const string &command) {
    // SELECT * FROM {table name} WHERE condition
    regex r(R"(SELECT \* FROM (\w+) WHERE (.+))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();
    string condition = m[2].str();
//    cout << table_name << " " << condition;

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
    return constr2long(std::move(s), 'z' - 'a', 'a');
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

string sql::hash_inverse(long long a, const string& type){
    if(type=="int") return to_string(a);
    if(type=="string") return conlong2str(a);
    if(type=="time") return conlong2time(a);
}

vector<string> sql::extract_parameters(const string &par) {
    // remove parenthesis from end and begin.
    string clear_par;
    for (char it : par) {
        if (it == '(' || it == ')')continue;
        clear_par += it;
    }
    // extract parameters.
    return split(clear_par, ',');

}

vector<string> sql::split(const string &par, const char &with) {
    string wit;
    wit += with;
    string reg = "([^" + wit + "]+)";
    regex par_regex(reg);
    vector<string> result;
    for (sregex_iterator it(par.begin(), par.end(), par_regex), it_end; it != it_end; it++) {
        result.push_back(it->str());
    }
    return result;
}



//sql& sql::get_sql() {
//    if(sql::SQL == nullptr) sql::SQL = new sql();
//    return *sql::SQL;
//}

