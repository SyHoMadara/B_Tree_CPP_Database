#include <cmath>
#include <iostream>
using namespace std;
template <typename T>
class BTNode;
template< typename T >class Node{
public:
    T data;
    Node<T>* nextField;
    BTNode<T>* self;
};

template <typename T>
class BTree;
template <typename T>
class BTNode {
   public:
    int m;
    int min;
    string name ;
    Node<T> *a;
    BTNode<T> **b;
    BTNode<T> *parent;
    int Num;
    bool l;
    BTNode(int M, bool f ,const string& name);
    bool IsFull();
    Node<T> *search(int k);
    void borrowFromPrev (int in)  ;
    void borrowFromNext(int in) ;
    void merge(int in);
    void fill(int in) ;
    void Delnl(int in);
    void Delete( T k) ;
    void print();
};

template <typename T>
class BTree {
   private:
    BTNode<T> * root ;
    int m;
    int min;
    int flag, flag1;

   public:
    string name;
    explicit BTree(int M, const string& name);
    T max(T a, T b);
    Node<T>* search(T k) ;
    BTNode<T> *s(BTNode<T> *h, T k, int in, BTNode<T> *p);
    void f(BTNode<T> * h ,int x ,BTNode<T> * t) ;
    Node<T>* insert1(BTNode<T> * h , T k) ;
    Node<T>* insert(T k );
    void Delete(T k) ;
    void print();


    BTNode<T> *Root();
    /*int find(BTNode<T> * h , int i);*/
};
