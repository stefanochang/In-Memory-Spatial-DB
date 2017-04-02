
#ifndef IN_MEMORY_SPATIAL_DB_TESTCASESQPOINT_H
#define IN_MEMORY_SPATIAL_DB_TESTCASESQPOINT_H

#include "../quadTreeLib.h"
#include "../qPoint.h"

using namespace std;


void testQPoints()
{
    cout<<"\n\n QPoints Testing - Started"<<endl;

    cout<<"\nQPoint spatialTests Case 1"<<endl;
    qPoint *tPoint1 = new qPoint(0,0);
    tPoint1->print();
    tPoint1->set(2.5,2.8);
    tPoint1->print();

    cout<<"\nQPoint spatialTests Case 2"<<endl;
    qPoint *tPoint2 = new qPoint(1,0,12);
    tPoint2->print();

    cout<<"\n\n QPoints Testing - Ended"<<endl;
}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASESQPOINT_H