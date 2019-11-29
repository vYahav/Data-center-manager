//
// Created by Yahav on 11/27/2019.
//

#ifndef MIVNIRATUV1_DATACENTERMANAGER_H
#define MIVNIRATUV1_DATACENTERMANAGER_H
#include "library1.h"
//============================================================================================
//=========================    Stack Class    ================================================
class Stack{
public:
    int topNum;
    int* a; // Maximum size of Stack

    Stack(int stackSize) {
        topNum = -1;
        a=new int[stackSize];
    }
    bool push(int x);
    int pop();
    int top();
    bool isEmpty();

};
//============================================================================================
//=========================    AVL Tree Class    =============================================
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
    Node<T>* treeInsert(Node<T>*, T);
    Node<T> *RR(Node<T> *);
    Node<T> *LL(Node<T> *);
    Node<T> *LR(Node<T> *);
    Node<T> *RL(Node<T> *);
    int treeDiff(Node<T> *);
    Node<T>* treeFind(Node<T>* , T );
    Node<T> * treeBalance(Node<T> *);
    Node<T>* treeDeleteNode(Node<T> *,T);

};



//============================================================================================
//=========================    DataCenterManager Class    ====================================



struct Server{
    int opSystem; //Linux=0 , Windows=1.   Default=0.
    bool inUse; //True= server is currently in use , False= server is free to use.   Default=False.
};
struct DataCenter {
    int dataCenterID;
    int numOfServers;
    Server* servers;
};

class DataCenterManager {
public:
    Node<DataCenter>* root;
    StatusType AddDataCenter(int dataCenterID, int numOfServers);

    StatusType RemoveDataCenter(int dataCenterID);

    StatusType RequestServer(int dataCenterID, int serverID, int os, int *assignedID);

    StatusType FreeServer(int dataCenterID, int serverID);

    StatusType GetDataCentersByOS(int os, int **dataCenters, int* numOfDataCenters);

    void Quit();

};
bool operator< (const DataCenter& x,const DataCenter& y);
bool operator> (const DataCenter& x,const DataCenter& y);
bool operator== (const DataCenter& x,const DataCenter& y);


#endif //MIVNIRATUV1_DATACENTERMANAGER_H
