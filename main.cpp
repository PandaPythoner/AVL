#include "AVL.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <string>


#define int long long


using namespace std;


mt19937 rnd(123123);


void help(){
    cout << "\n\n";
    cout << "This is a program, in that you can play with AVL tree" << "\n";
    cout << "Made by Anton Stepanov (all rights reserved)" << "\n\n";
    cout << "Commands: " << "\n";
    cout << "insert x (inserts node with key x)" << "\n";
    cout << "find x (finds node with key x)" << "\n";
    cout << "findmin (finds node with minimal key)" << "\n";
    cout << "del x (deletes node with key x)" << "\n";
    cout << "delmin (deletes node minimal key)" << "\n";
    cout << "print (prints AVL tree)" << "\n";
    cout << "help (shows information about this program)" << "\n";
    cout << "exit (stops program)" << "\n";
    cout << "\n\n";
}


int32_t main() {
    AVL<int> a;
    for(int i = 0; i < 10; i += 1){
        a.insert(rnd() % 100 + 1);
    }
    cout << "Tree: " << "\n";
    a.print_tree_tex();
    for(int i = 0; i < 3; i += 1){
        int x = rnd() % 100 + 1;
        cout << "Adding element " << x << " :" << "\n";
        a.print_insert(x);
    }
    /*
    help();
    while(1){
        string s;
        cin >> s;
        if(s == "insert"){
            int x;
            cin >> x;
            a.insert(x);
        } else if(s == "find"){
            int x;
            cin >> x;
            auto p = a.find(x);
            if(p == nullptr){
                cout << -1 << "\n";
            } else{
                cout << p->key << "\n";
            }
        } else if(s == "findmin"){
            auto p = a.find_min();
            if(p == nullptr){
                cout << -1 << "\n";
            } else{
                cout << p->key << "\n";
            }
        } else if(s == "delmin"){
            a.delete_min();
        } else if(s == "del"){
            int x;
            cin >> x;
            a.delete_by_key(x);
        } else if(s == "print"){
            cout << a << "\n";
        } else if(s == "exit"){
            break;
        } else if(s == "help"){
            help();
        }
    }
    */
    return 0;
}
