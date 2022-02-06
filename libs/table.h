#include "BTree.h"
#include "vector"

#ifndef B_TREE_CPP_DATABASE_DATA_BASE_H
#define B_TREE_CPP_DATABASE_DATA_BASE_H

// this is table implementation.
template<typename T>
class table{
public:
    using COLUMN_TYPE = pair<string,int>;

    table(string basicString, vector<COLUMN_TYPE> vector);

    vector<BTree<T>*> btrees;
    void create(string &name, const COLUMN_TYPE& columns);
    void insert(const vector<string>& fields);
};



#endif //B_TREE_CPP_DATABASE_DATA_BASE_H
