#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#ifndef DATASTORAGE_H
#include "data-storage.h"
#include "../integration/catalog.h"
#endif
using namespace std;

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
    cout << "GetNext passing for all defined test cases\n";
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

      cout << pntcollection->insert(*p1);
      cout << pntcollection->insert(*p2);
      cout << pntcollection->getSize();

      cout << pntcollection->removeById(1);
      cout << pntcollection->getSize();

}

int main() {
    //loadData("mdd","ddd",1,"ddd",2);
    //return 0;
    //int status;
    //cout<<"Returned status:"<<testAddVector()<<endl;
    //return 0;

    testGetNext();

  //loadData("data-storage","pointstable",TYPE_POINT, "pointsdata", 1);

}
