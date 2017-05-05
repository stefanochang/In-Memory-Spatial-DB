//
// Created by Prince Chawla on 4/5/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_TESTCASESPRQUADTREEV1BULKLOAD_H
#define IN_MEMORY_SPATIAL_DB_TESTCASESPRQUADTREEV1BULKLOAD_H

#include "../quadTreeLib.h"
#include "../qPoint.h"
#include "../prQuadTreeV1.h"
#include "../prQuadNodeV1.h"
#include "../qBoundingBox.h"

#include <sstream>
#include <fstream>
#include <cstring>


using namespace std;

using namespace std::chrono;


prQuadTreeV1* bulkLoadPrQuadTreeV1(std::string inputFilePath, vector<qPoint*> &pointsToLoad, int leafCapacity = 8){

//    vector<qPoint*> pointsToLoad;
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

    prQuadTreeV1* prQt = new prQuadTreeV1(qBb, leafCapacity);

    cout<<"\n\t\t Number of Points Inserted = "<<i<<endl;
    for(int i=0;i<pointsToLoad.size();i++) {
        prQt->insert(pointsToLoad[i]);
    }

    fileToLoad.close();

    return prQt;
}


double testprQuadTreeV1IndividualAverageSearchTime(prQuadTreeV1* prQT,qPoint* pointToSearch)
{
    double total_time = 0.0;

    for(int i=0; i<=2; i++)
    {
        milliseconds start_ms = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch()
        );


        prQT->queryRange(pointToSearch->getX()-0.0001, pointToSearch->getY()-0.0001, 0.0002, 0.0002);

        milliseconds end_ms = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch()
        );

        milliseconds diff = (end_ms - start_ms);

        total_time += diff.count();

    }

    total_time /= 3;

    return total_time;

}

double testprQuadTreeV1BulkSearchTime(prQuadTreeV1* prQT,vector<qPoint*> pointsToSearch)
{
    double total_search_time = 0;

    for(int i=0; i<pointsToSearch.size(); i++)
    {

        total_search_time += testprQuadTreeV1IndividualAverageSearchTime(prQT,pointsToSearch[i]);

    }

    return total_search_time;
}

void prQuadTreeV1BulkDelete(prQuadTreeV1* prQT)
{

    cout<<"\n\t\t prQuad Tree Deletion - Started"<<endl;
    prQT->deleteRoot();
    cout<<"\n\t\t prQuad Tree Deletion - Ended"<<endl;

}



void testprQuadTreeV1BulkLoad(int leafCapacity = 8) {

    milliseconds start_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    cout << "\n\n prQuadTreeV1 Leaf Capacity = "<<leafCapacity<<" Testing - Started" << endl;
    std:: string fileToLoadPath;
    fileToLoadPath = "/Users/ravichandran/Documents/Misc/Docs/ASU_Subjects/Spring_17/ADVDB/Project/Code/In-Memory-Spatial-DB/src/spatial-partitioning-indexing/spatialTests/data/point.csv";
//    fileToLoadPath = "../spatialTests/data/point.csv";

    vector<qPoint*> pointsToSearch;

    prQuadTreeV1* prQT = bulkLoadPrQuadTreeV1(fileToLoadPath,pointsToSearch,leafCapacity);

//    cout<<"\n\n\n";
//    prQT->print();
//    cout<<"\n\n\n";

    milliseconds end_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    milliseconds diff = (end_ms - start_ms);


    cout<<"\n\t\t Insertion Time = "<<std::to_string(diff.count())<<endl;

    double total_search_time = testprQuadTreeV1BulkSearchTime(prQT,pointsToSearch);

    cout<<"\n\t\t Average Search Time = "<<total_search_time<<endl;

//    prQuadTreeV1BulkDelete(prQT);

    cout << "\n\n prQuadTreeV1 Leaf Capacity = "<<leafCapacity<<" Testing - Ended" << endl;
}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASESPRQUADTREEV1BULKLOAD_H
