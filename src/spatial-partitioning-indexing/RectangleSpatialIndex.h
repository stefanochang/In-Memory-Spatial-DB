//
// Created by Darshan Shetty on 19-03-2017.
//

#ifndef IN_MEMORY_SPATIAL_DB_RECTANGLESPATIALINDEX_H
#define IN_MEMORY_SPATIAL_DB_RECTANGLESPATIALINDEX_H

#include "quadTreeLib.h"
#include "mxcifQuadTree.h"
#include "../integration/spatial-index-interface.h"
#include "../data-storage/ds_constants.h"
#include "qPoint.h"
#include "../integration/data-storage.h"

class RectangleSpatialIndex: public  SpatialIndexInterface {
private:
    mxcifQuadTree *mxCifTree;
    float* computeBounds(Rectangle rect) {
        float bounds[4];
        float x1 = rect.getCoordinates()[0];
        float y1 = rect.getCoordinates()[1];
        float x2 = rect.getCoordinates()[2];
        float y2 = rect.getCoordinates()[3];
        bool xResult = (x1 - x2) > ((fabs(x1) < fabs(x2) ? fabs(x2) : fabs(x1)) * numeric_limits<double>::epsilon());
        float minx = xResult ? x2 : x1;
        bool yResult = (y1 - y2) > ((fabs(y1) < fabs(y2) ? fabs(y2) : fabs(y1)) * numeric_limits<double>::epsilon());
        float miny = yResult ? y2 : y1;
        float width = fabs(x2-x1);
        float height = fabs(y2-y1);
        bounds[0]=minx; bounds[1]=miny; bounds[2]=width; bounds[3]=height;
        return bounds;
    }
    qBoundingBox* convertRectangle(Rectangle r) {
        float minX = r.getCoordinates()[0];
        float minY = r.getCoordinates()[1];
        float maxX = r.getCoordinates()[2];
        float maxY = r.getCoordinates()[3];
        return new qBoundingBox(minX,minY,maxX,maxY,r.getId());
    }
public:
    RectangleSpatialIndex() {}
    PointCollection search(Rectangle,PointCollection){
        throw "Method Not Supported";
    }
    RectangleCollection search(Rectangle bounds,RectangleCollection rectangleCollection){
        RectangleCollection *result;
        float *queryBounds = computeBounds(bounds);
        vector<qBoundingBox> iBoxes = mxCifTree->queryRange(queryBounds[0],queryBounds[1],queryBounds[2],queryBounds[3]);
        vector<Rectangle> rectangles;
        int i=0;
        for(qBoundingBox box : iBoxes) {
            rectangles.push_back(rectangleCollection.getById(box.getId()));
        }
        result = new RectangleCollection("RectangleCollection","Rectangle",TYPE_RECTANGLE,rectangles);
        delete iBoxes;
        delete rectangles;
        return *result;
    }
    void createIndex(PointCollection){
        throw "Method Not Supported";
    }
    void createIndex(RectangleCollection rectangles){
        //Needs to change after solution is ready
        vector<Rectangle> allRectangles = rectangles.getNext(rectangles.getSize());
        vector<qBoundingBox*> qRectangles;
        for (std::vector<Rectangle>::iterator rectangle = allRectangles.begin() ; rectangle != allRectangles.end(); ++rectangle){
            qRectangles.push_back(convertRectangle(*rectangle));
        }
        qBoundingBox *box = qBoundingBox::getQBoundingBoxCooridinates(qRectangles);
        mxCifTree = new mxcifQuadTree(box);
        vector<Rectangle> rectangleVector = rectangles.getNext();
        for (std::vector<Rectangle>::iterator rect = rectangleVector.begin() ; rect != rectangleVector.end(); ++rect){
            float *bounds = computeBounds(*rect);
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
