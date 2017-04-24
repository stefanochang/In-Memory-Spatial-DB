//
// Created by Prince Chawla on 4/5/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_TESTCASESPRQUADTREEBULKLOAD_H
#define IN_MEMORY_SPATIAL_DB_TESTCASESPRQUADTREEBULKLOAD_H

#include "../quadTreeLib.h"
#include "../qPoint.h"
#include "../prQuadTree.h"
#include "../prQuadNode.h"
#include "../qBoundingBox.h"

#include <sstream>
#include <fstream>
#include <cstring>


using namespace std;


prQuadTree* bulkLoadPrQuadTree(std::string inputFilePath, int leafCapacity = 4){

    vector<qPoint*> pointsToLoad;
    qBoundingBox* qBb;
    float height, width;
    float originX, originY = 0.0;

    ifstream fileToLoad (inputFilePath);
    string line;

    float val = 0.0;
    int i = 0;

    if ( fileToLoad.is_open() ) {
        while (getline(fileToLoad, line)) {
            stringstream ss(line);
            qPoint* temp = new qPoint();
            vector<float> vect;
            while (ss >> val) {
                vect.push_back(val);
                if (ss.peek() == ',')
                    ss.ignore();
            }
            temp->set(vect.at(0),vect.at(1),i);
            pointsToLoad.push_back( new qPoint(vect.at(0),vect.at(1),i));
//            prQt->insert(temp);
            i++;
        }
        qBb = qBoundingBox::getQBoundingBoxCooridinates(pointsToLoad);
        height = qBb->getHeight();
        width = qBb->getWidth();


    }

    prQuadTree* prQt = new prQuadTree(qBb, leafCapacity);

    cout<<"\t\t Size of points = "<<i<<endl;
    for(int i=0;i<pointsToLoad.size();i++) {
        prQt->insert(pointsToLoad[i]);
    }

    fileToLoad.close();

    return prQt;
}


void testprQuadTreeBulkLoad(int leafCapacity = 8) {


    cout << "\n\n prQuadTree Leaf Capacity = "<<leafCapacity<<" Testing - Started" << endl;
    std:: string fileToLoadPath;
//    fileToLoadPath = "../spatialTests/data/point.csv";
    fileToLoadPath = "data/point.csv";
    prQuadTree* prQT = bulkLoadPrQuadTree(fileToLoadPath,leafCapacity);
    int sizeOfprQT = sizeof(prQT);
    cout << "\t\t prQuadTree size = "<<sizeOfprQT<< endl;

    cout << "\n\n prQuadTree Leaf Capacity = "<<leafCapacity<<" Testing - Ended" << endl;
}



#endif //IN_MEMORY_SPATIAL_DB_TESTCASESPRQUADTREEBULKLOAD_H
