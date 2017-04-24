#ifndef CATALOG_H
#include "../integration/catalog.h"
#endif
#ifndef IN_MEMORY_SPATIAL_DB_SPATIALINDEXIMPL_H
#include "SpatialIndexImpl.h"
#endif
#include <iostream>
using namespace std;


PointCollection* pointCollectionTestCases1()
{
    PointCollection *pointCollection = new PointCollection();

    Point *testPoint1 = new Point(3, 4);
    Point *testPoint2 = new Point(1, 2);
    Point *testPoint3 = new Point(2, 1);
    Point *testPoint4 = new Point(3, 3);

    Point *testPoint5 = new Point(-1, -2);
    Point *testPoint6 = new Point(-1, 2);
    Point *testPoint7 = new Point(1, -2);

    testPoint1->setId(999);
    testPoint2->setId(998);
    testPoint3->setId(997);
    testPoint4->setId(996);
    testPoint5->setId(995);
    testPoint6->setId(994);
    testPoint7->setId(993);

    pointCollection->insert(*testPoint1);
    pointCollection->insert(*testPoint2);
    pointCollection->insert(*testPoint3);
    pointCollection->insert(*testPoint4);
    pointCollection->insert(*testPoint5);
    pointCollection->insert(*testPoint6);
    pointCollection->insert(*testPoint7);

    return pointCollection;
}

void spatialIndexingPointsQueryRange(SpatialIndexInterface* spatialIndexInterface, PointCollection *pointCollection,double minX, double minY, double maxX, double maxY)
{
    Rectangle *rectangle = new Rectangle(minX,minY,maxX,maxY);
    PointCollection pointCollectionresult = spatialIndexInterface->searchPoint(*rectangle, pointCollection);
    int size = pointCollectionresult.getSize();
    cout << "\n\n\tQuery Range For ( "<<minX<<" , "<<minY<<" ) , ( "<<maxX<<" , "<<maxY<<" ) "<<endl;
    cout<<"\t\t Result Size =  " <<size<<endl;

    for (int i=0; i < size ; i++) {
        vector<Point> point = pointCollectionresult.getNext(1);
        vector<float> coords = point[0].getCoordinates();
        cout << "\t\t\t ( " << coords[0] << ", " << coords[1] << " ) "<< endl;
    }

}
int main()
{

    cout<<"\n Spatial Indexing Integration Testing Points - Started \n"<<endl;

    PointCollection *pointCollection = pointCollectionTestCases1();


    vector<Point> curPoints = pointCollection->getNext(pointCollection->getSize());

    cout<<"\t Size Of Points Created = "<<curPoints.size()<<endl;;

    for (int i=0;i<curPoints.size();i++){
        cout<<"\t\tPoint | X = "<<(curPoints.at(i)).getX()<<" | Y = "<<(curPoints.at(i)).getY()<<" | ID = "<<(curPoints.at(i)).getId()<<endl;
    }


    cout<<"\t Size Of Points Loaded = "<<pointCollection->getSize()<<endl;;


    SpatialIndexInterface* spatialIndexInterface = new SpatialIndexImpl();
    spatialIndexInterface->createIndex(*pointCollection);

    spatialIndexingPointsQueryRange(spatialIndexInterface,pointCollection,0,0,100,100);

    spatialIndexingPointsQueryRange(spatialIndexInterface,pointCollection,0,0,2.5,2.5);

    spatialIndexingPointsQueryRange(spatialIndexInterface,pointCollection,0,0,2.5,-2.5);

    spatialIndexingPointsQueryRange(spatialIndexInterface,pointCollection,0,0,-2.5,2.5);

    spatialIndexingPointsQueryRange(spatialIndexInterface,pointCollection,0,0,-2.5,-2.5);


    cout<<"\n Spatial Indexing Integration Testing Points - Ended \n"<<endl;

    return 0;
}