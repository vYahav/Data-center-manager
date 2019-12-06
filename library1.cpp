#include "library1.h"
#include "DataCenterManager.h"
#include "iostream"
void * Init() {
    DataCenterManager *DS = new DataCenterManager ();
    return ( void *)DS;
}
StatusType AddDataCenter ( void * DS, int dataCenterID, int numOfServers) {
    if(dataCenterID<=0 || DS==NULL || numOfServers<=0) return INVALID_INPUT; //Invalid input check
    return ((DataCenterManager *)DS)-> AddDataCenter (dataCenterID, numOfServers);
}

StatusType RemoveDataCenter(void *DS, int dataCenterID){
    if(dataCenterID<=0 || DS==NULL) return INVALID_INPUT;
    return ((DataCenterManager *)DS)-> RemoveDataCenter (dataCenterID);
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    if(DS==NULL || serverID<0 || assignedID==NULL || os>1 || os<0 || dataCenterID<=0) return INVALID_INPUT;
    return ((DataCenterManager *)DS)-> RequestServer (dataCenterID,serverID,os,assignedID);
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    if(DS==NULL || serverID<0 || dataCenterID<=0) return INVALID_INPUT;
    return ((DataCenterManager *)DS)-> FreeServer (dataCenterID,serverID);
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    if(DS==NULL || dataCenters==NULL || os>1 || numOfDataCenters==NULL || os<0) return INVALID_INPUT;
    return ((DataCenterManager *)DS)-> GetDataCentersByOS (os,dataCenters,numOfDataCenters);
}

void Quit(void** DS){
    ((DataCenterManager *)*DS)-> Quit ();
    DataCenterManager** BS=(DataCenterManager**)DS;
    delete *(DataCenterManager**)BS;
    *DS=NULL;
}