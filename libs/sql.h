#ifndef B_TREE_CPP_DATABASE_SQL_H
#define B_TREE_CPP_DATABASE_SQL_H


#include <string>
#include "vector"
#include <sstream>

using namespace std;

class sql {
    const vector<string> commands = {"CREATE", "DELETE", "UPDATE", "INSERT", "SElECT"};
    vector<string> tokenize(string &str);
    pair<int, vector<string>>* findCommand(string command);

};


#endif //B_TREE_CPP_DATABASE_SQL_H
