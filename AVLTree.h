//
// Created by Yahav on 11/28/2019.
//

#ifndef MIVNIRATUV1_AVLTREE_H
#define MIVNIRATUV1_AVLTREE_H
#include <stdio.h>
template<class T>
struct Node {
    T data;
    struct Node<T> *l;
    struct Node<T> *r;
};


template<class T>
class AVLTree {
public:
    Node<T>* root;

    AVLTree(){root= NULL;}
    int treeHeight(Node<T> *);
    Node<T> * treeInsert(Node<T> *, T, int); // tree's root, node to insert, DataCenter ID
    Node<T> *RR(Node<T> *);
    Node<T> *LL(Node<T> *);
    Node<T> *LR(Node<T> *);
    Node<T> *RL(Node<T> *);
    Node<T> * treeBalance(Node<T> *);

    void show(Node<T> *, int);
    void inorder(Node<T> *);
};



#endif //MIVNIRATUV1_AVLTREE_H
