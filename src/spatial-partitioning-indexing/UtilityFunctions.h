//
// Created by ravichandran on 19/03/17.
//

#ifndef ADVDBTEST_UTILITYFUNCTIONS_H
#define ADVDBTEST_UTILITYFUNCTIONS_H

#include "QuadTreeLib.h"
#include "QPoint.h"

using namespace std;

void printQPointVectors(vector<QPoint> qP)
{
    for(int i=0;i< qP.size();i++) {
        qP[i].print();
    }
}


#endif //ADVDBTEST_UTILITYFUNCTIONS_H
