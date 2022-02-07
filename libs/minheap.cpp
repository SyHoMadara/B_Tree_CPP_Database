#include "iostream"

using namespace std;

class MinHeap
{
    int *heaparr;
    int maxsize;
    int size;

public:
    MinHeap(int n){
        heaparr = new int [n] ;
        maxsize = n ;
        size = 0 ;
    }

    int parent(int i) { return (i-1)/2; }

    int leftchild(int i) { return (2*i + 1); }

    int rightchild(int i) { return (2*i + 2); }


    void MinHeapify(int i ){
        int l = leftchild(i);
        int r = rightchild(i);
        int smallchild = i;
        if (l < size && heaparr[l] < heaparr[i])
            smallchild = l;
        if (r < size && heaparr[r] < heaparr[smallchild])
            smallchild = r;
        if (smallchild != i) {
            swap(heaparr[i], heaparr[smallchild]);
            MinHeapify(smallchild);
        }

    }
    void decreaseKey(int i, int key){
        if ( heaparr[i] < key) return ;
        heaparr[i] = key;
        while (0 < i   && heaparr[i] < heaparr[parent(i)] ){
            swap(heaparr[i], heaparr[parent(i)]);
            i = parent(i);
        }
    }
    void insert(int k){
        if (size == maxsize) return ;
        int i = size ;
        heaparr[i] = k;
        while (0 < i   && heaparr[i] < heaparr[parent(i)]){
            swap(heaparr[i], heaparr[parent(i)]);
            i = parent(i);
        }
        size++;
    }
    int getMin() { return heaparr[0]; }
    void deleteMin(){
        if (size < 1) return ;
        heaparr[0] = heaparr[size - 1] ;
        size -- ;
        MinHeapify(0) ;
    }
    int getSize(){ return size ;}


};