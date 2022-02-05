#ifndef B_TREE_CPP_DATABASE_SQL_H
#define B_TREE_CPP_DATABASE_SQL_H


#include <string>
#include "vector"
#include "data_base.h"
#include <sstream>

using namespace std;

class sql {
protected:
    explicit sql();
public:
//    static sql* SQL;
    static sql& get_sql();
    const vector<data_base> dbs;
    vector<string> commands;
    static vector<string> tokenize(string &str);
    pair<int, string>* find_command(string &command);
    void command_handler(string command);
    void remove(const string &command);
    void create(const string &command);
    void update(const string &command);
    void insert(const string &command);
    void select(const string &command);
};


#endif //B_TREE_CPP_DATABASE_SQL_H
