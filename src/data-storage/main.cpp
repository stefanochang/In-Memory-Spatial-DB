#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "data-storage.h"

using namespace std;
int callLoadData();
int callGetSize();
int main()
{
  int status;
  cout<<"Returned status:"<<callGetSize()<<endl;
  return 0;
}

int callLoadData()
{
  loadData("data-storage","pointstable",TYPE_POINT, "pointsdata", 1);
}

int callGetSize()
{
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
