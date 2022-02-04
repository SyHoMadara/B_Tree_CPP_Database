#ifndef B_TREE_CPP_DATABASE_SQL_H
#define B_TREE_CPP_DATABASE_SQL_H


#include <string>
#include "vector"
#include "data_base.h"
#include <sstream>

using namespace std;

class sql {
private:
    explicit sql();
    static sql* SQL;
public:
    static sql& get_sql();
    const vector<data_base> dbs;
    const vector<string> commands = {"CREATE", "DELETE", "UPDATE", "INSERT", "SElECT"};
    static vector<string> tokenize(string &str);
    pair<int, vector<string>>* find_command(string &command);
    void command_handler(string command);
    void remove(const vector<string>& vector);
    void create(const vector<string>& vector);
    void update(const vector<string>& vector);
    void insert(const vector<string>& vector);
    void select(const vector<string>& vector);
};


#endif //B_TREE_CPP_DATABASE_SQL_H
