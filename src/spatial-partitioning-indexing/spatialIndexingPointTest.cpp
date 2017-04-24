#ifndef CATALOG_H
#include "../integration/catalog.h"
#endif
#ifndef IN_MEMORY_SPATIAL_DB_SPATIALINDEXIMPL_H
#include "SpatialIndexImpl.h"
#endif
#include <iostream>
using namespace std;
int main()
{
    PointCollection *pc = new PointCollection();
    Point *testPoint3 = new Point(2, 1);
    Point *testPoint4 = new Point(3, 3);
    Point *testPoint = new Point(3, 4);
    Point *testPoint2 = new Point(1, 2);
    testPoint->setId(999);
    testPoint2->setId(998);
    testPoint3->setId(997);
    testPoint4->setId(996);
//    cout<<"before insertion - testPoint 1 id = "<<testPoint->getId()<<endl;
//    cout<<"before insertion - testPoint 2 id = "<<testPoint2->getId()<<endl;
//    cout<<"before insertion - testPoint 3 id = "<<testPoint3->getId()<<endl;
//    cout<<"before insertion - testPoint 4 id = "<<testPoint4->getId()<<endl;
    pc->insert(*testPoint);
    pc->insert(*testPoint2);
    pc->insert(*testPoint3);
    pc->insert(*testPoint4);
//    cout<<"after insertion - testPoint 1 id = "<<testPoint->getId()<<endl;
//    cout<<"after insertion - testPoint 2 id = "<<testPoint2->getId()<<endl;
//    cout<<"after insertion - testPoint 3 id = "<<testPoint3->getId()<<endl;
//    cout<<"after insertion - testPoint 4 id = "<<testPoint4->getId()<<endl;
    vector<Point> curPoints = pc->getNext(pc->getSize());
    cout<<"curPoints Size = "<<curPoints.size()<<endl;;
    for (int i=0;i<curPoints.size();i++){
        cout<<"x = "<<(curPoints.at(i)).getX()<<" | Y = "<<(curPoints.at(i)).getY()<<" | ID = "<<(curPoints.at(i)).getId()<<endl;
    }
    cout << pc->getSize() << endl;
    //executeSpatialIndexingTestCases();
    SpatialIndexInterface* sp = new SpatialIndexImpl();
    sp->createIndex(*pc);
    Rectangle *r = new Rectangle(0,0,100,100);
    PointCollection res = sp->searchPoint(*r, pc);
    cout << "Result: " << res.getSize();
    return 0;
}