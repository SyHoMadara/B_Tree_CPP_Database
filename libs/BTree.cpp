#include <BTree.h>
#include <cmath>
#include <iostream>

template <typename T>
BTNode<T>::BTNode(int M, bool f,const string& name) {
    this->name = name;
    m = M;
    min = (m + 1) / 2;
    a = new Node<T>[m - 1];
    b = new BTNode *[m];
    Num = 0;
    l = f;
}

template <typename T>
bool BTNode<T>::IsFull() {
    if (Num == m - 1) return true;
    return false;
    //k;kkh
}
template <typename T>
void BTNode<T>::borrowFromPrev (int in) {
    BTNode* child=b[in];
    BTNode* sibling=b[in-1];
    for (int i = child->Num-1; i>=0; --i) child->a[i+1].data = child->a[i].data;
    if (child->l == false){
        for(int i=child->Num ; i>=0; --i) child->b[i+1] = child->b[i];
    }
    child->a[0].data = a[in-1].data;
    if(child->l == false ) child->b[0] = sibling->b[sibling->Num];
    a[in-1].data = sibling->a[sibling->Num-1].data;
    child->Num ++;
    sibling->Num --;
    return;
}
template <typename T>
void BTNode<T>::borrowFromNext(int in) {
    BTNode *child = b[in];
    BTNode *sibling=b[in+1];
    child->a[(child->Num)].data = a[in].data;
    if (child->l == false) child->b[(child->Num)+1] = sibling->b[0];
    a[in].data = sibling->a[0].data;
    for (int i=1; i<sibling->Num; ++i)
        sibling->a[i-1].data = sibling->a[i].data;
    if ( sibling->l == false) {
        for(int i=1; i<=sibling->Num; ++i) sibling->b[i-1] = sibling->b[i];
    }
    child->Num ++;
    sibling->Num --;
    return;
}
template <typename T>
void BTNode<T>::merge(int in){
    BTNode *child = b[in];
    BTNode *sibling = b[in+1];
    child->a[min-1].data = a[in].data;
    for (int i=0; i<sibling->Num; ++i) child->a[i+min].data = sibling->a[i].data;
    if (child->l == false){
        for(int i=0; i<=sibling->Num; ++i) child->b[i+min] = sibling->b[i];
    }
    for (int i=in+1; i<Num; ++i) a[i-1].data = a[i].data;
    for (int i=in + 2; i<=Num; ++i)  b[i-1] = b[i];
    child->Num += sibling->Num + 1;
    Num--;
    delete(sibling);
    return;
}
template <typename T>
void BTNode<T>::fill(int in){
    if (in != 0 && min<=b[in-1]->Num) borrowFromPrev(in);
    else if (in !=  Num && min <= b[in+1]->Num) borrowFromNext(in);
    else{
        if (in != Num)
            merge(in);
        else
            merge(in-1);
    }
    return;
}
template <typename T>
void BTNode<T>::Delnl(int in){
    int k = a[in].data;
    if (min <=  b[in]->Num ) {
        BTNode *q = b[in];
        while (q->l == false) q = q->b[q->Num];
        int pred =q->a[q->Num-1].data;
        a[in].data = pred;
        b[in]->Delete(pred);
    }
    else if  (min <= b[in+1]->Num ) {
        BTNode *q = b[in+1];
        while (q->l == false) q = q->b[0];
        int ne = q->a[0].data;
        a[in].data = ne;
        b[in+1]->Delete(ne);
    }
    else{
        merge(in);
        b[in]->Delete(k);
    }
    return;
}
template <typename T>
void BTNode<T>::Delete( T k){
    int in=0;
    while (in < Num && a[in].data < k) in++;
    if (in < Num && a[in].data == k) {
        if (l){
            for (int i=in + 1; i<Num; ++i) a[i-1].data = a[i].data;
            Num--;
            return;
        }
        else Delnl(in);
    }
    else{
        if (l) return;
        bool flag ;
        if(in == Num) flag = true ;
        else flag = false ;
        if (b[in]->Num < min) fill(in);
        if (flag && in > Num)
            b[in-1]->Delete(k);
        else
            b[in]->Delete(k);
    }
    return;
}
template <typename T>
Node<T> *BTNode<T>::search(int k) {
    int i = 0 ;
    while(i <= Num &&  a[i].data < k ) i++ ;
    if (a[i].data == k) return a[i] ;
    if( l) return NULL ;
    return b[i]->search(k) ;
}

template <typename T>
void BTNode<T>::print() {
    int i ;
    for (i = 0; i < Num ; i++){
        cout <<" "  << a[i].data;
        if (l == false) b[i]->print();



    }
    if (l == false)
        b[i]->print();
}

template <typename T>
BTree<T>::BTree(int M, const string& name, string type) {
    this->type = type;
    root = NULL;
    this->name = name;
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
Node<T>* BTree<T>:: search(T k){
    return root->search(k) ;

}
template <typename T>
BTNode<T> *BTree<T>::s(BTNode<T> *h, T k, int in, BTNode<T> *p) {
    if( h != NULL){
        if (h->l) return h ;
        int i ;
        for( i = 0 ; i <h->Num ; i++){
            if (k < h->a[i].data){
                return s(h->b[i] , k , i , h) ;
            }
        }
        return s(h->b[h->Num] , k , i , h) ;
    }
    else{
        BTNode<T> *tnode = new BTNode<T>( m , true,name);
        p->b[in] = tnode ;
        tnode->parent = p ;
        return tnode;
    }
}
template <typename T>
void BTree<T>::f(BTNode<T> * h , int x , BTNode<T> * t){
    BTNode<T> * q = new BTNode<T>( m , h->l ,name);
    q->Num = min-1 ;
    for( int i = 0 ; i < min - 1 ; i++) q->a[i].data = h->a[i+min].data;
    if (h->l == false){
        for (int i = 0; i < min ; i++) q->b[i] = h->b[i+min];
    }
    h->Num = min - 1 ;
    for (int i = t->Num; i >= x+1; i--) t->b[i+1] = t->b[i] ;
    t->b[x+1] = q;
    for (int i = t->Num; i >= x; i--) t->a[i+1].data = t->a[i].data ;
    t->a[x].data = h->a[min-1].data ;
    t->Num ++ ;
}
template <typename T>
Node<T>* BTree<T>:: insert1(BTNode<T> * h , T k){
    int i = h->Num - 1 ;
    if(h->l){
        while ( 0 <=i  && h->a[i] > k){
            h->a[i+1].data = h->a[i].data;
            i--;
        }
        h->a[i+1].data = k;
        h->Num ++;
        h->a[i+1].self=h->a[i+1] ;
        return h->a[i+1] ;
    }
    else{
        while (i >= 0 && h->a[i] > k) i--;
        if (h->b[i+1]->Num == m-1){
            f(h->b[i+1],i+1,h);
            if (h->a[i+1].data < k)i++;
        }
        insert1(h->b[i+1],k);
    }
}
template <typename T>
Node<T>* BTree<T>::insert(T k) {
    if( root == NULL ){
        //cout<<8 ;
        BTNode<T> *tnode = new BTNode<T>( m , true,name);
        root = tnode ;
        root->parent = NULL ;
        root->a[0].data = k ;
        root->Num ++ ;
        root->a[0].self = root ;
        return root->a[0] ;
    }

    else{
        //cout << 7 ;
        if( root->Num == m-1){
            BTNode<T> *t = new BTNode<T>(m, false,name);
            t->b[0] = root;
            f( root,0,t);
            int i = 0;
            if (t->a[0].data < k) i++;
            insert1( t->b[i] ,k);
            root = t;
        }
        else{
            //cout<< 6 ;
            insert1(root , k) ;
        }
        /*BTNode<T> * h = s(root, k, 0 , NULL);

            if(h->Num == 0 ){
                h->a[0] = k ;
                h->Num ++ ;
                return root ;
            }
            if(h->Num < m-1 ){
                int i = 0 ;
                while( h->a[i] < k && i<h->Num) i++;
                for( int j = h->Num - 1 ; i<=j ; j--){
                    h->a[j+1] = h->a[j] ;
                }
                h->a[i] = k ;
                h->Num ++;
                return root ;

            }
            else{
                whihe( h->Num == m-1){
                    T*
                    if(h->parent != NULL){
                    int in ;
                    for ( int i = 0 ; i <h->parent->Num ; i++){
                        if(h->parent->b[i] == h){
                            in = i ;
                            break;
                        }
                    }
                    }

                }

            }
        /*while(h != NULL ){
            if( h->Num == m-1 && h->parent != NULL && h->parent->Num < m){
                BTNode<T>* q = NULL;
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
                        for (int j = (q->Num) - 1; j >= 1; j--)
                            q->a[j + 1] = q->a[j];
                        q->a[0] = p1;
                        h->parent->a[m == 0 ? m : m - 1] = h->a[h->Num - 1];
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
                               if( in==0 || in==1){
                                   h->parent->a[0] = p1;
                                h->parent->a[1] = p2;
                                h->parent->b[0] = h;
                                h->parent->b[1] = q;
                                h->parent->b[2] = s;
                                return root;
                            }
                            else{
                                h->parent->a[in - 1] = p1;
                                   h->parent->a[in] = p2;
                                h->parent->b[in-1] = h;
                                h->parent->b[in] = q;
                                h->parent->b[in + 1] = s;
                                return root;
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
void BTree<T>::Delete(T k){
    if (root == NULL) return;
    root->Delete(k);
    if (root->Num == 0) {
        BTNode<T> *t = root;
        if (root->l)root = NULL;
        else root = root->b[0];
        delete t;
    }
    return;
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