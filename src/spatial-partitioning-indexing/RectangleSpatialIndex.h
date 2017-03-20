//
// Created by Darshan Shetty on 19-03-2017.
//

#ifndef ADVDBTEST_RECTANGLESPATIALINDEX_H
#define ADVDBTEST_RECTANGLESPATIALINDEX_H
#include <math.h>
#include <limits>
#include "mxcifQuadTree.h"
#include "spatial-index-interface.h"
#include "QPoint.h"
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
        float miny = xResult ? y2 : y1;
        float width = fabs(x2-x1);
        float height = fabs(y2-y1);
        bounds[0]=minx; bounds[1]=miny; bounds[2]=width; bounds[3]=height;
        return bounds;
    }
public:
    RectangleSpatialIndex() {}
    vector<Point> search(Rectangle){
        throw "Method Not Supported";
    }
    vector<Rectangle> searchRectangle(Rectangle bounds){
        vector<Rectangle>result;
        float *queryBounds = computeBounds(&bounds);
        vector<QBoundingBox> iBoxes = mxCifTree->queryRange(queryBounds[0],queryBounds[1],queryBounds[2],queryBounds[3]);
        for(QBoundingBox box : iBoxes) {
            result.push_back(getRaectangleByUUID("Rectangle",box.getId()));
        }
        return result;
    }
    void createIndex(PointCollection, float, float){
        throw "Method Not Supported";
    }
    void createIndex(RectangleCollection rectangles, float width, float height){
        mxCifTree = new mxcifQuadTree(width, height);
        Rectangle *rect;
        while((rect = rectangles.getNext())!= NULL){
            float *bounds = computeBounds(rect);
            mxCifTree->insert(bounds[0],bounds[1],bounds[2],bounds[3],rect->getId());
        }
    }
    bool update(PointCollection,float, float){
        throw "Method Not Supported";
    }
    bool update(RectangleCollection rectangles,float width, float height){
        bool result = true;
        try {
            //Call MX CIF Tree delete here
            createIndex(rectangles,width,height);
        } catch( const char *msg) {
            result = false;
        }
        return result;
    }
    bool deleteIndex(){
        //Call MX CIF delete here
    }
};
#endif //ADVDBTEST_RECTANGLESPATIALINDEX_H
