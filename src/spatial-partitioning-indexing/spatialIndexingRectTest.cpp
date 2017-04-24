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
    RectangleCollection* rc = new RectangleCollection();
    Rectangle *testRect1 = new Rectangle(1,1,2,2);
    Rectangle *testRect2 = new Rectangle(1,2,3,3);
    Rectangle *testRect3 = new Rectangle(10,10,20,20);
    testRect1->setId(999);
    testRect2->setId(998);
    testRect3->setId(997);
    cout<<"before insertion - testRect  1 id = "<<testRect1->getId()<<endl;
    cout<<"before insertion - testRect  2 id = "<<testRect2->getId()<<endl;
    cout<<"before insertion - testRect  3 id = "<<testRect3->getId()<<endl;
    rc->insert(*testRect1);
    rc->insert(*testRect2);
    rc->insert(*testRect3);
    cout<<"after insertion - testRect 1 id = "<<testRect1->getId()<<endl;
    cout<<"after insertion - testRect 2 id = "<<testRect2->getId()<<endl;
    cout<<"after insertion - testRect 3 id = "<<testRect3->getId()<<endl;
    vector<Rectangle> curRects = rc->getNext(rc->getSize());
    cout<<"curRects Size = "<<curRects.size()<<endl;;
    for (int i=0;i<curRects.size();i++){
        cout<<"X1 = "<<(curRects.at(i)).getVal(0)<<" | Y1 = "<<(curRects.at(i)).getVal(1)<<" |X2 = "<<(curRects.at(i)).getVal(2)<<" | Y2 = "<<(curRects.at(i)).getVal(3)<<"| ID = "<<(curRects.at(i)).getId()<<endl;
    }
    cout << rc->getSize() << endl;
    //executeSpatialIndexingTestCases();
    SpatialIndexInterface* sp = new SpatialIndexImpl();
    sp->createIndex(*rc);
    Rectangle *r = new Rectangle(0,0,4,4);
	RectangleCollection res = sp->searchRectangle(*r, rc);
    int size = res.getSize();
	cout << "ResultSet size: " << size << endl;
	for (int i=0; i < size; i++) {
		vector<Rectangle> rectangle = res.getNext(1);
		vector<float> coords = rectangle[0].getCoordinates();
		cout << "[(" << coords[0] << ", " << coords[1] << "), (" << coords[2] << ", " << coords[3] << ")]" << endl;
	}
    return 0;
}