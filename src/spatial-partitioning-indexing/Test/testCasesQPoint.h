
#ifndef ADVDBTEST_TESTCASESQPOINT_H
#define ADVDBTEST_TESTCASESQPOINT_H

#include "../QuadTreeLib.h"
#include "../QPoint.h"

using namespace std;


void testQPoints()
{
    cout<<"\n\n QPoints Testing - Started"<<endl;

    cout<<"\nQPoint Test Case 1"<<endl;
    QPoint *tPoint1 = new QPoint(0,0);
    tPoint1->print();
    tPoint1->set(2.5,2.8);
    tPoint1->print();

    cout<<"\nQPoint Test Case 2"<<endl;
    QPoint *tPoint2 = new QPoint(1,0,12);
    tPoint2->print();

    cout<<"\n\n QPoints Testing - Ended"<<endl;
}


#endif //ADVDBTEST_TESTCASESQPOINT_H