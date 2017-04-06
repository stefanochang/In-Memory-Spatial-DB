//
// Created by ravichandran on 19/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_TESTCASESMXCIFQUADTREE_H
#define IN_MEMORY_SPATIAL_DB_TESTCASESMXCIFQUADTREE_H

#include "../qUtilityFunctions.h"
#include "../mxcifQuadNode.h"
#include "../mxcifQuadTree.h"

using namespace std;


void testmxcifQuadNode()
{
    cout<<"\n\n mxcifQuadNode Testing - Started"<<endl;

    cout<<"\n\n mxcifQuadNode spatialTests Case 1"<<endl;
    mxcifQuadNode *mxcifQuadNode1= new mxcifQuadNode();
    mxcifQuadNode1->print();

    cout<<"\n\n mxcifQuadNode spatialTests Case 2"<<endl;
    qBoundingBox *tqbb1 = new qBoundingBox(0,0,100,100);
    mxcifQuadNode *mxcifQuadNode2= new mxcifQuadNode(*tqbb1);
    mxcifQuadNode2->print();

    cout<<"\n\n mxcifQuadNode Testing - Ended"<<endl;

}

void printmxcifQuadTreeRange(mxcifQuadTree *mxcifQT,float x, float y, float width, float height)
{
    vector<qBoundingBox> vQBoundingBox = mxcifQT->queryRange(x,y,width,height);
    printQBoundingBoxVectors(vQBoundingBox);

}


vector<qBoundingBox*> rectanglesTestCase1(){

    vector<qBoundingBox*> vQBoundingBox;

    vQBoundingBox.push_back(qBoundingBox::createRectangle(3,6,8,36,1));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(25,34,34,38,2));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(33,21,37,36,3));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(21,23,38,27,4));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(6,3,26,8,5));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(31,15,35,19,6));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(23,25,26,36,7));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(27,14.5,33.5,20.5,8));
    vQBoundingBox.push_back(qBoundingBox::createRectangle(16,3.5,22,7.5,9));


    return vQBoundingBox;

}

void mxcifQuadTreeTestCase1()
{
    cout<<"\n\nmxcifQuadTree spatialTests Case 1"<<endl;

    vector<qBoundingBox*> testQBoundingBoxes = rectanglesTestCase1();
    qBoundingBox *QBB = qBoundingBox::getQBoundingBoxCooridinates(testQBoundingBoxes);
    mxcifQuadTree *mxcifQT = new mxcifQuadTree(QBB);

    for(int i=0;i<testQBoundingBoxes.size();i++) {
        mxcifQT->insert(testQBoundingBoxes[i]);
    }
    mxcifQT->print();
    cout<<"\n\n\n\n\n"<<endl;
    cout<<"\n\nmxcifQuadTree 1 - Query Range 1"<<endl;
    printmxcifQuadTreeRange(mxcifQT,0,0,10,10);

    /**
     * CONCLUSION: Works fine
     */
}


void testmxcifQuadTree()
{
    cout<<"\n\n mxcifQuadTree Testing - Started"<<endl;

    mxcifQuadTreeTestCase1();

    cout<<"\n\n mxcifQuadTree Testing - Ended"<<endl;

}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASESMXCIFQUADTREE_H
