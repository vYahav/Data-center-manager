//
// Created by Yahav on 11/27/2019.
//

#include "DataCenterManager.h"
void * Init(){

}

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers){

}

StatusType RemoveDataCenter(void *DS, int dataCenterID){

}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
change test
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID){

}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){

}

void Quit(void** DS){

}