//
// Created by ravichandran on 18/03/17.
//

#ifndef ADVDBTEST_TESTCASESQBOUNDINGBOX_H
#define ADVDBTEST_TESTCASESQBOUNDINGBOX_H

#include "../QuadTreeLib.h"
#include "../QBoundingBox.h"

using namespace std;

void testQBoundingBox()
{
    cout<<"\n\n QBoundingBox Testing - Started"<<endl;

    cout<<"\nQBoundingBox 1"<<endl;
    QBoundingBox *tqbb1 = new QBoundingBox(100,100);
    tqbb1->print();
    tqbb1->set(200,100);
    tqbb1->print();
    tqbb1->set(10,10,200,100);
    tqbb1->print();

    cout<<"\nQBoundingBox 2"<<endl;
    QBoundingBox *tqbb2 = new QBoundingBox(0,0,100,100);
    tqbb2->print();
    tqbb2->set(50,50);
    tqbb2->print();
    tqbb2->set(10,10,100,100);
    tqbb2->print();

    cout<<"\n\n QBoundingBox Testing - Ended"<<endl;

}


#endif //ADVDBTEST_TESTCASESQBOUNDINGBOX_H