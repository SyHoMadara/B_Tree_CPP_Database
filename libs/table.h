#include "BTree.h"
#include "vector"
#include "queue"
#include "minheap.cpp"

#ifndef B_TREE_CPP_DATABASE_DATA_BASE_H
#define B_TREE_CPP_DATABASE_DATA_BASE_H

// this is table implementation.
template<typename T>
class table{
public:
    using COLUMN_TYPE = pair<string,int>;
    string name;
    priority_queue<int, vector<int>, greater<>> id_queue;
    BTree<T> *id_bTree;
    int counter = 0;
    const static short int NUMBER_OF_CHILDES = 5; // In love Hamkari
    table(const string& name, const vector<COLUMN_TYPE>& columns);

    vector<BTree<T>*> btrees;
    void create(string &table_name, const vector<COLUMN_TYPE>& columns);
    void insert(const vector<string>& fields);
    void select(vector<string>& fields, const string& condition);

    void select(vector<string> &fields, string condition);
};



#endif //B_TREE_CPP_DATABASE_DATA_BASE_H
