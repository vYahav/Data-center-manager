
#include "AVLTree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

template<class T>
Node<T>* AVLTree<T>::RR(Node<T>* n){
    Node<T> * n2;
    n2 = n->r;
    n->r = n2->l;
    n2->l = n;
    return n2;
}
template<class T>
Node<T>* AVLTree<T>::LL(Node<T>* n){
    Node<T> * n2;
    n2 = n->l;
    n->l = n2->r;
    n2->r = n;
    return n2;
}
template<class T>
Node<T>* AVLTree<T>::LR(Node<T>* n){
    Node<T> * n2;
    n2 = n->l;
    n->l = RR(n2);
    return LL(n);
}
template<class T>
Node<T>* AVLTree<T>::RL(Node<T>* n){
    Node<T> *n2;
    n2 = n->r;
    n->r = LL(n2);
    return RR(n);
}

int max(int i, int j){
    if(i<j) return j;
    return i;
}

template<class T>
int AVLTree<T>::treeHeight(Node<T>* n) {
    int h = 0;
    if (n == NULL) return h;

    int lh = treeHeight(n->l);
    int rh = treeHeight(n->r);
    int maxh = max(lh, rh);
    h = maxh + 1;

    return h;
}

template<class T>
int AVLTree<T>::treeDiff(Node<T>* n) {
    int l_height = treeHeight(n->l);
    int r_height = treeHeight(n->r);
    int b_factor = l_height - r_height;
    return b_factor;
}


template<class T>
Node<T>* AVLTree<T>::treeBalance(Node<T>* n){

    int bal_factor = treeDiff(n);
    if (bal_factor > 1) {
        if (treeDiff(n->l) > 0)
            n = LL(n);
        else
            n = LR(n);
    } else if (bal_factor < -1) {
        if (treeDiff(n->r) > 0)
            n = RL(n);
        else
            n = RR(n);
    }
    return n;
}

template<class T>
Node<T>* AVLTree<T>::treeInsert(Node<T>* n, T newdata)
{
    if (n == NULL) {
        n = new Node<T>;
        n->data = newdata;
        n->l = NULL;
        n->r = NULL;
        return n;
    } else if (newdata< n->data) {
        n->l = treeInsert(n->l, newdata);
        n = treeBalance(n);
    } else{
        n->r = treeInsert(n->r, newdata);
        n = treeBalance(n);
    } return n;
}

template<class T>
Node<T>* AVLTree<T>::treeFind(Node<T>* n, T lookingFor)
{
    if(n==NULL) return NULL;
    if(n->data == lookingFor) return n;
    if(n->data < lookingFor) return treeFind(n->r,lookingFor);
    if(n->data > lookingFor) return treeFind(n->l,lookingFor);
    return NULL;
}

template<class T>
Node<T>* AVLTree<T>::treeDeleteNode(Node<T> *n,T deleteNode) {
    if (n == NULL) return n;
    if(n->data > deleteNode) {
        n->l= treeDeleteNode(n->l, deleteNode);

    }
    if(n->data < deleteNode){
        n->r= treeDeleteNode(n->r, deleteNode);
    }
    if(n->data == deleteNode){
        if(n->l == NULL || n->r == NULL){ //1 or less children
            Node<T> *helper = NULL;
            if(n->l == NULL)  helper = n->r;
            else helper = n->l;

            if(helper == NULL) {
                helper = n;
                n= NULL;
            }
            else{
                *n = *helper;
            }
            free(helper);
        }
        else{ //2 children
            Node<T>* temp = n->r;
            while (temp->l != NULL)
                temp = temp->l;


            n->data = temp->data;

            n->r = treeDeleteNode(n->r, temp->data);
        }

    }
    if(n!=NULL) n= treeBalance(n);
    return n;
}