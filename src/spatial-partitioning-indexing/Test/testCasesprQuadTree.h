//
// Created by ravichandran on 19/03/17.
//

#ifndef ADVDBTEST_TESTCASESPRQUADTREE_H_H
#define ADVDBTEST_TESTCASESPRQUADTREE_H_H

#include "../UtilityFunctions.h"
#include "../prQuadNode.h"
#include "../prQuadTree.h"

void testprQuadNode()
{
    cout<<"\n\n prQuadNode Testing - Started"<<endl;

    cout<<"\n\n prQuadNode Test Case 1"<<endl;
    prQuadNode *prQuadNode1= new prQuadNode();
    prQuadNode1->print();

    cout<<"\n\n prQuadNode Test Case 2"<<endl;
    QBoundingBox *tqbb1 = new QBoundingBox(0,0,100,100);
    prQuadNode *prQuadNode2= new prQuadNode(*tqbb1);
    prQuadNode2->print();

    cout<<"\n\n prQuadNode Testing - Ended"<<endl;

}

void printprQuadTreeRange(prQuadTree *prQT,float x, float y, float width, float height)
{
    vector<QPoint> vQPoint = prQT->queryRange(x,y,width,height);
    printQPointVectors(vQPoint);

}

//testcase 1:
vector<QPoint*> pointsTestCase1(){
    vector<QPoint*> vQPoint;
    vQPoint.push_back(new QPoint(20,20,5));
    vQPoint.push_back(new QPoint(30,30,6));
    vQPoint.push_back(new QPoint(40,40,7));
    vQPoint.push_back(new QPoint(22,22,10));
    vQPoint.push_back(new QPoint(42,42,11));

    return vQPoint;

}

void prQuadTreeTestCase1()
{
    cout<<"\n\nprQuadTree Test Case 1"<<endl;
    prQuadTree *prQT = new prQuadTree(0,0,200,200);
    vector<QPoint*> testQPoints=pointsTestCase1();
    for(int i=0;i<testQPoints.size();i++) {
        prQT->insert(testQPoints[i]);
    }
    prQT->print();
    cout<<"\n\n\n\n\n"<<endl;
    cout<<"\n\nprQuadTree 1 - Query Range 1"<<endl;
    printprQuadTreeRange(prQT,0,0,30,30);

    /**
     * CONCLUSION: Works fine
     */
}

void prQuadTreeTestCase1Delete()
{
    cout<<"\n\nDelete prQuadTree Test Case 1"<<endl;
    prQuadTree *prQT = new prQuadTree(0,0,200,200);
    vector<QPoint*> testQPoints=pointsTestCase1();
    for(int i=0;i<testQPoints.size();i++) {
        prQT->insert(testQPoints[i]);
    }
//    prQT->print();
    prQT->deleteRoot();
    cout<<"Root Deleted"<<endl;
    cout<<"\n\n\n\n\n"<<endl;

}

//testcase 2:
vector<QPoint*> pointsTestCase2(){
    vector<QPoint*> vQPoint;
    vQPoint.push_back(new QPoint(20,30,5));
    vQPoint.push_back(new QPoint(30,30,6));
    vQPoint.push_back(new QPoint(30,20,7));
    vQPoint.push_back(new QPoint(20,20,8));

    return vQPoint;

}

void prQuadTreeTestCase2()
{
    cout<<"\n\nprQuadTree Test Case 2"<<endl;
    prQuadTree *prQT = new prQuadTree(25,25,50,50);
    vector<QPoint*> testQPoints=pointsTestCase2();
    for(int i=0;i<testQPoints.size();i++) {
        prQT->insert(testQPoints[i]);
    }
    prQT->print();
    cout<<"\n\n\n\n\n"<<endl;
    cout<<"\n\nprQuadTree 2 - Query Range 1"<<endl;
    printprQuadTreeRange(prQT,0,0,30,30);

    cout<<"\n\nprQuadTree 2 - Query Range 1.1"<<endl;
    printprQuadTreeRange(prQT,30,30,1,1);

    cout<<"\n\nprQuadTree 2 - Query Range 2"<<endl;
    printprQuadTreeRange(prQT,0,0,31,31);

    cout<<"\n\nprQuadTree 2 - Query Range 3"<<endl;
    printprQuadTreeRange(prQT,0,0,20,20);

    cout<<"\n\nprQuadTree 2 - Query Range 4"<<endl;
    printprQuadTreeRange(prQT,0,0,21,21);

    cout<<"\n\nprQuadTree 2 - Query Range 5"<<endl;
    printprQuadTreeRange(prQT,30,30,0,0);

    cout<<"\n\nprQuadTree 2 - Query Range 6"<<endl;
    printprQuadTreeRange(prQT,29,29,1,1);

    cout<<"\n\nprQuadTree 2 - Query Range 7"<<endl;
    printprQuadTreeRange(prQT,30,30,1,1);

    cout<<"\n\nprQuadTree 2 - Query Range 8"<<endl;
    printprQuadTreeRange(prQT,20,30,1,1);

    cout<<"\n\nprQuadTree 2 - Query Range 9"<<endl;
    printprQuadTreeRange(prQT,19,29,1,1);

    cout<<"\n\nprQuadTree 2 - Query Range 10"<<endl;
    printprQuadTreeRange(prQT,30,20,1,1);

    cout<<"\n\nprQuadTree 2 - Query Range 11"<<endl;
    printprQuadTreeRange(prQT,29,19,1,1);

    cout<<"\n\nprQuadTree 2 - Query Range 12"<<endl;
    printprQuadTreeRange(prQT,15,15,30,10);

    /**
     * CONCLUSION: parameter height and width does not include points that lie on them,
     *             but parameters x and y include a points that lie on them
     */
}

//testcase 3:
vector<QPoint*> pointsTestCase3(){
    vector<QPoint*> vQPoint;
    vQPoint.push_back(new QPoint(100,100,5));
    vQPoint.push_back(new QPoint(150,150,6));
    vQPoint.push_back(new QPoint(175,175,7));
    vQPoint.push_back(new QPoint(187.5,187.5,8));
    vQPoint.push_back(new QPoint(193.75,193.75,9));
    return vQPoint;

}

void prQuadTreeTestCase3()
{
    cout<<"\n\nprQuadTree Test Case 3"<<endl;
    prQuadTree *prQT = new prQuadTree(0,0,400,400);
    vector<QPoint*> testQPoints=pointsTestCase3();
    for(int i=0;i<testQPoints.size();i++) {
        prQT->insert(testQPoints[i]);
    }
    prQT->print();
    cout<<"\n\n\n\n\n"<<endl;
    cout<<"\n\nprQuadTree 3 - Query Range 1"<<endl;
    printprQuadTreeRange(prQT,0,0,400,400);

    /**
     * CONCLUSION: Works fine
     */
}

//testcase 4:
vector<QPoint*> pointsTestCase4(){
    vector<QPoint*> vQPoint;
    vQPoint.push_back(new QPoint(55,55,5));
    vQPoint.push_back(new QPoint(60,60,6));
    vQPoint.push_back(new QPoint(65,65,7));
    vQPoint.push_back(new QPoint(70,70,8));
    vQPoint.push_back(new QPoint(50,60,9)); //on border
    return vQPoint;

}

void prQuadTreeTestCase4()
{
    cout<<"\n\nprQuadTree 4"<<endl;
    prQuadTree *prQT = new prQuadTree(50,50,100,100);
    vector<QPoint*> testQPoints = pointsTestCase4();
    for(int i=0;i<testQPoints.size();i++) {
        prQT->insert(testQPoints[i]);
    }

    prQT->print();
    cout<<"\n\n\n\n\n"<<endl;
    cout<<"\n\nprQuadTree 4 - Query Range 1"<<endl;
    printprQuadTreeRange(prQT,0,0,100,100);

    /**
     * CONCLUSION: Works fine
     */
}

void testprQuadTree()
{
    cout<<"\n\n prQuadTree Testing - Started"<<endl;

    prQuadTreeTestCase1();
//    prQuadTreeTestCase1Delete();
    prQuadTreeTestCase2();
    prQuadTreeTestCase3();
    prQuadTreeTestCase4();

    cout<<"\n\n prQuadTree Testing - Ended"<<endl;

}



#endif //ADVDBTEST_TESTCASESPRQUADTREE_H_H
