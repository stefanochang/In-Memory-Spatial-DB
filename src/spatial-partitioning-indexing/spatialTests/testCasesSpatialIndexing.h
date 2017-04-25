//
// Created by ravichandran on 18/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_TESTCASESSPATIALINDEXING_H
#define IN_MEMORY_SPATIAL_DB_TESTCASESSPATIALINDEXING_H

#include "testCasesqPoint.h"
#include "testCasesqBoundingBox.h"
#include "testCasesprQuadTree.h"
#include "testCasesprQuadTreeBulkLoad.h"
#include "testCasesmxcifQuadTree.h"
#include <ctime>

using namespace std;

void executeSpatialIndexingTestCases(int leafCapacity = 8)
{


    clock_t begin = clock();
    cout<<"\n\n\nSpatial Indexing Testing - Started"<<endl;
//    testQPoints();
//    testQBoundingBox();
//    testprQuadNode();
//    testprQuadTree(leafCapacity);
    testprQuadTreeBulkLoad(leafCapacity);
//    testmxcifQuadNode();
//    testmxcifQuadTree();

    cout<<"\n\n\nSpatial Indexing Testing - Ended"<<endl;

    clock_t end = clock();
    double elapsed_secs = double(end - begin)*1000 / CLOCKS_PER_SEC;
    cout<<"\n\n\n Time Elapsed = "<<elapsed_secs<<endl;
    long i = 0;
    cout<<"\n\n\nWhile Loop - Started"<<endl;
    while(true)i++;
//    cout<<"\n\n\nWhile Loop - Ended"<<endl;

}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASES_H
