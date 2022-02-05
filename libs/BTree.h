#include <cmath>
#include <iostream>
using namespace std;

template <typename T>
class BTree;
template <typename T>
class BTNode {
   public:
    int m;
    int min;
    T *a;
    BTNode<T> **b;
    BTNode<T> *parent;
    int Num;
    bool l;
    BTNode(int M, bool f);
    bool IsFull();
    BTNode<T> *search(int k);
    void print();
};

template <typename T>
class BTree {
   private:
    BTNode<T> *root;
    int m;
    int min;
    int flag, flag1;

   public:
    explicit BTree(int M);
    T max(T a, T b);
    BTNode<T> *s(BTNode<T> *h, T k, int in, BTNode<T> *p);
    void f(BTNode<T> * h ,int x ,BTNode<T> * t) ;
    void insert1(BTNode<T> * h , T k) ;
    void insert(T k );
    void print();

    BTNode<T> *Root();
    /*int find(BTNode<T> * h , int i);*/
};
