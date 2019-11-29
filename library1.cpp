#include "library1.h"
#include "DataCenterManager.h"
void * Init() {
    DataCenterManager *DS = new DataCenterManager ();
    return ( void *)DS;
}
StatusType AddDataCenter ( void * DS, int dataCenterID, int numOfServers) {
    if(dataCenterID<=0 || DS==NULL || numOfServers<=0) return INVALID_INPUT; //Invalid input check
    return ((DataCenterManager *)DS)-> AddDataCenter (dataCenterID, numOfServers);
}

StatusType RemoveDataCenter(void *DS, int dataCenterID){
    return ((DataCenterManager *)DS)-> RemoveDataCenter (dataCenterID);
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    return ((DataCenterManager *)DS)-> RequestServer (dataCenterID,serverID,os,assignedID);
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    return ((DataCenterManager *)DS)-> FreeServer (dataCenterID,serverID);
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    return ((DataCenterManager *)DS)-> GetDataCentersByOS (os,dataCenters,numOfDataCenters);
}

void Quit(void** DS){
    return ((DataCenterManager *)DS)-> Quit ();
}