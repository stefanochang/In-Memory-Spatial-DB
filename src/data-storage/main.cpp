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
  return loadData("data-storage","pointstable",TYPE_POINT, "pointsdata", 1);
}
