#include "table.h"
#include "BTree.h"
#include "vector"
#include "minheap.cpp"

template<typename T>
void table<T>::create(string &table_name, const vector<COLUMN_TYPE> &columns) {
    this->name = table_name;
    for (const auto &column: columns) {
        BTree<T> bTree(NUMBER_OF_CHILDES, column.first, column.second);
        btrees.push_back(&bTree);
    }
}

template<typename T>
void table<T>::insert(const vector<string> &fields) {
    int id;
    if(id_queue.empty())id = counter++;
    else {
        id = id_queue.top();
        id_queue.pop();
    }
}

template<typename T>
table<T>::table(const string &name, const vector<COLUMN_TYPE> &columns) {
    create(name, columns);
}
