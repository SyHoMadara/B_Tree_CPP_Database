#include "table.h"
#include "BTree.h"
#include "vector"
#include "minheap.cpp"
#include "sql.h"

template<typename T>
void table<T>::create(string &table_name, const vector<COLUMN_TYPE> &columns) {
    this->name = table_name;
    BTree<T> id_btree(NUMBER_OF_CHILDES, "id", "int");
    this->id_bTree = &id_btree;
    btrees.push_back(id_btree);
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
    Node<T> *temp,*id_temp,*po;
    id_temp = id_bTree->insert(id);
    temp = id_temp;
    for(int i=0;i<fields.size();i++){
        po = btrees[i+1]->insert(sql::hash_code(fields[i], btrees[i+1]->type));
        po->nextField = temp;
        temp = po;
    }
    id_temp->nextField = po;


}

template<typename T>
table<T>::table(const string &name, const vector<COLUMN_TYPE> &columns) {
    create(name, columns);
}
