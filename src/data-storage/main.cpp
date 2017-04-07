#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#ifndef DATASTORAGE_H
#include "data-storage.h"
#include "../integration/catalog.h"
#endif
#ifndef CATALOG_H
#include "../integration/catalog.h"
#endif
using namespace std;

void printData(PointCollection *pointsRepo){
  ds_record *tmp_head;
  tmp_head = pointsRepo->getHead();
  if(tmp_head == NULL)
    cout << "Empty Collection" << "\n";
  else{
    cout << "X: " << tmp_head->geom->pnt->x;
    cout << " Y: " << tmp_head->geom->pnt->y << "\n";
    ds_record *tmp_node = tmp_head->next;
    while(tmp_node != tmp_head){
      cout << "X: " << tmp_node->geom->pnt->x;
      cout << " Y: " << tmp_node->geom->pnt->y << "\n";
      tmp_node = tmp_node->next;
    }
  }

}

bool testGetNextSingle() {
  PointCollection *pc = new PointCollection();

  Point *testPoint = new Point(1, 2);

  pc->insert(*testPoint);

  vector<Point> result = pc->getNext(1, 1);
  bool testResultSize = result.size() == 1;

  bool testResultPointCoordinates = false;
  if(result.size() > 0) {
      vector<float> resultPointCoordinates = result[0].getCoordinates();
      testResultPointCoordinates = resultPointCoordinates[0] == 1 && resultPointCoordinates[1] == 2;
      if(!testResultPointCoordinates) {
        cout << "testGetNextSingle: Failed in getting single points\n";
        return false;
      }
  }

  return testResultSize && testResultPointCoordinates;
}

bool testGetNextMultiple() {
  PointCollection *pc = new PointCollection();

  Point *testPoint = new Point(1, 2);
  Point *testPoint2 = new Point(3, 4);

  pc->insert(*testPoint);
  pc->insert(*testPoint2);

  vector<Point> result = pc->getNext(2, 2);
  bool testResultSize = result.size() == 2;

  bool testResultPointCoordinates = false;
  bool testResultPointCoordinates2 = false;
  if(result.size() > 0) {
    vector<float> resultPointCoordinates = result[0].getCoordinates();
    testResultPointCoordinates = resultPointCoordinates[0] == 1 && resultPointCoordinates[1] == 2;

    vector<float> resultPointCoordinates2 = result[1].getCoordinates();
    testResultPointCoordinates2 = resultPointCoordinates2[0] == 3 && resultPointCoordinates2[1] == 4;

    if(!(testResultPointCoordinates && testResultPointCoordinates2)) {
      cout << "testGetNextMultiple: Failed in getting 2 points\n";
      return false;
    }
  }
  return testResultSize && testResultPointCoordinates && testResultPointCoordinates2;
}

bool testGetNextState() {
  PointCollection *pc = new PointCollection();

  Point *testPoint = new Point(1, 2);
  Point *testPoint2 = new Point(3, 4);

  pc->insert(*testPoint);
  pc->insert(*testPoint2);

  vector<Point> result = pc->getNext(1, 3);
  bool testResultPointCoordinates = false;

  if(result.size() > 0) {
    vector<float> resultPointCoordinates = result[0].getCoordinates();
    testResultPointCoordinates = resultPointCoordinates[0] == 1 && resultPointCoordinates[1] == 2;
    if(!testResultPointCoordinates) {
      cout << "testGetNextState: First point retrieval failing\n";
      return false;
    }
  }

  result = pc->getNext(2, 3);
  bool testResultPointCoordinates2 = false;

  if(result.size() > 0) {
    vector<float> resultPointCoordinates2 = result[0].getCoordinates();
    testResultPointCoordinates2 = resultPointCoordinates2[0] == 3 && resultPointCoordinates2[1] == 4;
    if(!testResultPointCoordinates2) {
      cout << "testGetNextState: Second point retrieval failing. State not being maintained\n";
      return false;
    }
  }
  return testResultPointCoordinates && testResultPointCoordinates2;
}

bool testGetNext() {
  bool result = testGetNextSingle() && testGetNextMultiple() && testGetNextState();
  if(result) {
    cout << "\nGetNext passing for all defined test cases\n";
  }
}

int testAddVector() {
  PointCollection *pntCollection;
  Point *pnt1 = new Point(5.5, 6.5);
  Point *pnt2 = new Point(4, 6.7);
  vector<Point> vecpnt = {*pnt1, *pnt2};
  pntCollection = new PointCollection("djdhd","djhdjh", 1, vecpnt);
  return pntCollection->getSize();
}

int callLoadDataBulk() {
  PointCollection *pc1 = new PointCollection();
  PointCollection *pc2 = new PointCollection();
  Point *p = new Point(1.0,1.0);
  Point *q = new Point(2.0,2.0);
  pc1->insert(*p);
  pc1->insert(*q);
  return pc2->insertBulk(*pc1);
}

int callGetSize() {
  PointCollection *pntcollection;
  pntcollection = new PointCollection();

  Point *p1;
  p1 = new Point(12.34, 10.34);

  Point *p2;
  p2 = new Point(12.35, 10.34);
  pntcollection->insert(*p1);
  pntcollection->insert(*p2);

  return pntcollection->getSize();
}

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
    printData(pntcollection);
}

void test_insertDataSortedX() {
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

    cout << pntcollection->insert(*p1);
    cout << pntcollection->insert(*p2);
    cout << pntcollection->insert(*p3);
    cout << pntcollection->insert(*p4);
    cout << pntcollection->getSize();
}

void test_deleteData() {

      PointCollection *pntcollection;
      pntcollection = new PointCollection();

      Point *p1;
      p1 = new Point(12.34, 10.34);

      Point *p2;
      p2 = new Point(12.35, 10.34);

      cout << pntcollection->insert(*p1) << "\n";
      cout << pntcollection->insert(*p2) << "\n";
      cout << pntcollection->getSize() << "\n";

      cout << pntcollection->removeById(1);
      cout << pntcollection->getSize();

}


bool testGetPointByUUID() {
  PointCollection *pntcollection;
  pntcollection = new PointCollection();

  Point *p1;
  p1 = new Point(12.34, 10.34);

  Point *p2;
  p2 = new Point(12.35, 10.34);

  pntcollection->insert(*p1);
  pntcollection->insert(*p2);

  Point * point = pntcollection->getPointByUUID("name", 0);
  vector<float> resultPointCoordinates = point->getCoordinates();

  bool testResultPointCoordinates = (resultPointCoordinates[0] == 12.34f && resultPointCoordinates[1] == 10.34f);
  if(!testResultPointCoordinates) {
    cout << "testGetPointByUUID: Failed getting first point by ID\n";
    return false;
  }

  point = pntcollection->getPointByUUID("name", 1);
  resultPointCoordinates = point->getCoordinates();

  bool testResultPointCoordinates2 = resultPointCoordinates[0] == 12.35f && resultPointCoordinates[1] == 10.34f;
  if(!testResultPointCoordinates2) {
    cout << "testGetPointByUUID: Failed getting second point by ID\n";
    return false;
  }

  return testResultPointCoordinates && testResultPointCoordinates2;
}

void testGetByUUID() {
  bool resultGetPointByUUID = testGetPointByUUID();

  if(resultGetPointByUUID) {
    cout << "\ntestGetByUUID passing for all test cases\n";
  }
}

void test_insertDataSortedY() {
    PointCollection *pntcollection;
    pntcollection = new PointCollection(COLLECTION_STRUCT_SORTEDY);

    Point *p1;
    p1 = new Point(12.34, 10.34);

    Point *p2;
    p2 = new Point(12.35, 10.54);

    Point *p3;
    p3 = new Point(12.36, 1.34);

    Point *p4;
    p4 = new Point(12.37, 4.34);

    pntcollection->insert(*p1);
    pntcollection->insert(*p2);
    pntcollection->insert(*p3);
    pntcollection->insert(*p4);
    cout << "Size: " << pntcollection->getSize() << "/n";
    printData(*pntcollection);
}

int main() {
    loadData("datastore","pointcollection",1,"pointsdata",12);
    PointCollection *pointcollection = Catalog::Instance()->getPointCollectionByName("datastore", "pointcollection");
    vector<Point> vpts =  pointcollection->getNext(pointcollection->getSize());
    for(int i = 0; i < vpts.size(); i++) {
      cout << vpts[i].getCoordinates().at(0) << " : " << vpts[i].getCoordinates().at(1) << endl;
    }
    //return 0;

    //int status;

    //int status;=
    test_insertData();
    //cout<<"Returned status:"<<testAddVector()<<endl;
    //return 0;

    testGetNext();
    testGetByUUID();

  //loadData("data-storage","pointstable",TYPE_POINT, "pointsdata", 1);

}
