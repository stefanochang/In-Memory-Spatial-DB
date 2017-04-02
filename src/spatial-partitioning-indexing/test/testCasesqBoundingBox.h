//
// Created by ravichandran on 18/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_TESTCASESQBOUNDINGBOX_H
#define IN_MEMORY_SPATIAL_DB_TESTCASESQBOUNDINGBOX_H

#include "../quadTreeLib.h"
#include "../qBoundingBox.h"

using namespace std;

void qBoundingBoxTestCase1()
{
    cout<<"\nqBoundingBox 1"<<endl;
    qBoundingBox *tqbb1 = new qBoundingBox(100,100);
    tqbb1->print();
    tqbb1->set(200,100);
    tqbb1->print();
    tqbb1->set(10,10,200,100);
    tqbb1->print();

}

void qBoundingBoxTestCase2()
{
    cout<<"\nqBoundingBox 2"<<endl;
    qBoundingBox *tqbb2 = new qBoundingBox(0,0,100,100);
    tqbb2->print();
    tqbb2->set(50,50);
    tqbb2->print();
    tqbb2->set(10,10,100,100);
    tqbb2->print();

}


void qBoundingBoxTestCase3()
{
    cout<<"\nqBoundingBox 3"<<endl;
    float minX = 50;
    float minY = 50;
    float maxX = 100;
    float maxY = 100;
    qBoundingBox *tqbb3 = new qBoundingBox(minX,minY,maxX,maxY,24);
    tqbb3->print();

}




void testCreateQBoundingBox()
{
    cout<<"\n\n Create qBoundingBox Testing - Started"<<endl;

    qBoundingBoxTestCase1();
    qBoundingBoxTestCase2();
    qBoundingBoxTestCase3();

    cout<<"\n\n Create qBoundingBox Testing - Started"<<endl;

}

vector<qPoint*> pointsTestCaseQBoundingBox1(){

    vector<qPoint*> vQPoint;

    vQPoint.push_back(new qPoint(-20,-10,5));
    vQPoint.push_back(new qPoint(5,5,6));
    vQPoint.push_back(new qPoint(6,-26,7));
    vQPoint.push_back(new qPoint(10,-10,10));
    vQPoint.push_back(new qPoint(-5,-10,11));
    vQPoint.push_back(new qPoint(-5,11,11));

    return vQPoint;

}

void pointsGetQBoundingBoxTestCase1()
{
    cout<<"\nPoints test Case 1"<<endl;
    vector<qPoint*> testQPoints = pointsTestCaseQBoundingBox1();
    qBoundingBox *QBB = qBoundingBox::getQBoundingBoxCooridinates(testQPoints);
    QBB->print();

}

vector<qBoundingBox*> rectanglesTestCaseQBoundingBox1(){

    vector<qBoundingBox*> vQBoundingBox;

    vQBoundingBox.push_back(qBoundingBox::createRectangle(3,6,8,36));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(25,34,34,38));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(33,21,37,36));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(21,23,38,27));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(6,3,26,8));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(31,15,35,19));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(23,25,26,36));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(27,14.5,33.5,20.5));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(16,3.5,22,7.5));


    return vQBoundingBox;

}

void rectanglesGetQBoundingBoxTestCase1()
{
    cout<<"\nRectangles test Case 1"<<endl;
    vector<qBoundingBox*> testQBoundingBoxes = rectanglesTestCaseQBoundingBox1();
    qBoundingBox *QBB = qBoundingBox::getQBoundingBoxCooridinates(testQBoundingBoxes);
    QBB->print();

}

void testGetBoundingBoxCoordinates()
{
    cout<<"\n\n Get BoundingBox Co-ordinates Points - Testing - Started"<<endl;

    pointsGetQBoundingBoxTestCase1();
    rectanglesGetQBoundingBoxTestCase1();

    cout<<"\n\n Get BoundingBox Co-ordinates Points - Testing - Ended"<<endl;
}

void testQBoundingBox()
{
    cout<<"\n\n qBoundingBox Testing - Started"<<endl;

    testCreateQBoundingBox();
    testGetBoundingBoxCoordinates();


    cout<<"\n\n qBoundingBox Testing - Ended"<<endl;

}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASESQBOUNDINGBOX_H