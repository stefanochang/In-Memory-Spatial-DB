#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "data-storage.h"

using namespace std;
int callLoadData();
int main()
{
    int status;
    status = callLoadData();
    cout<<"Returned status:"<<status<<endl;
    return 0;
}

int callLoadData()
{
  PointCollection *pntclctn = loadData("data-storage","pointstable",TYPE_POINT, "pointsdata", 1);
  Point pnt = pntclctn->getById(2);
  cout<<pntclctn->getSize();
}
