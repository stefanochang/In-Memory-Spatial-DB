
#include "spatialTests/testCasesSpatialIndexing.h"

using namespace std;

int main(int argc, char *argv[])
{
    int leafCapacity = 8;

    if(argc >= 1)leafCapacity = atoi(argv[0]);

    cout<<"Leaf Capacity at Main"<<leafCapacity<<endl;

    executeSpatialIndexingTestCases();
    return 0;
}


