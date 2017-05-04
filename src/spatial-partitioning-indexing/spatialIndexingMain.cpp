
#include "spatialTests/testCasesSpatialIndexing.h"

using namespace std;

int main(int argc, char *argv[])
{
    int loop_exit = 0;
    int leafCapacity = 8;
    char quadTree = 'e';

    if(argc >= 2)
    {
        leafCapacity = atoi(argv[1]);
    }

    if(argc >= 3)
    {
        quadTree =  *argv[2];
    }

    if(argc >= 4)
    {
        loop_exit =  atoi(argv[3]);
    }


    cout<<"\n\nEntering Main | Leaf Capacity = "<<leafCapacity<<" | QuadTree Type = "<<quadTree<<endl;

    executeSpatialIndexingTestCases(leafCapacity,quadTree,loop_exit);
    return 0;
}


