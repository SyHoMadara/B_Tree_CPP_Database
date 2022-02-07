#ifndef B_TREE_CPP_DATABASE_SQL_H
#define B_TREE_CPP_DATABASE_SQL_H


#include <string>
#include "vector"
#include "table.h"
#include <sstream>

using namespace std;

using NODE_HASH_TYPE = pair<long long, int>;

class sql {

public:
    sql();

//    static sql* SQL;
//    static sql& get_sql();
    vector<table<long long>> tables;
    vector<string> commands;

    static vector<string> tokenize(string &str);

    pair<int, string> *find_command(string &command);

    void command_handler(string command);

    static vector<string> extract_parameters(const string &par);

    void remove(const string &command);

    void create(const string &command);

    void update(const string &command);

    void insert(const string &command);

    void select(const string &command);


    const int BASE_CONVERT = 26;
    const char BASE_CHARE = 'a';


    string conlong2time(long long int a);

    long long int contime2long(string s);

    long long int constr2long(string s, int base_convert, char base_char);

    string conlong2str(long long int a, int base_convert, char base_char);

    string conlong2str(long long int a);

    long long int constr2long(string s);

    static NODE_HASH_TYPE hash_code(const string &s1, const string &s2);

    static vector<string> split(const string &par, const char &with);

    void select_all(const string &command);
};


#endif //B_TREE_CPP_DATABASE_SQL_H
