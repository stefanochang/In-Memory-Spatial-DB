#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#ifndef DATASTORAGE_H
#include "data-storage.h"
#endif

using namespace std;

void test_insertData() {
    PointCollection *pntcollection;
    pntcollection = new PointCollection();

    Point *p1;
    p1 = new Point(12.34, 10.34);

    Point *p2;
    p2 = new Point(12.35, 10.34);

    Point *p3;
    p3 = new Point(12.36, 10.34);

    Point *p4;
    p4 = new Point(12.37, 10.34);

    cout << pntcollection->insert(*p1) << "\n";
    cout << pntcollection->insert(*p2) << "\n";
    cout << pntcollection->insert(*p3) << "\n";
    cout << pntcollection->insert(*p4) << "\n";
    cout <<"Size: " << pntcollection->getSize() << "\n";
}

int main()
{
    test_insertData();
    return 0;
}
