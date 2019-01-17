//
//  main.cpp
//  Program3
//
//  Created by Brendon Malouf on 5/13/18.
//  Copyright © 2018 Brendon Malouf. All rights reserved.
//

#include <iostream>
#include "RBTree.hpp"

int main(int argc, const char * argv[]) {
    RBtree<const char> family;
    family.insert("Grandma", 10);
    family.insert("Uncle Joe", 12);
    family.insert("Dad", 8);
    family.insert("Me", 6);
    family.insert("Gary", 9);
    family.insert("Ant", 11);
    family.insert("Nick", 13);
    family.insert("Jim", 7);
    family.insert("Zoe", 14);
    cout << "Uncle Joe has a key of 12. Find him..." << endl;
    family.find(12);
    cout << "\nGrandpa has a key of 10. Find her..." << endl;
    family.find(10);
    cout << "\nI have a key of 6. Find me..." << endl;
    family.find(7);
    cout << "\nZoe has a key of 14. Find her..." << endl;
    family.find(14);
    
    if(family.mostBlack(family.getRoot(), 0) ==
       family.leastBlack(family.getRoot(), 0)){
        cout << "\nThis tree has the same amount of black nodes";
        cout << " along each path.\n";
    }
    else{
        cout << "\nThis tree does not have the same amount of black nodes";
        cout << " along each path.\n";
    }
    exit(0);
}
