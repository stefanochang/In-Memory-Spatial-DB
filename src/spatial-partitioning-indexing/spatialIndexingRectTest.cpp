#ifndef CATALOG_H
#include "../integration/catalog.h"
#endif
#ifndef IN_MEMORY_SPATIAL_DB_SPATIALINDEXIMPL_H
#include "SpatialIndexImpl.h"
#endif
#include <iostream>
using namespace std;

RectangleCollection* rectangleCollectionTestCases1()
{
    RectangleCollection* rectangleCollection = new RectangleCollection();

    Rectangle *testRect1 = new Rectangle(1,1,2,2);
    Rectangle *testRect2 = new Rectangle(1,2,3,3);
    Rectangle *testRect3 = new Rectangle(10,10,20,20);

    testRect1->setId(999);
    testRect2->setId(998);
    testRect3->setId(997);


    rectangleCollection->insert(*testRect1);
    rectangleCollection->insert(*testRect2);
    rectangleCollection->insert(*testRect3);

    return rectangleCollection;
}

void spatialIndexingRectsQueryRange(SpatialIndexInterface* spatialIndexInterface, RectangleCollection *rectangleCollection,double minX, double minY, double maxX, double maxY)
{

    Rectangle *rectangle = new Rectangle(minX,minY,maxX,maxY);
    RectangleCollection rectangleCollectionResult = spatialIndexInterface->searchRectangle(*rectangle, rectangleCollection);
    int size = rectangleCollectionResult.getSize();
    cout << "\n\n\tQuery Range For ( "<<minX<<" , "<<minY<<" ) , ( "<<maxX<<" , "<<maxY<<" ) "<<endl;
    cout<<"\t\t Result Size =  " <<size<<endl;
    for (int i=0; i < size; i++) {
        vector<Rectangle> rectangle = rectangleCollectionResult.getNext(1);
        vector<float> coords = rectangle[0].getCoordinates();
        cout << "\t\t\t ( " << coords[0] << " , " << coords[1] << " ), ( " << coords[2] << " , " << coords[3] << " ) " << endl;
    }

}

int main()
{

    cout<<"\n Spatial Indexing Integration Testing Rectangles - Started \n"<<endl;

    RectangleCollection* rectangleCollection = rectangleCollectionTestCases1();


    vector<Rectangle> curRects = rectangleCollection->getNext(rectangleCollection->getSize());


    cout<<"\t Size Of Rectangles Created = "<<curRects.size()<<endl;

    for (int i=0;i<curRects.size();i++){
        cout<<"\t\t Rectangle | minX = "<<(curRects.at(i)).getVal(0)<<" | minY = "<<(curRects.at(i)).getVal(1)<<" | maxX = "<<(curRects.at(i)).getVal(2)<<" | maxY = "<<(curRects.at(i)).getVal(3)<<"| ID = "<<(curRects.at(i)).getId()<<endl;
    }

    cout<<"\t Size Of Rectangles Loaded = "<<rectangleCollection->getSize()<<endl;

    SpatialIndexInterface* spatialIndexInterface = new SpatialIndexImpl();
    spatialIndexInterface->createIndex(*rectangleCollection);

    spatialIndexingRectsQueryRange(spatialIndexInterface,rectangleCollection,0,0,4,4);

    spatialIndexingRectsQueryRange(spatialIndexInterface,rectangleCollection,0,0,21,21);

    spatialIndexingRectsQueryRange(spatialIndexInterface,rectangleCollection,9,9,21,21);

    spatialIndexingRectsQueryRange(spatialIndexInterface,rectangleCollection,9,9,19,19);

    spatialIndexingRectsQueryRange(spatialIndexInterface,rectangleCollection,15,15,19,19);

    cout<<"\n Spatial Indexing Integration Testing Rectangles - Ended \n"<<endl;

    return 0;
}