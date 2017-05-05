
#include "spatialTests/testCasesSpatialIndexing.h"

using namespace std;

int main(int argc, char *argv[])
{
    int leafCapacity = 8;

    if(argc >= 2)
    {
        leafCapacity = atoi(argv[1]);
    }

//    cout<<"\n\nEntering Main | Leaf Capacity = "<<leafCapacity<<endl;

    executeSpatialIndexingTestCases(leafCapacity);
    return 0;
}


