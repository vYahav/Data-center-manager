#include "library1.h"
#include "DataCenterManager.h"
void * Init() {
    DataCenterManager *DS = new DataCenterManager ();
    return ( void *)DS;
}
StatusType AddDataCenter ( void * DS, int dataCenterID, int numOfServers) {
    return ((DataCenterManager *)DS)-> AddDataCenter (dataCenterID, numOfServers);
}