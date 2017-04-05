#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "data-storage.h"

using namespace std;

bool testGetNextSingle() {
  PointCollection *pc = new PointCollection();

  Point *testPoint = new Point(1, 2);

  pc->insert(*testPoint);

  vector<Point> result = pc->getNext(1, 1);
  bool testResultSize = result.size() == 1;

  vector<float> resultPointCoordinates = result[0].getCoordinates();
  bool testResultPointCoordinates = resultPointCoordinates[0] == 1 && resultPointCoordinates[1] == 2;

  return testResultSize; // && testResultPointCoordinates;
}

bool testGetNextMultiple() {
  PointCollection *pc = new PointCollection();

  Point *testPoint = new Point(1, 2);
  Point *testPoint2 = new Point(3, 4);

  pc->insert(*testPoint);
  pc->insert(*testPoint2);

  vector<Point> result = pc->getNext(2, 1);
  bool testResultSize = result.size() == 2;

  vector<float> resultPointCoordinates = result[0].getCoordinates();
  bool testResultPointCoordinates = resultPointCoordinates[0] == 1 && resultPointCoordinates[1] == 2;

  vector<float> resultPointCoordinates2 = result[1].getCoordinates();
  bool testResultPointCoordinates2 = resultPointCoordinates2[0] == 3 && resultPointCoordinates2[1] == 4;

  return testResultSize && testResultPointCoordinates && testResultPointCoordinates2;
}

bool testGetNext() {
  return testGetNextSingle() && testGetNextMultiple();
}

int main()
{
    //loadData("mdd","ddd",1,"ddd",2);
    //return 0;

    cout << "Result for getNext: " << testGetNext();
}
