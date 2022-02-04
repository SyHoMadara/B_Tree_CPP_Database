#include <BTree.h>

#include <cmath>
#include <iostream>

template <typename T>
BTNode<T>::BTNode(int M, bool f) {
    m = M;
    min = (m + 1) / 2;
    a = new int[m - 1];
    b = new BTNode *[m];
    Num = 0;
    l = f;
}

template <typename T>
bool BTNode<T>::IsFull() {
    if (Num == m - 2) return true;
    return false;
}

template <typename T>
BTNode<T> *BTNode<T>::search(int k) {
    int i = 0;
    while (i <= Num && a[i] < k) i++;
    if (a[i] == k) return this;
    if (l) return NULL;
    return b[i]->search(k);
}

template <typename T>
void BTNode<T>::print() {
    for (int i = 0; i < num; i++) {
        if (l == false)
            b[i]->print();
        cout << " " << a[i];
    }
    if (l == false)
        b[i]->print();
}

template <typename T>
BTree<T>::BTree(int M) {
    root = NULL;
    m = M;
    min = (m + 1) / 2;
    flag = 1;
    flag1 = 1;
}
template <typename T>
T BTree<T>::max(T a, T b) {
    if (a <= b) return b;
    return a;
}
template <typename T>
BTNode<T> *BTree<T>::s(BTNode<T> *h, T k, int in, BTNode<T> *p) {
    if (h != NULL) {
        if (h->l) return h;
        for (int i = 0; i < h->num; i++) {
            if (k < h->a[i]) {
                return s(h->b[i], k);
            }
        }
        return s(h->b[h->num], k);
    } else {
        BTNode<T> *tnode = new BTNode<T>(m, true);
        p->b[in] = tnode;
        tnode->parent = p;
        return tnode;
    }
}
template <typename T>
BTNode<T> *BTree<T>::insert(T k) {
    if (root == NULL) {
        BTNode<T> *tnode = new BTNode<T>(m, true);
        r = tnode;
        r->parent = NULL;
        r->a[0] = k;
        r->Num++;
        return r;
    } else {
        if (root->Num == m - 1) {
            BTNode<T> *tnode = new BTNode<T>(m, false);
            tnode->b[0] = root;
        }
        /*BTNode* h = s(r, k, 0 , NULL);
        while(h != NULL ){

                if(h->Num == 0 ){
                        h->a[0] = k ;
                        h->Num ++ ;
                        return r ;
                }
                if(h->Num < m-1 ){
                        int i = 0 ;
                        while( h->a[i] < k && i<h->num) i++;
                        for( int j = h->Num - 1 ; i<=j ; j--){
                                h->a[j+1] = h->a[j] ;
                        }
                        h->a[i] = k ;
                        h->Num ++;
                        return r ;

                }
                if( h->Num == m-1 && h->parent != NULL && h->parent->Num < m){
                        BTNode* q = NULL;
                        int in ;
                        for ( int i = 0 ; i <h->parent->Num ; i++){
                                if(h->parent->b[i] == h){
                                        in = i ;
                                        break;
                                }
                        }
                        if(in <m-1){
                                q = h->parent->b[in + 1] ;
                                if (q == NULL){
                                        int p1;
                if (in == 0 ) p1 = h->parent->a[0];
                else p1 = h->parent->a[in - 1];
                for (int i = (q->n) - 1; j >= 1; j--)
                q->key[j + 1] = q->key[j];
                q->key[0] = put;
                p->parent->key[m == 0 ? m : m - 1] = p->key[p->n - 1];
                                }
                                else{
                                        if(q->Num == m-1){
                                                int * merge ;
                                                merge = new int [2*m] ;
                                                int i ;
                                                for( i = 0 ; i < h->Num ; i++){
                                                        merge[i] = h->a[i] ;
                                                }
                                                merge[i+1] = k ;
                                                merge[i+2] = h->parent->a[in] ;
                                                for( int j = i+2 ; j < i + 2 + q->Num ; j++ ){
                                                        merge[j] = q->a[j-i-2] ;
                                                }
                                                BTNode<T> *s = new BTNode<T>( m , true) ;
                                                int p1 , p2 ;
                                                for (int i = 0; i < (2*m-2) / 3; i++) h->a[i] = merge[i];
                        p1 = merge[(2*m-2) / 3];
                        for (int i = (2*m-2) / 3 + 1 ; i < (4*m)/ 3; i++) q->a[i - (2*m-2) / 3 - 1 ] = merge[i];
                        p2 = merge[(4*m)/ 3];
                        for (int i = (4*m) / 3 + 1 ; i < (2*m); i++) s->a[i - (4*m) / 3 - 1 ] = merge[i];
                        if( ind==0 || ind==1){
                                h->parent->a[0] = p1;
                        h->parent->a[1] = p2;
                        h->parent->b[0] = h;
                        h->parent->b[1] = q;
                        h->parent->b[2] = s;
                        return r;
                                                }
                                                else{
                                                        h->parent->a[ind - 1] = p1;
                        h->parent->a[ind] = p2;
                        h->parent->b[ind-1] = h;
                        h->parent->b[ind] = q;
                        h->parent->b[ind + 1] = s;
                        return r;
                                                }


                                        }

                                }
                        }
                }
        h = h->parent ;
        }*/
    }
}

template <typename T>
BTNode<T> *BTree<T>::Root() {
    return root;
}

/*int find(BTNode<T> * h , int i){
            if( h == head) h->min = 1 ;
            if(h == NULL) return 0 ;
            int l  ;
            if(h->left != NULL)l = h->left->chn + 1;
            else l = 0 ;
            //cout<<h->min <<" " << i <<" " <<l <<'\n' ;
            if(i == h->min  + l ){
                    return h->weight ;
            }
            else if(i < h->min  + l) {
                    if(h->left != NULL){
                            h->left->min = h->min ;
                    }
                    find(h->left , i) ;
            }
            else{
                    if(h->right != NULL){
                            h->right->min = h->min + l + 1 ;
                    }
                    find(h->right , i);
            }
    }

    void print(){
            Tnode<T> * h =head ;
            while( h != NULL){
                    cout << h->weight <<" " <<h->chn<<"\n";
                    h = h->left ;
            }
    }*/