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
#include "testCasesmxcifQuadTreeBulkLoad.h"

using namespace std;

void executeSpatialIndexingTestCases(int leafCapacity = 8, char quadTree = 'e', int loop_exit = 0)
{

    milliseconds start_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    cout<<"\n\n\nSpatial Indexing Testing - Started"<<endl;


    if(quadTree == 'p')
    {
            testprQuadTreeBulkLoad(leafCapacity);
    }
    else if(quadTree == 'r')
    {
        testmxcifQuadTreeBulkLoad(leafCapacity);
    } else
    {
//        testQPoints();
//        testQBoundingBox();
//        testprQuadNode();
//        testprQuadTree(leafCapacity);
//        testprQuadTreeBulkLoad(leafCapacity);
//        testmxcifQuadNode(leafCapacity);
//        testmxcifQuadTree(leafCapacity);
        testmxcifQuadTreeBulkLoad(leafCapacity);
    }

    cout<<"\n\n\nSpatial Indexing Testing - Ended"<<endl;


    milliseconds end_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );


    milliseconds diff_ms = (end_ms - start_ms);

    cout<<"\n\n\n Time Elapsed = "<<std::to_string(diff_ms.count())<<endl;

    int min_exit = loop_exit;
    int milli_sec = 60000;
    long total_time = min_exit*milli_sec;

    cout<<"\n\n\nWhile Loop - Started"<<endl;
    cout<<"\n\nTime - Mins = "<<min_exit<<endl;
    milliseconds cur_start_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    while(true)
    {
        milliseconds cur_end_ms = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch()
        );
        milliseconds cur_diff_ms = (cur_end_ms - cur_start_ms);

        if(cur_diff_ms.count()>=total_time)break;
    }
    cout<<"\n\nWhile Loop - Ended"<<endl;

}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASES_H
