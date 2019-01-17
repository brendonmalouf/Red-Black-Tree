//
//  RBTree.hpp
//  Program3
//
//  Created by Brendon Malouf on 5/13/18.
//  Copyright © 2018 Brendon Malouf. All rights reserved.
//

#ifndef RBTree_hpp
#define RBTree_hpp

#include "iostream"

using namespace std;

template <class T> class RBtree;
enum colEnum {BLACK, RED};
const char* printColor[] = {"Black", "Red"};

//-----------------------------------------------------------------------------
template <class T>
struct node{
    friend class RBtree<T>;
    int key;
    colEnum color;
    T* data;
    node* parent;
    node* left;
    node* right;
    node( T* data ): data(data){};
    ~node(){ delete data; }
    
};

//-----------------------------------------------------------------------------
template <class T>
class RBtree{
private:
    node<T>* root;
    node<T>* p;
public:
    RBtree(){
        p = nullptr;
        root = nullptr;}
    ~RBtree(){
        while(root != nullptr) delete p;
    }
    void insert( T* data, int k );
    void fixInsertion(node<T> *t);
    void rotateLeft(node<T>* c);
    void rotateRight(node<T>* c);
    void find(int k);
    int mostBlack(node<T>* n, int c);
    int leastBlack(node<T>* n, int c);
    node<T>* getRoot(){ return root; }
};

//-----------------------------------------------------------------------------
template <class T>
void RBtree<T>::
insert( T* data, int k ){
    node<T> *c, *p;
    node<T>* temp = new node<T>(data);
    temp->key = k;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->color = RED;
    c = root;
    p = nullptr;
    
    if(root == nullptr)
    {
        root = temp;
        temp->parent = nullptr;
    }
    else{
        while(c != nullptr){
            p = c;
            if(temp->key > c->key)
                c = c->right;
            else
                c = c->left;
        }
        temp->parent = p;
        if(p->key < temp->key)
            p->right = temp;
        else
            p->left = temp;
    }
    fixInsertion(temp);
}

//-----------------------------------------------------------------------------
template <class T>
void RBtree<T>::
fixInsertion(node<T>* t){
    node<T>* k;
    if(root == t){
        t->color = BLACK;
        return;
    }
    while(t->parent != nullptr && t->parent->color == 'r'){
        node<T>* m = t->parent->parent;
        if(m->left == t->parent){
            if(m->right != nullptr){
                k = m->right;
                if(k->color == RED){
                    t->parent->color = BLACK;
                    k->color = BLACK;
                    m->color = RED;
                    t = m;
                }
            }
            else{
                if(t->parent->right == t){
                    t = t->parent;
                    rotateLeft(t);
                }
                t->parent->color = BLACK;
                m->color = RED;
                rotateRight(m);
            }
        }
        else
        {
            if(m->left != nullptr){
                k = m->left;
                if(k->color == RED){
                    t->parent->color = BLACK;
                    k->color = BLACK;
                    m->color = RED;
                    t = m;
                }
            }
            else{
                if(t->parent->left == t){
                    t = t->parent;
                    rotateRight(t);
                }
                t->parent->color = BLACK;
                m->color = RED;
                rotateLeft(m);
            }
        }
        root->color = BLACK;
    }
}

//-----------------------------------------------------------------------------
template <class T>
void RBtree<T>::
rotateLeft(node<T>* p){
    if(p->right == nullptr) return;
    else{
        node<T>* x = p->right;
        if(x->left != nullptr){
            p->right = x->left;
            x->left->parent = p;
        }
        else p->right = nullptr;
        if(p->parent != nullptr) x->parent = p->parent;
        if(p->parent == nullptr) root = x;
        else{
            if(p == p->parent->left) p->parent->left = x;
            else p->parent->right = x;
        }
        x->left = p;
        p->parent = x;
    }
}

//-----------------------------------------------------------------------------
template <class T>
void RBtree<T>::
rotateRight(node<T> *p){
    if(p->left == nullptr)
        return;
    else{
        node<T>* x = p->left;
        if(x->right != nullptr){
            p->left = x->right;
            x->right->parent = p;
        }
        else p->left = nullptr;
        if(p->parent != nullptr)
            x->parent = p->parent;
        if(p->parent == nullptr)
            root = x;
        else{
            if(p == p->parent->left)
                p->parent->left = x;
            else p->parent->right = x;
        }
        x->right = p;
        p->parent = x;
    }
}

//-----------------------------------------------------------------------------
template <class T>
void RBtree<T>::
find(int k){
    if(root == nullptr){
        cout<<"\nEmpty Tree\n" ;
        return;
    }
    node<T>* c = root;
    bool found = false;
    while(c != nullptr && !(found)){
        if(c->key == k) found = true;
        if(!(found))
        {
            if(c->key < k) c = c->right;
            else c = c->left;
        }
    }
    if(!(found)) cout << "\nItem Not Found.";
    else{
        cout << "\n\t Item Found: " << endl;
        cout << c->data;
        cout << "\nKey: " << c->key;
        cout << "\nColor: ";
        cout << printColor[c->color] << endl;
    }
}

//-----------------------------------------------------------------------------
//Finds the amount of black nodes in the path with the most black nodes.
template <class T>
int RBtree<T>::
mostBlack(node<T>* n, int c){
    if(n == nullptr) return c;
    if(n->color == BLACK) c++;
    
    int a = mostBlack(n->right, c);
    int b = mostBlack(n->left, c);
    
    return a > b ? a : b;
}

//-----------------------------------------------------------------------------
//Finds the amount of black nodes in the path with the least black nodes.
template <class T>
int RBtree<T>::
leastBlack(node<T>* n, int c){
    if(n == nullptr) return c;
    if(n->color == BLACK) c++;
    
    int a = leastBlack(n->right, c);
    int b = leastBlack(n->left, c);
    
    return a < b ? a : b;
}

#endif /* RBTree_hpp */
