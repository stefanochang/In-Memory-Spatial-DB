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


prQuadTree* bulkLoadPrQuadTree(std::string inputFilePath, vector<qPoint*> &pointsToLoad, int leafCapacity = 8){

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

    prQuadTree* prQt = new prQuadTree(qBb, leafCapacity);

    cout<<"\n\t\t Number of Points Inserted = "<<i<<endl;
    for(int i=0;i<pointsToLoad.size();i++) {
        prQt->insert(pointsToLoad[i]);
    }

    fileToLoad.close();

    return prQt;
}


double testprQuadIndividualAverageSearchTime(prQuadTree* prQT,qPoint* pointToSearch)
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

double testprQuadBulkSearchTime(prQuadTree* prQT,vector<qPoint*> pointsToSearch)
{
    double total_search_time = 0;

    for(int i=0; i<pointsToSearch.size(); i++)
    {

        total_search_time += testprQuadIndividualAverageSearchTime(prQT,pointsToSearch[i]);

    }

    return total_search_time;
}

void prQuadTreeBulkDelete(prQuadTree* prQT)
{

    cout<<"\n\t\t prQuad Tree Deletion - Started"<<endl;
    prQT->deleteRoot();
    cout<<"\n\t\t prQuad Tree Deletion - Ended"<<endl;

}



void testprQuadTreeBulkLoad(int leafCapacity = 8) {

    milliseconds start_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    cout << "\n\n prQuadTree Leaf Capacity = "<<leafCapacity<<" Testing - Started" << endl;
    std:: string fileToLoadPath;
    fileToLoadPath = "/Users/ravichandran/Documents/Misc/Docs/ASU_Subjects/Spring_17/ADVDB/Project/Code/In-Memory-Spatial-DB/src/spatial-partitioning-indexing/spatialTests/data/point.csv";
//    fileToLoadPath = "../spatialTests/data/point.csv";

    vector<qPoint*> pointsToSearch;

    prQuadTree* prQT = bulkLoadPrQuadTree(fileToLoadPath,pointsToSearch,leafCapacity);

//    cout<<"\n\n\n";
//    prQT->print();
//    cout<<"\n\n\n";

    milliseconds end_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    milliseconds diff = (end_ms - start_ms);


    cout<<"\n\t\t Insertion Time = "<<std::to_string(diff.count())<<endl;

    double total_search_time = testprQuadBulkSearchTime(prQT,pointsToSearch);

    cout<<"\n\t\t Average Search Time = "<<total_search_time<<endl;

    prQuadTreeBulkDelete(prQT);

    cout << "\n\n prQuadTree Leaf Capacity = "<<leafCapacity<<" Testing - Ended" << endl;
}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASESPRQUADTREEBULKLOAD_H
