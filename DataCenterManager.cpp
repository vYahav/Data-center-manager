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

StatusType DataCenterManager::AddDataCenter(int dataCenterID, int numOfServers){
    cout<<endl<<"!!Adding Data Center..."<<endl;
    //Setting up the Data Center.  O(m)
    DataCenter ds;
    ds.dataCenterID=dataCenterID;
    ds.numOfServers=numOfServers;
    ds.servers=new Server[numOfServers];
    for (int i = 0; i < numOfServers; ++i) {
        ds.servers[i].inUse=false;
        ds.servers[i].opSystem=0;
    }
    //Inserting the data center in the tree.  O(log(n))
    AVLTree<DataCenter> tree;
    this->root = tree.treeInsert(this->root,ds);
    return SUCCESS;
}

StatusType DataCenterManager::RemoveDataCenter(int dataCenterID){
    return SUCCESS;
}

StatusType DataCenterManager::RequestServer(int dataCenterID, int serverID, int os, int *assignedID){
    return SUCCESS;

}

StatusType DataCenterManager::FreeServer(int dataCenterID, int serverID){
    return SUCCESS;

}

StatusType DataCenterManager::GetDataCentersByOS(int os, int **dataCenters, int* numOfDataCenters){
    return SUCCESS;

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



