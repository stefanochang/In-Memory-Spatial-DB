//
// Created by Prince Chawla on 4/5/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_TESTCASESMXCIFQUADTREEBULKLOAD_H
#define IN_MEMORY_SPATIAL_DB_TESTCASESMXCIFQUADTREEBULKLOAD_H

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


mxcifQuadTree* bulkLoadmxcifQuadTree(std::string inputFilePath, vector<qBoundingBox*> &rectsToLoad, int leafCapacity = 8){

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

            vector<float> vect;
            while (ss >> val) {
                vect.push_back(val);
                if (ss.peek() == ',')
                    ss.ignore();
            }
            qBoundingBox* temp = qBoundingBox::createRectangle(vect.at(0),vect.at(1),vect.at(2),vect.at(3),i);

            rectsToLoad.push_back( temp);
            i++;
        }
        qBb = qBoundingBox::getQBoundingBoxCooridinates(rectsToLoad);
        height = qBb->getHeight();
        width = qBb->getWidth();

    }

    mxcifQuadTree* mxcifQt = new mxcifQuadTree(qBb, leafCapacity);

    cout<<"\n\t\t Number of Rectangles Inserted = "<<i<<endl;
    for(int i=0;i<rectsToLoad.size();i++) {
//        cout<<"i = "<<i<<endl;
//        rectsToLoad[i]->print("\t\t");
        mxcifQt->insert(rectsToLoad[i]);
    }

    fileToLoad.close();

    return mxcifQt;
}


double testmxcifQuadIndividualAverageSearchTime(mxcifQuadTree* mxcifQT, qBoundingBox* rectToSearch)
{
    double total_time = 0.0;

    for(int i=0; i<=2; i++)
    {
        milliseconds start_ms = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch()
        );


//        mxcifQT->queryRange(rectToSearch->getMinX()-0.0001, rectToSearch->getMinY()-0.0001, rectToSearch->getWidth() - 0.0002, rectToSearch->getHeight() - 0.0002);

        mxcifQT->queryRange(rectToSearch->getMinX(), rectToSearch->getMinY(), rectToSearch->getWidth(), rectToSearch->getHeight());

        milliseconds end_ms = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch()
        );

        milliseconds diff = (end_ms - start_ms);

        total_time += diff.count();

    }

    total_time /= 3;

    return total_time;

}

double testmxCifQuadBulkSearchTime(mxcifQuadTree* mxcifQT,vector<qBoundingBox*> rectsToSearch)
{
    double total_search_time = 0;

    for(int i=0; i<rectsToSearch.size(); i++)
    {

        total_search_time += testmxcifQuadIndividualAverageSearchTime(mxcifQT,rectsToSearch[i]);

    }

    return total_search_time;
}

void mxcifQuadTreeBulkDelete(mxcifQuadTree* mxcifQT)
{

    cout<<"\n\t\t mxcifQuad Tree Deletion - Started"<<endl;
    mxcifQT->deleteRoot();
    cout<<"\n\t\t mxcifQuad Tree Deletion - Ended"<<endl;

}



void testmxcifQuadTreeBulkLoad(int leafCapacity = 8) {

    milliseconds start_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    cout << "\n\n mxcifQuadTree Leaf Capacity = "<<leafCapacity<<" Testing - Started" << endl;
    std:: string fileToLoadPath;
    fileToLoadPath = "/Users/ravichandran/Documents/Misc/Docs/ASU_Subjects/Spring_17/ADVDB/Project/Code/In-Memory-Spatial-DB/src/spatial-partitioning-indexing/spatialTests/data/rectangle.csv";
//    fileToLoadPath = "../spatialTests/data/point.csv";

    vector<qBoundingBox*> rectsToSearch;

    mxcifQuadTree* mxcifQT = bulkLoadmxcifQuadTree(fileToLoadPath,rectsToSearch,leafCapacity);

//    cout<<"\n\n\n";
//    mxcifQT->print();
//    cout<<"\n\n\n";

    milliseconds end_ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    milliseconds diff = (end_ms - start_ms);


    cout<<"\n\t\t Insertion Time = "<<std::to_string(diff.count())<<endl;

    double total_search_time = testmxCifQuadBulkSearchTime(mxcifQT,rectsToSearch);

    cout<<"\n\t\t Average Search Time = "<<total_search_time<<endl;

//    mxcifQuadTreeBulkDelete(mxcifQT);

    cout << "\n\n mxcifQuadTree Leaf Capacity = "<<leafCapacity<<" Testing - Ended" << endl;
}


#endif //IN_MEMORY_SPATIAL_DB_TESTCASESMXCIFQUADTREEBULKLOAD_H
