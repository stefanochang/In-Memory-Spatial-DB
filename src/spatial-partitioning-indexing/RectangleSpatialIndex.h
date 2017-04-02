//
// Created by Darshan Shetty on 19-03-2017.
//

#ifndef IN_MEMORY_SPATIAL_DB_RECTANGLESPATIALINDEX_H
#define IN_MEMORY_SPATIAL_DB_RECTANGLESPATIALINDEX_H

#include "quadTreeLib.h"
#include "mxcifQuadTree.h"
#include "spatial-index-interface.h"
#include "qPoint.h"
#include "data-storage.h"

class RectangleSpatialIndex: public  SpatialIndexInterface {
private:
    mxcifQuadTree *mxCifTree;
    float* computeBounds(Rectangle *rect) {
        float bounds[4];
        float x1 = rect->getCoordinates()[0];
        float y1 = rect->getCoordinates()[1];
        float x2 = rect->getCoordinates()[2];
        float y2 = rect->getCoordinates()[3];
        bool xResult = (x1 - x2) > ((fabs(x1) < fabs(x2) ? fabs(x2) : fabs(x1)) * numeric_limits<double>::epsilon());
        float minx = xResult ? x2 : x1;
        bool yResult = (y1 - y2) > ((fabs(y1) < fabs(y2) ? fabs(y2) : fabs(y1)) * numeric_limits<double>::epsilon());
        float miny = yResult ? y2 : y1;
        float width = fabs(x2-x1);
        float height = fabs(y2-y1);
        bounds[0]=minx; bounds[1]=miny; bounds[2]=width; bounds[3]=height;
        return bounds;
    }
    QBoundingBox* convertRectangle(Rectangle *r) {
        float minX = r->getCoordinates()[0];
        float minY = r->getCoordinates()[1];
        float maxX = r->getCoordinates()[2];
        float maxY = r->getCoordinates()[3];
        return new QBoundingBox(minX,minY,maxX,maxY,r->getId());
    }
public:
    RectangleSpatialIndex() {}
    PointCollection search(Rectangle){
        throw "Method Not Supported";
    }
    RectangleCollection searchRectangle(Rectangle bounds){
        RectangleCollection *result;
        float *queryBounds = computeBounds(&bounds);
        vector<QBoundingBox> iBoxes = mxCifTree->queryRange(queryBounds[0],queryBounds[1],queryBounds[2],queryBounds[3]);
        Rectangle rectangles[iBoxes.size()];
        int i=0;
        for(QBoundingBox box : iBoxes) {
            rectangles[i++] = getRaectangleByUUID("Rectangle",box.getId());
        }
        result = new RectangleCollection(iBoxes.size(),rectangles);
        delete iBoxes;
        delete rectangles;
        return *result;
    }
    void createIndex(PointCollection){
        throw "Method Not Supported";
    }
    void createIndex(RectangleCollection rectangles){
        //Needs to change after solution is ready
        mxCifTree = new mxcifQuadTree(5000, 5000);
        Rectangle *rect;
        while((rect = rectangles.getNext())!= NULL){
            float *bounds = computeBounds(rect);
            mxCifTree->insert(bounds[0],bounds[1],bounds[2],bounds[3],rect->getId());
//            mxCifTree->insert(convertRectangle(rect));
        }
    }
    bool update(PointCollection){
        throw "Method Not Supported";
    }
    bool update(RectangleCollection rectangles){
        bool result = true;
        try {
            mxCifTree->deleteRoot();
            createIndex(rectangles);
        } catch( const char *msg) {
            result = false;
        }
        return result;
    }
    bool deleteIndex(){
        bool result = true;
        try {

            mxCifTree->deleteRoot();

        } catch(const char *msg){
            result = false;
        }
        return result;
    }
};
#endif //IN_MEMORY_SPATIAL_DB_RECTANGLESPATIALINDEX_H
