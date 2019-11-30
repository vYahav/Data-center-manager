//
// Created by Yahav on 11/27/2019.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "DataCenterManager.h"
using namespace std;

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


//============================================================================================
//=========================    AVLTree Class Functions    ====================================
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





//============================================================================================
//=========================    DataCenterManager Class Functions    ==========================
StatusType DataCenterManager::AddToCountTree(int dataCenterID,int numOfWindows,int numOfLinux){
    //Adding to [os]Tree.  O(2*log(n))=O(log(n))
    AVLTree<Pair> k;
    Pair linuxP,windowsP;
    linuxP.dataCenterID=dataCenterID;
    windowsP.dataCenterID=dataCenterID;
    linuxP.serverCount=numOfLinux;
    windowsP.serverCount=numOfWindows;
    this->linuxTree=k.treeInsert(this->linuxTree,linuxP);
    this->windowsTree=k.treeInsert(this->windowsTree,windowsP);
    //----
    return SUCCESS;
}
StatusType DataCenterManager::RemoveFromCountTree(int dataCenterID,int oldNumOfWindows,int oldNumOfLinux){
    //Removing data center from windowsTree and linuxTree
    //Setting up the Pair to look for.  O(1)
    Pair winP,linuxP;
    winP.dataCenterID=dataCenterID;
    linuxP.dataCenterID=dataCenterID;
    winP.serverCount=oldNumOfWindows;
    linuxP.serverCount=oldNumOfLinux;
    //Getting the node we want to delete.  O(log(n))
    AVLTree<Pair> k;
    Node<Pair>* linuxnode=k.treeFind(this->linuxTree,linuxP);
    Node<Pair>* winnode=k.treeFind(this->windowsTree,winP);
    if(linuxnode==NULL || winnode==NULL) return FAILURE;
    //Removing the node from the tree. O(log(n))
    Node<Pair>* templinux=k.treeDeleteNode(this->linuxTree,linuxP);
    Node<Pair>* tempwindows=k.treeDeleteNode(this->windowsTree,winP);

    this->linuxTree=templinux;
    this->windowsTree=tempwindows;
    //---
    return SUCCESS;
}
StatusType DataCenterManager::UpdateCountTree(int dataCenterID,int oldNumOfWindows,int oldNumOfLinux,int newNumOfWindows,int newNumOfLinux){
    RemoveFromCountTree(dataCenterID,oldNumOfWindows,oldNumOfLinux);
    AddToCountTree(dataCenterID,newNumOfWindows,newNumOfLinux);
}






StatusType DataCenterManager::AddDataCenter(int dataCenterID, int numOfServers){ // O(log(n) + m)
    //Setting up the Data Center.  O(m)
    AVLTree<DataCenter> t;
    DataCenter ds;
    ds.dataCenterID=dataCenterID;

    if(t.treeFind(this->root,ds)!=NULL) return FAILURE; //return failure because there is already a center with this ID.   O(log(n))

    ds.numOfServers=numOfServers;
    ds.servers=new Node<Server>*[numOfServers];
    ds.linuxFirstServerID=new int;
    ds.windowsFirstServerID=new int;
    ds.linuxLastServerID=new int;
    ds.windowsLastServerID=new int;
    ds.numOfWindowsServers=new int;
    ds.numOfLinuxServers=new int;
    *ds.linuxFirstServerID=0;
    *ds.windowsFirstServerID=-1;
    *ds.linuxLastServerID=numOfServers-1;
    *ds.windowsLastServerID=-1;
    *ds.numOfWindowsServers=0;
    *ds.numOfLinuxServers=numOfServers;

    if(ds.servers==NULL) return ALLOCATION_ERROR; //Failed to allocate memory for the array
    for (int i = 0; i < numOfServers; i++) { //Creating the servers.  O(m)
        Node<Server>* newNode= new Node<Server>;
        (*newNode).data.opSystem=0;
        (*newNode).data.inUse=false;
        (*newNode).data.serverID=i;
        ds.servers[i]=newNode;
    }
    //Linking the servers with each other.  O(m)
    ds.servers[0]->l=NULL;
    for (int j = 0; j < numOfServers-1; j++) {
        ds.servers[j]->r=ds.servers[j+1];
        ds.servers[j+1]->l=ds.servers[j];
    }
    ds.servers[numOfServers-1]->r=NULL;
    //Inserting the data center in the tree.  O(2*log(n)) = O(log(n))
     this->root = t.treeInsert(this->root , ds);
     return AddToCountTree(dataCenterID,0,numOfServers); // O(log(n))
}

StatusType DataCenterManager::RemoveDataCenter(int dataCenterID){   // O(log(n) + m)
    //Setting up the Data Center to look for.  O(1)
    DataCenter ds;
    ds.dataCenterID=dataCenterID;
    //Getting the node we want to delete.  O(log(n))
    AVLTree<DataCenter> t;
    Node<DataCenter>* n=t.treeFind(this->root,ds);
    int oldnumofwin=*n->data.numOfWindowsServers;
    int oldnumoflinux=*n->data.numOfLinuxServers;
    if(n==NULL) return FAILURE;
    //Removing the node from the tree. O(log(n))
    Node<DataCenter>* temp=t.treeDeleteNode(this->root,ds);
    this->root=temp;

    if(RemoveFromCountTree(dataCenterID,oldnumofwin,oldnumoflinux)!=SUCCESS){
        cout<<endl<<"WHAT?!"<<endl;
        return FAILURE;
    }

    //Free-ing the node values. O(1)
    delete n->data.servers;
    delete n;
    //NEED TO ADD HERE: FREE THE SERVERS NODES AND ARRAY AND int POINTERS

    //Done.
    return SUCCESS;
}

StatusType DataCenterManager::RequestServer(int dataCenterID, int serverID, int os, int *assignedID){
    //Setting up Data Center.  O(1)
    DataCenter ds;
    ds.dataCenterID=dataCenterID;
    //Retrieving the given Data Center. O(log(n))
    AVLTree<DataCenter> t;
    if(t.treeFind(this->root,ds)==NULL) return FAILURE;
    ds= t.treeFind(this->root,ds)->data;

    //Finding the given server.  O(1)
    if((*ds.linuxFirstServerID)==-1 && (*ds.windowsFirstServerID)==-1) return FAILURE; //No free servers available

    ds.servers[serverID]->data;
    if(!ds.servers[serverID]->data.inUse)
    {
        if((*ds.linuxFirstServerID)==serverID)
        {
            if(ds.servers[serverID]->r!=NULL)(*ds.linuxFirstServerID)=ds.servers[serverID]->r->data.serverID;
            else{
                (*ds.linuxFirstServerID) = -1;
                (*ds.linuxLastServerID) = -1;
            }
        }
        if((*ds.windowsFirstServerID)==serverID)
        {
            if(ds.servers[serverID]->r!=NULL) (*ds.windowsFirstServerID)=ds.servers[serverID]->r->data.serverID;
            else{
                (*ds.windowsFirstServerID) = -1;
                (*ds.windowsLastServerID) = -1;
            }
        }
        ds.servers[serverID]->data.inUse=true;
        *assignedID=serverID;

        if(ds.servers[serverID]->r!=NULL) ds.servers[serverID]->r->l=ds.servers[serverID]->l;
        if(ds.servers[serverID]->l!=NULL) ds.servers[serverID]->l->r=ds.servers[serverID]->r;
        ds.servers[serverID]->l=NULL;
        ds.servers[serverID]->r=NULL;
        int oldnumofwin=(*ds.numOfWindowsServers);
        int oldnumoflinux=(*ds.numOfLinuxServers);
        if(os==0 && ds.servers[serverID]->data.opSystem==1)
        {
            (*ds.numOfLinuxServers)++;
            (*ds.numOfWindowsServers)--;
        }
        if(os==1 && ds.servers[serverID]->data.opSystem==0)
        {
            (*ds.numOfLinuxServers)--;
            (*ds.numOfWindowsServers)++;
        }
        ds.servers[serverID]->data.opSystem=os;
        if(UpdateCountTree(dataCenterID,oldnumofwin,oldnumoflinux,(*ds.numOfWindowsServers),(*ds.numOfLinuxServers))!=SUCCESS){ //O(log(n))
            cout<<endl<<"PROBSSS 1"<<endl;
            return FAILURE;
        }
        return SUCCESS;
    }
    //serverID is taken; Finding a different server with the same operating system.  O(1)
    if(os==0 && (*ds.linuxFirstServerID)!=-1){
        serverID=(*ds.linuxFirstServerID);

        if(ds.servers[serverID]->r!=NULL) (*ds.linuxFirstServerID)=ds.servers[serverID]->r->data.serverID;
        else{
            (*ds.linuxFirstServerID) = -1;
            (*ds.linuxLastServerID) = -1;
        }
        ds.servers[serverID]->data.inUse=true;
        *assignedID=serverID;
        if(ds.servers[serverID]->r!=NULL) ds.servers[serverID]->r->l=ds.servers[serverID]->l;
        if(ds.servers[serverID]->l!=NULL) ds.servers[serverID]->l->r=ds.servers[serverID]->r;
        ds.servers[serverID]->l=NULL;
        ds.servers[serverID]->r=NULL;

        return SUCCESS;
    }
    if(os==1 && (*ds.windowsFirstServerID)!= -1){
        serverID=(*ds.windowsFirstServerID);

        if (ds.servers[serverID]->r != NULL) (*ds.windowsFirstServerID) = ds.servers[serverID]->r->data.serverID;
        else {
            (*ds.windowsFirstServerID) = -1;
            (*ds.windowsLastServerID) = -1;
        }

        ds.servers[serverID]->data.inUse=true;
        *assignedID=serverID;
        if(ds.servers[serverID]->r!=NULL) ds.servers[serverID]->r->l=ds.servers[serverID]->l;
        if(ds.servers[serverID]->l!=NULL) ds.servers[serverID]->l->r=ds.servers[serverID]->r;
        ds.servers[serverID]->l=NULL;
        ds.servers[serverID]->r=NULL;

        return SUCCESS;
    }
    //Couldn't find a different server with the same operating system; Finding a free server and installing the given OS
    //O(1)
    if(os==0 && (*ds.windowsFirstServerID)!= -1){
        serverID=(*ds.windowsFirstServerID);

        if (ds.servers[serverID]->r != NULL) (*ds.windowsFirstServerID) = ds.servers[serverID]->r->data.serverID;
        else {
            (*ds.windowsFirstServerID) = -1;
            (*ds.windowsLastServerID) = -1;
        }

        ds.servers[serverID]->data.inUse=true;
        *assignedID=serverID;
        if(ds.servers[serverID]->r!=NULL) ds.servers[serverID]->r->l=ds.servers[serverID]->l;
        if(ds.servers[serverID]->l!=NULL) ds.servers[serverID]->l->r=ds.servers[serverID]->r;
        ds.servers[serverID]->l=NULL;
        ds.servers[serverID]->r=NULL;
        int oldnumofwin=(*ds.numOfWindowsServers);
        int oldnumoflinux=(*ds.numOfLinuxServers);
        if(os==0 && ds.servers[serverID]->data.opSystem==1)
        {
            (*ds.numOfLinuxServers)++;
            (*ds.numOfWindowsServers)--;
        }
        ds.servers[serverID]->data.opSystem=os;
        if(UpdateCountTree(dataCenterID,oldnumofwin,oldnumoflinux,(*ds.numOfWindowsServers),(*ds.numOfLinuxServers))!=SUCCESS){ //O(log(n))
            cout<<endl<<"PROBSSS 1"<<endl;
            return FAILURE;
        }
        return SUCCESS;
    }

    if(os==1 && (*ds.linuxFirstServerID)!=-1){
        serverID=(*ds.linuxFirstServerID);

        if(ds.servers[serverID]->r!=NULL) (*ds.linuxFirstServerID)=ds.servers[serverID]->r->data.serverID;
        else{
            (*ds.linuxFirstServerID) = -1;
            (*ds.linuxLastServerID) = -1;
        }
        ds.servers[serverID]->data.inUse=true;
        *assignedID=serverID;
        if(ds.servers[serverID]->r!=NULL) ds.servers[serverID]->r->l=ds.servers[serverID]->l;
        if(ds.servers[serverID]->l!=NULL) ds.servers[serverID]->l->r=ds.servers[serverID]->r;
        ds.servers[serverID]->l=NULL;
        ds.servers[serverID]->r=NULL;
        int oldnumofwin=(*ds.numOfWindowsServers);
        int oldnumoflinux=(*ds.numOfLinuxServers);
        if(os==1 && ds.servers[serverID]->data.opSystem==0)
        {
            (*ds.numOfLinuxServers)--;
            (*ds.numOfWindowsServers)++;
        }
        ds.servers[serverID]->data.opSystem=os;
        if(UpdateCountTree(dataCenterID,oldnumofwin,oldnumoflinux,(*ds.numOfWindowsServers),(*ds.numOfLinuxServers))!=SUCCESS){ //O(log(n))
            cout<<endl<<"PROBSSS 1"<<endl;
            return FAILURE;
        }
        return SUCCESS;
    }

    return FAILURE;
}

StatusType DataCenterManager::FreeServer(int dataCenterID, int serverID){
    //Setting up Data Center.  O(1)
    DataCenter ds;
    ds.dataCenterID=dataCenterID;
    //Retrieving the given Data Center. O(log(n))
    AVLTree<DataCenter> t;
    if(t.treeFind(this->root,ds)==NULL) return FAILURE;
    ds= t.treeFind(this->root,ds)->data;
    if(serverID>=ds.numOfServers) return INVALID_INPUT;
    //Finding the given server and changing "inUse" to False.  O(1)
    if(!ds.servers[serverID]->data.inUse) return FAILURE;
    ds.servers[serverID]->data.inUse=false;



    int os=ds.servers[serverID]->data.opSystem;
    if(os==0){
        //Setting linuxLastServerID to serverID.  O(1)
        if((*ds.linuxLastServerID)==-1){
            (*ds.linuxLastServerID)=serverID;
            (*ds.linuxFirstServerID)=serverID;
        }
        else{
            int serverBeforeLastID;
            serverBeforeLastID=(*ds.linuxLastServerID);
            //Updating linuxLastServerID from old to new serverID.  O(1)
            (*ds.linuxLastServerID)=serverID;
            //Putting the server in the node list, as the last node, linking it with the previous last node.  O(1)
            ds.servers[serverBeforeLastID]->r=ds.servers[serverID];
            ds.servers[serverID]->l=ds.servers[serverBeforeLastID];
        }
        return SUCCESS;
    }

    if(os==1){
        //Setting windowsLastServerID to serverID.  O(1)
        if((*ds.windowsLastServerID)==-1){
            (*ds.windowsLastServerID)=serverID;
            (*ds.windowsFirstServerID)=serverID;
        }
        else{
            int serverBeforeLastID;
            serverBeforeLastID=(*ds.windowsLastServerID);
            //Updating linuxLastServerID from old to new serverID.  O(1)
            (*ds.windowsLastServerID)=serverID;
            //Putting the server in the node list, as the last node, linking it with the previous last node.  O(1)
            ds.servers[serverBeforeLastID]->r=ds.servers[serverID];
            ds.servers[serverID]->l=ds.servers[serverBeforeLastID];
        }
        return SUCCESS;
    }

    return FAILURE;
}
int DataCenterManager::CountDataCenters(Node<DataCenter>* n){
    if(n->l!=NULL && n->r!=NULL) return 1+CountDataCenters(n->l) + CountDataCenters(n->r);
    if(n->l!=NULL) return 1+CountDataCenters(n->l);
    if(n->r!=NULL) return 1+CountDataCenters(n->r);
    if(n->r==NULL && n->l==NULL) return 1;
    return 0;

}

StatusType DataCenterManager::GetDataCentersByOS(int os, int **dataCenters, int* numOfDataCenters){
    if(this->root==NULL) return FAILURE;
    *numOfDataCenters=0;
    *numOfDataCenters=CountDataCenters(this->root);
    cout<<endl<<"COUNT RESULT:"<<*numOfDataCenters<<endl;
    int* array= (int*) malloc((*numOfDataCenters)*sizeof(int));
    dataCenters=(int**) malloc(sizeof(array));
    *dataCenters=array;
    if(os==0){
        //linuxTree inorder traversal
    }
    if(os==1){
        //winTree inorder
    }
    return FAILURE;
}
void DataCenterManager::Quit(){

}

bool operator< (const DataCenter& x,const DataCenter& y){
    if(x.dataCenterID<y.dataCenterID) return true;
    return false;
}
bool operator> (const DataCenter& x,const DataCenter& y){
    if(x.dataCenterID>y.dataCenterID) return true;
    return false;
}
bool operator== (const DataCenter& x,const DataCenter& y){
    if(x.dataCenterID==y.dataCenterID) return true;
    return false;
}
bool operator< (const Pair& x,const Pair& y){
    if(x.serverCount<y.serverCount) return true;
    return false;
}
bool operator> (const Pair& x,const Pair& y){
    if(x.serverCount>y.serverCount) return true;
    return false;
}
bool operator== (const Pair& x,const Pair& y){
    if(x.dataCenterID==y.dataCenterID) return true;
    return false;
}