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

using namespace std::chrono;


prQuadTree* bulkLoadPrQuadTree(std::string inputFilePath, int leafCapacity = 8){

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

    cout<<"\n\t\t Size of Points Inserted= "<<i<<endl;
    for(int i=0;i<pointsToLoad.size();i++) {
        prQt->insert(pointsToLoad[i]);
    }

    fileToLoad.close();

    return prQt;
}


void testprQuadTreeBulkLoad(int leafCapacity = 8) {

    milliseconds start_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    cout << "\n\n prQuadTree Leaf Capacity = "<<leafCapacity<<" Testing - Started" << endl;
    std:: string fileToLoadPath;
    fileToLoadPath = "/Users/ravichandran/Documents/Misc/Docs/ASU_Subjects/Spring_17/ADVDB/Project/Code/In-Memory-Spatial-DB/src/spatial-partitioning-indexing/spatialTests/data/point.csv";
//    fileToLoadPath = "data/point.csv";
    prQuadTree* prQT = bulkLoadPrQuadTree(fileToLoadPath,leafCapacity);


    milliseconds end_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    milliseconds diff = (end_ms - start_ms);
    cout<<"\n\t\t Insertion Time = "<<std::to_string(diff.count())<<endl;

    cout << "\n\n prQuadTree Leaf Capacity = "<<leafCapacity<<" Testing - Ended" << endl;
}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASESPRQUADTREEBULKLOAD_H
