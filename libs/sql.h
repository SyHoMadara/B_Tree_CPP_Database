#ifndef B_TREE_CPP_DATABASE_SQL_H
#define B_TREE_CPP_DATABASE_SQL_H


#include <string>
#include "vector"
#include "data_base.h"
#include <sstream>

using namespace std;

using NODE_HASH_TYPE=pair<long long, int>;
class sql {
protected:
    explicit sql();

public:
//    static sql* SQL;
//    static sql& get_sql();
    const vector<data_base> dbs;
    vector<string> commands;

    static vector<string> tokenize(string &str);

    pair<int, string> *find_command(string &command);

    void command_handler(string command);

    static vector<pair<long long int, int>> extract_parameters(const string &par);

    void remove(const string &command);

    void create(const string &command);

    void update(const string &command);

    void insert(const string &command);

    void select(const string &command);

    static NODE_HASH_TYPE hash_code(const string &s1, const string &s2);

    string conlong2str(long long int a);

    static long long int constr2long(string s);

    string contime2str(long long int a);

    static long long int constr2time(string s);
};


#endif //B_TREE_CPP_DATABASE_SQL_H
