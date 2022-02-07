#include "bits/stdc++.h"
using namespace std;
// this is table implementation.
template<typename T>
class BTree;
class sql;
template<typename T>
class Node;
template<typename T>
class table {
public:
    using COLUMN_TYPE = pair<string, int>;
    string name;
    priority_queue<int, vector<int>, greater<>> id_queue;
    BTree<T> *id_bTree;
    int counter = 0;
    const static short int NUMBER_OF_CHILDES = 5; // In love Hamkari
    table(const string &name, const vector<COLUMN_TYPE> &columns);

    vector<BTree<T> *> btrees;

    void insert(const vector<string> &fields);

    vector<string> select(vector<string> &fields, string &condition);

    void remove(string &condition);

    void update(const vector<string> &fields, string &condition);

    void create(string table_name, const vector<COLUMN_TYPE> &columns);
};


template<typename T>
void table<T>::create(string table_name, const vector<COLUMN_TYPE> &columns) {
    this->name = table_name;
    BTree<T> id_btree(NUMBER_OF_CHILDES, "id", "int");
    this->id_bTree = &id_btree;
    btrees.push_back(id_bTree);

    for (const auto &column: columns) {
        string type;
        if(column.second==0) type = "int";
        if(column.second==1) type = "string";
        if(column.second==2) type = "time";

        BTree<T> bTree(NUMBER_OF_CHILDES, column.first, type);
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

template<typename T>
vector<string> table<T>::select(vector<string> &fields, string &condition) {
    auto con = sql::split(condition, '=');
    BTree<T> *bTree;
    for(table<T> &t: btrees){
        if(t.name==con[0]) {
            bTree = &t;
            break;
        }
    }
    Node<T> *node = bTree->search(sql::hash_code(con[1], bTree->type)), *id_node;
    while(node->self->name!="id") node = node->nextField;
    vector<string> result;
    id_node = node;
    node = node->nextField;
    for(string field: fields){
        while(node->self->name!=field) node = node->nextField;
        result.push_back(sql::hash_inverse(node->data, node->self->name));
        node = id_node->nextField;
    }
//    for(auto& r: result) cout << r << " ";
//    cout << '\n';
    return result;

}

template<typename T>
void table<T>::remove(string &condition) {
    auto con = sql::split(condition, '=');
    BTree<T> *bTree;
    for(table<T> &t: btrees){
        if(t.name==con[0]) {
            bTree = &t;
            break;
        }
    }
    Node<T> *node = bTree->search(sql::hash_code(con[1], bTree->type)), *id_node;
    while(node->self->name!="id") node = node->nextField;
    id_node = node;
    node = node->nextField;
    BTree<T>* bt1;
    Node<T>* nn = id_node->nextField, *next;
    next = nn->nextField;
    while(nn!=id_node){
        for(BTree<T> &bt: btrees){
            if(nn->self->name==bt.name){
                bt1 = &bt;
                break;
            }
        }
        bt1->Delete(nn->data);
        nn = next;
        next = nn->nextField;
    }
    for(BTree<T> &bt: btrees){
        if(id_node->self->name==bt.name){
            bt1 = &bt;
            break;
        }
    }
    int iid = id_node->data;
    bt1->Delete(id_node->data);
    id_queue.push(iid);

}

template<typename T>
void table<T>::update(const vector<string> &fields, string &condition) {
    vector<string> fields_name;
    for(auto *bt: btrees){
        fields_name.push_back(bt->name);
    }
    auto p = select(fields_name, condition);
    remove(condition);
    insert(fields);
}



template <typename T>
class BTNode;
template< typename T >class Node{
public:
    T data;
    Node<T>* nextField;
    BTNode<long long int> *self;
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
    string type;
    BTree(int M, const string& name, string type);
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
        while ( 0 <=i  && h->a[i].data > k){
            h->a[i+1].data = h->a[i].data;
            i--;
        }
        h->a[i+1].data = k;
        h->Num ++;
        h->a[i+1] = h->a[i+1] ;
        return &h->a[i+1] ;
    }
    else{
        while (i >= 0 && h->a[i].data > k) i--;
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
        return &root->a[0] ;
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







using NODE_HASH_TYPE = pair<long long, int>;

class sql {

public:
    sql();

//    static sql* SQL;
//    static sql& get_sql();
    vector<table<long long>*> tables;
    vector<string> commands;

    static vector<string> tokenize(string &str);

    pair<int, string> *find_command(string &command);

    void command_handler(string command);

    static vector<string> extract_parameters(const string &par);

    void remove(const string &command);

    void create(const string &command);

    void update(const string &command);

    void insert(const string &command);

    void select(const string &command);


    const int BASE_CONVERT = 26;
    const char BASE_CHARE = 'a';


    static string conlong2time(long long int a);

    static long long int contime2long(string s);

    static long long int constr2long(string s, int base_convert, char base_char);

    static string conlong2str(long long int a, int base_convert, char base_char);

    static string conlong2str(long long int a);

    static long long int constr2long(string s);

    static NODE_HASH_TYPE hash_code(const string &s2, const string &s1);

    static vector<string> split(const string &par, const char &with);

    void select_all(const string &command);

    static string hash_inverse(long long int a, const string &type);
};



sql::sql() {
    commands = {"CREATE TABLE", "DELETE FROM", "UPDATE", "INSERT INTO", "SELECT \\*", "SELECT"};
    for (auto &command : commands) command += " .+";
}

vector<string> sql::tokenize(string &str) {
    vector<string> strs;
    stringstream ss(str);
    string s;
    while (ss >> s)strs.push_back(s);
    return strs;
}

pair<int, string> *sql::find_command(string &command) {
    for (int i = 0; i < commands.size(); i++)
        if (regex_match(command, regex(commands[i])))
            return new pair<int, string>(i, command);
    return nullptr;
}

void sql::command_handler(string command) {
    // const vector<string> commands = {"CREATE", "DELETE", "UPDATE", "INSERT", "SElECT"};
    auto p = find_command(command);
    switch (p->first) {
        case 0:
            sql::create(p->second);
            break;
        case 1:
            sql::remove(p->second);
            break;
        case 2:
            sql::update(p->second);
            break;
        case 3:
            sql::insert(p->second);
            break;
        case 4:
            sql::select_all(p->second);
            break;
        case 5:
            sql::select(p->second);
            break;

    }
}

void sql::remove(const string &command) {
    // DELETE FROM {table name} WHERE {condition}
    regex r(R"(DELETE FROM (\w+) WHERE (.+))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();
    string condition = m[2];
    for(auto &t: tables){
        if(t->name == table_name){
            t->remove(condition);
            break;
        }
    }

}

void sql::create(const string &command) {
    //CREATE TABLE {table name} (column1 type,column2 type,...)
    regex first_regex(R"(CREATE TABLE (\w+) (\(.+)\))"), r(R"([\w\d/]+)");
    smatch m;
    regex_search(command, m, first_regex);
    string table_name = m[1].str();
    auto parameters = sql::extract_parameters(m[2].str());
    vector<pair<string, int>> p;
    for (string ss: parameters) {
        sregex_iterator it2(ss.begin(), ss.end(), r);
        string name = it2->str();
        p.emplace_back(name, hash_code(name, (it2++)->str()).second);
    }
    tables.push_back(new table<long long>(table_name, p));
}

void sql::update(const string &command) {
    // UPDATE employee SET ("Hamid",2022/8/7,50000) WHERE name=="Hamid"
    regex r(R"(UPDATE (\w+) SET \((.+)\) WHERE (.+))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();
    auto p = extract_parameters(m[2]);
    string condition = m[3];
    for(auto &t: tables){
        if(table_name==t->name){
            t->update(p, condition);
            break;
        }
    }

}

void sql::insert(const string &command) {
    // INSERT INTO {table name} VALUES (field1,field2,...)
    regex r(R"(INSERT INTO (\w+) VALUES (\(.+)\))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();
    auto fields = sql::extract_parameters(m[2].str());
    for(auto &t: tables){
        if(t->name == table_name){
            t->insert(fields);
            break;
        }
    }

}

void sql::select(const string &command) {
    // SELECT (column1,column2,...) FROM {table name} WHERE condition
    regex r(R"(SELECT (\(.+)\) FROM (\w+) WHERE (.+))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[2].str();
    auto columns = sql::extract_parameters(m[1].str());
//    for (auto cc: columns) cout << cc << endl;
    string condition = m[3];
    for(auto &t: tables){
        if(table_name==t->name){
            t->select(columns, condition);
        }
    }

}

void sql::select_all(const string &command) {
    // SELECT * FROM {table name} WHERE condition
    regex r(R"(SELECT \* FROM (\w+) WHERE (.+))");
    smatch m;
    regex_search(command, m, r);
    string table_name = m[1].str();
    string condition = m[2].str();
//    cout << table_name << " " << condition;

}

string sql::conlong2str(long long a, const int base_convert, const char base_char) {
    string s;
    while (a) {
        s += (char) (base_char + a % base_convert);
        a /= base_convert;
    }
    return s;
}

string sql::conlong2str(long long a) {
    return conlong2str(a, 'z' - 'a', 'a');
}


long long sql::constr2long(string s, const int base_convert, const char base_char) {
    long long a = 0;
    long long i = 1;
    for (auto it = s.begin(); it != s.end(); it++, i *= base_convert) {
        a += i * (*it - base_char);
    }
    return a;
}

long long sql::constr2long(string s) {
    return constr2long(std::move(s), 'z' - 'a', 'a');
}

string sql::conlong2time(long long a) {
    return conlong2str(a, 'z' - '/', '/');
}

long long sql::contime2long(string s) {
    return constr2long(std::move(s), 'z' - '/', '/');
}

NODE_HASH_TYPE sql::hash_code(const string &s2, const string &s1) {
    NODE_HASH_TYPE result;
    if (s2 == "int") {
        result.first = stoll(s1);
        result.second = 0;
    } else if (s2 == "string") {
        result.first = constr2long(s1);
        result.second = 1;
    } else if (s2 == "time") {
        result.first = contime2long(s1);
        result.second = 2;
    }
    return result;
}

string sql::hash_inverse(long long a, const string& type){
    if(type=="int") return to_string(a);
    if(type=="string") return conlong2str(a);
    if(type=="time") return conlong2time(a);
    return "";
}

vector<string> sql::extract_parameters(const string &par) {
    // remove parenthesis from end and begin.
    string clear_par;
    for (char it : par) {
        if (it == '(' || it == ')')continue;
        clear_par += it;
    }
    // extract parameters.
    return split(clear_par, ',');

}

vector<string> sql::split(const string &par, const char &with) {
    string wit;
    wit += with;
    string reg = "([^" + wit + "]+)";
    regex par_regex(reg);
    vector<string> result;
    for (sregex_iterator it(par.begin(), par.end(), par_regex), it_end; it != it_end; it++) {
        result.push_back(it->str());
    }
    return result;
}



//sql& sql::get_sql() {
//    if(sql::SQL == nullptr) sql::SQL = new sql();
//    return *sql::SQL;
//}

