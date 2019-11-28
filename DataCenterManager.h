//
// Created by Yahav on 11/27/2019.
//

#ifndef MIVNIRATUV1_DATACENTERMANAGER_H
#define MIVNIRATUV1_DATACENTERMANAGER_H
#include "library1.h"
#include "AVLTree.h"
struct Server{
    int opSystem; //Linux=0 , Windows=1. Default=0.
    bool inUse; //True= server is currently in use , False= server is free to use.
};
struct DataCenter {
    int dataCenterID;
    int numOfServers;
    Server* servers;
};

class DataCenterManager {

    AVLTree<DataCenter> * root;
    StatusType AddDataCenter(int dataCenterID, int numOfServers);

    StatusType RemoveDataCenter(int dataCenterID);

    StatusType RequestServer(int dataCenterID, int serverID, int os, int *assignedID);

    StatusType FreeServer(int dataCenterID, int serverID);

    StatusType GetDataCentersByOS(int os, int **dataCenters, int* numOfDataCenters);

    void Delete();

};


#endif //MIVNIRATUV1_DATACENTERMANAGER_H
