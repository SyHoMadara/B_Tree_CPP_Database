#ifndef B_TREE_CPP_DATABASE_SQL_H
#define B_TREE_CPP_DATABASE_SQL_H


#include <string>
#include "vector"
#include "data_base.h"
#include <sstream>

using namespace std;

class sql {
public:
    const vector<data_base> dbs;
    const vector<string> commands = {"CREATE", "DELETE", "UPDATE", "INSERT", "SElECT"};
    static vector<string> tokenize(string &str);
    pair<int, vector<string>>* find_command(string &command);
    void command_handler(string command);
    void remove(vector<string> vector);
    void create(vector<string> vector);
    void update(vector<string> vector);
    void insert(vector<string> vector);
    void select(vector<string> vector);
};


#endif //B_TREE_CPP_DATABASE_SQL_H
