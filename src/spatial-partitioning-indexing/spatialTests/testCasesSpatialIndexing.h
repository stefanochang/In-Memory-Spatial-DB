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

using namespace std;

void executeSpatialIndexingTestCases()
{

    cout<<"\n\n\nSpatial Indexing Testing - Started"<<endl;
//    testQPoints();
//    testQBoundingBox();
//    testprQuadNode();
    testprQuadTree();
//    testprQuadTreeBulkLoad();
//    testmxcifQuadNode();
//    testmxcifQuadTree();

    cout<<"\n\n\nSpatial Indexing Testing - Ended"<<endl;
//    long i = 0;
//    cout<<"\n\n\nWhile Loop - Started"<<endl;
//    while(true)i++;
//    cout<<"\n\n\nWhile Loop - Ended"<<endl;

}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASES_H
