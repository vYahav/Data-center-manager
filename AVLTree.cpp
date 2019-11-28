
#include "AVLTree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
Node<T>* AVLTree<T>::treeInsert(Node<T>*, int)
{

}
template<class T>
Node<T>* AVLTree<T>::AVLTree<T>::RR(Node<T>*){

}
template<class T>
Node<T>* AVLTree<T>::LL(Node<T>*){

}
template<class T>
Node<T>* AVLTree<T>::LR(Node<T>*){

}
template<class T>
Node<T>* AVLTree<T>::RL(Node<T>*){

}
template<class T>
Node<T>* AVLTree<T>::treeBalance(Node<T>*){

}
template<class T>
void AVLTree<T>::show(Node<T>*, int){

}
template<class T>
void AVLTree<T>::inorder(Node<T>*){

}