#include<iostream>
//#include "libs/BTree.h"
#include "regex"
using namespace std;


int main(){
    regex r("CREATE TABLE +");
    string s = "CREATE TABLE slkdfjlksdjlf";
    cout << regex_match(s, r);
	
}