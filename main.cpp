#include<iostream>
#include "libs/BTree.h"
using namespace std;


int main(){
    BTree<int> B(4);
    B.insert(4) ;
    B.insert(2) ;
    B.insert(1) ;
    B.insert(5) ;
    B.insert(3) ;
    B.insert(6) ;
    B.print() ;
	;

	
}