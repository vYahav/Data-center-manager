//
// Created by Yahav on 11/27/2019.
//

#ifndef MIVNIRATUV1_DATACENTERMANAGER_H
#define MIVNIRATUV1_DATACENTERMANAGER_H
#include "library1.h"

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


struct Pair{
    int dataCenterID;
    int serverCount;
};
struct Server{
    int opSystem; //Linux=0 , Windows=1.   Default=0.
    bool inUse; //True= server is currently in use , False= server is free to use.   Default=False.
    int serverID;
};
struct DataCenter {
    int dataCenterID;
    int numOfServers;
    Node<Server>** servers;
    int * linuxFirstServerID;
    int * windowsFirstServerID;
    int * linuxLastServerID;
    int * windowsLastServerID;
    int * numOfLinuxServers;
    int * numOfWindowsServers;

};

class DataCenterManager {
public:
    Node<DataCenter>* root;
    Node<Pair>* windowsTree;
    Node<Pair>* linuxTree;
    StatusType AddDataCenter(int dataCenterID, int numOfServers);

    StatusType RemoveDataCenter(int dataCenterID);

    StatusType RequestServer(int dataCenterID, int serverID, int os, int *assignedID);

    StatusType FreeServer(int dataCenterID, int serverID);

    StatusType GetDataCentersByOS(int os, int **dataCenters, int* numOfDataCenters);

    StatusType AddToCountTree(int dataCenterID,int numOfWindows,int numOfLinux);
    StatusType RemoveFromCountTree(int dataCenterID,int oldNumOfWindows,int oldNumOfLinux);
    StatusType UpdateCountTree(int dataCenterID,int oldNumOfWindows,int oldNumOfLinux,int newNumOfWindows,int newNumOfLinux);
    int CountDataCenters(Node<DataCenter>* n);
    void GetDataCentersByOSHelper(Node<Pair>* t,int* i,int** dataCenters);
    void Quit();
};
bool operator< (const DataCenter& x,const DataCenter& y);
bool operator> (const DataCenter& x,const DataCenter& y);
bool operator== (const DataCenter& x,const DataCenter& y);
bool operator< (const Pair& x,const Pair& y);
bool operator> (const Pair& x,const Pair& y);
bool operator== (const Pair& x,const Pair& y);

#endif //MIVNIRATUV1_DATACENTERMANAGER_H
