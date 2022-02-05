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

    static vector<string> extract_parameters(const string &par);

    static void remove(const string &command);

    static void create(const string &command);

    static void update(const string &command);

    static void insert(const string &command);

    static void select(const string &command);



    static const int BASE_CONVERT = 26;
    static const char BASE_CHARE = 'a';




    static string conlong2time(long long int a);

    static long long int contime2long(string s);

    static long long int constr2long(string s, int base_convert, char base_char);

    static string conlong2str(long long int a, int base_convert, char base_char);

    static string conlong2str(long long int a);

    static long long int constr2long(string s);

    static NODE_HASH_TYPE hash_code(const string& s1, const string& s2);

    static vector<string> split(const string &par, const char &with);

    static void select_all(const string& command);
};


#endif //B_TREE_CPP_DATABASE_SQL_H
