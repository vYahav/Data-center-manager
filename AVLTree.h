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


    int treeHeight(Node<T> *);
    Node<T>* treeInsert(Node<T> *, T);
    Node<T> *RR(Node<T> *);
    Node<T> *LL(Node<T> *);
    Node<T> *LR(Node<T> *);
    Node<T> *RL(Node<T> *);
    int treeDiff(Node<T> *);
    Node<T>* treeFind(Node<T>* , T );
    Node<T> * treeBalance(Node<T> *);
};



#endif //MIVNIRATUV1_AVLTREE_H
