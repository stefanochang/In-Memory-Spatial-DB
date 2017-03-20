//
// Created by ravichandran on 18/03/17.
//

#ifndef ADVDBTEST_TESTCASES_H
#define ADVDBTEST_TESTCASES_H

#include "testCasesQPoint.h"
#include "testCasesQBoundingBox.h"
#include "testCasesprQuadTree.h"
#include "testCasesmxcifQuadTree.h"

using namespace std;

void executeSpatialIndexingTestCases()
{

    cout<<"\n\n\nSpatial Indexing Testing - Started"<<endl;
    testQPoints();
    testQBoundingBox();
    testprQuadNode();
    testprQuadTree();
    cout<<"\n\n\nSpatial Indexing Testing - Ended"<<endl;

}


#endif //ADVDBTEST_TESTCASES_H
