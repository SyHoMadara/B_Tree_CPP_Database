#include <cmath>
#include <iostream>
using namespace std;

template <typename T>
class BTree;
template <typename T>
class BTNode {
   public:
    int m;
    int minc{};
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
    int minc;
    int flag, flag1;

   public:
    explicit BTree(int M);
    T max(T a, T b);
    BTNode<T> *s(BTNode<T> *h, T k, int in, BTNode<T> *p);

    BTNode<T> *insert(T k);
    void print();

    BTNode<T> *Root();
    /*int find(BTNode<T> * h , int i);*/
};
