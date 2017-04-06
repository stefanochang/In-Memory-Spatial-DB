//
// Created by Darshan Shetty on 19-03-2017.
//

#ifndef IN_MEMORY_SPATIAL_DB_POINTSPATIALINDEX_H
#define IN_MEMORY_SPATIAL_DB_POINTSPATIALINDEX_H

#include "quadTreeLib.h"
#include "prQuadTree.h"
#include "../integration/spatial-index-interface.h"
#include "qPoint.h"
#include "../integration/data-storage.h"

class PointSpatialIndex: public  SpatialIndexInterface {
private:
    prQuadTree *prTree;
    QPoint* convertPoint(Point *p) {
        return new QPoint(p->getCoordinates()[0],p->getCoordinates()[1],p->getId());
    }
public:
    PointSpatialIndex() {}
    PointCollection search(Rectangle bounds){
        PointCollection *result;
        float x1 = bounds.getCoordinates()[0];
        float y1 = bounds.getCoordinates()[1];
        float x2 = bounds.getCoordinates()[2];
        float y2 = bounds.getCoordinates()[3];
        bool xResult = (x1 - x2) > ((fabs(x1) < fabs(x2) ? fabs(x2) : fabs(x1)) * numeric_limits<double>::epsilon());
        float minx = xResult ? x2 : x1;
        bool yResult = (y1 - y2) > ((fabs(y1) < fabs(y2) ? fabs(y2) : fabs(y1)) * numeric_limits<double>::epsilon());
        float miny = yResult ? y2 : y1;
        float width = fabs(x2-x1);
        float height = fabs(y2-y1);
        vector<QPoint>iPoints = prTree->queryRange(minx,miny,width,height);
        Point points[iPoints.size()];
        int i=0;
        for(QPoint point : iPoints) {
            points[i++] = getPointByUUID("Point",point.getId());
        }
        result = new PointCollection(iPoints.size(),points);
        delete points;
        delete iPoints;
        return *result;
    }
    RectangleCollection searchRectangle(Rectangle){
        throw "Method Not Supported";
    }
    void createIndex(PointCollection points){
        prTree = new prQuadTree(5000, 5000);
        Point *p;
        while((p=points.getNext()) != NULL){
            prTree->insert(convertPoint(p));
        }
    }
    void createIndex(RectangleCollection){
        throw "Method Not Supported";
    }
    bool update(PointCollection points){
        bool result = true;
        try {
            prTree->deleteRoot();
            createIndex(points);
        } catch( const char *msg) {
            result = false;
        }
        return result;
    }
    bool update(RectangleCollection,float, float){
        throw "Method Not Supported";
    }
    bool deleteIndex(){
        bool result = true;
        try {

            prTree->deleteRoot();

        } catch(const char *msg){
            result = false;
        }
        return result;
    }
};
#endif //IN_MEMORY_SPATIAL_DB_POINTSPATIALINDEX_H