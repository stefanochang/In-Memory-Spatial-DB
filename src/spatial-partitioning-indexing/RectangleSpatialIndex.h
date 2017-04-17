//
// Created by Darshan Shetty on 19-03-2017.
//

#ifndef IN_MEMORY_SPATIAL_DB_RECTANGLESPATIALINDEX_H
#define IN_MEMORY_SPATIAL_DB_RECTANGLESPATIALINDEX_H

#include "quadTreeLib.h"
#include "mxcifQuadTree.h"
#include "../integration/spatial-index-interface.h"
#include "qPoint.h"

class RectangleSpatialIndex: public  SpatialIndexInterface {
private:
    mxcifQuadTree *mxCifTree;
    vector<float> computeBounds(Rectangle rect) {
        vector<float> bounds;
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
        bounds.push_back(minx); bounds.push_back(miny); bounds.push_back(width); bounds.push_back(height);
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
    PointCollection searchPoint(Rectangle,PointCollection*){
        throw "Method Not Supported";
    }
    RectangleCollection searchRectangle(Rectangle bounds,RectangleCollection *rectangleCollection){
        RectangleCollection *result;
        vector<float> queryBounds = computeBounds(bounds);
        vector<qBoundingBox> iBoxes = mxCifTree->queryRange(queryBounds.at(0),queryBounds.at(1),queryBounds.at(2),queryBounds.at(3));
        vector<Rectangle> rectangles;
        int i=0;
        for(qBoundingBox box : iBoxes) {
            rectangles.push_back(rectangleCollection->getById(box.getId()));
        }
        result = new RectangleCollection("RectangleCollection","Rectangle",TYPE_RECTANGLE,rectangles);
        if(!iBoxes.empty()){
            iBoxes.clear();
        }
        if(!rectangles.empty()){
            rectangles.clear();
        }
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
            vector<float> bounds = computeBounds(*rect);
            mxCifTree->insert(bounds.at(0),bounds.at(1),bounds.at(2),bounds.at(3),rect->getId());
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
