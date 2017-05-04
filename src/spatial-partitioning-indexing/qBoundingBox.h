//
// Created by ravichandran on 18/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_QBOUNDINGBOX_H
#define IN_MEMORY_SPATIAL_DB_QBOUNDINGBOX_H

#include "quadTreeLib.h"
#include "qPoint.h"

using namespace std;
int qbbID = -333;

class qBoundingBox : public qPoint
{
private:
     float height;
     float width;

     float minX;
     float minY;
     float maxX;
     float maxY;


public:

    qBoundingBox():qPoint(0,0,qbbID){}
    qBoundingBox(int id):qPoint(0,0,id){}


    qBoundingBox(float width, float height):qPoint(0,0,qbbID)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin(0,0);
        this->setMax(width,height);
    }

    qBoundingBox(int originX, int originY, float width, float height):qPoint(originX,originY,qbbID)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin(originX,originY);
        this->setMax(originX + width,originY + height);

    }

    qBoundingBox(int originX, int originY, float width, float height,int id):qPoint(originX,originY,id)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin(originX,originY);
        this->setMax(originX + width,originY + height);

    }

    qBoundingBox(qPoint *downLeft, float width, float height):qPoint((*downLeft).getX(),(*downLeft).getY(),(*downLeft).getId())
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin((*downLeft).getX(),(*downLeft).getY());
        this->setMax((*downLeft).getX() + width,(*downLeft).getY() + height);
    }

    qBoundingBox(float minX,float minY,float maxX,float maxY,int id):qPoint(minX,minY,id)
    {
        int curHeight = (int)(maxY - minY);
        int curWidth = (int)(maxX - minX);

        this->setHeight(curHeight);
        this->setWidth(curWidth);
        this->setMin(minX,minY);
        this->setMax(maxX,maxY);

    }



    float getMinX() {
        return minX;
    }

    float getMinY() {
        return minY;
    }


    float getMaxX() {
        return maxX;
    }

    float getMaxY() {
        return maxY;
    }


    void setHeight(float height)
    {
        this->height = height;
    }

    float getHeight() {
        return height;
    }

    void setWidth(float width)
    {
        this->width = width;
    }

    float getWidth() {
        return width;
    }

    void setMin(float x, float y )
    {
        this->minX = x;
        this->minY = y;
    }

    void setMax(float x, float y )
    {
        this->maxX = x;
        this->maxY = y;
    }

    void set(float width, float height)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMax(this->minX+ width,this->minY + height);
    }

    void set(int originX, int originY, float width, float height)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin(originX,originY);
        this->setMax(originX + width,originY + height);
    }

    void set(qPoint (*downLeft), float width, float height)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin((*downLeft).getX(),(*downLeft).getY());
        this->setMax((*downLeft).getX() + width,(*downLeft).getY() + height);
    }


    bool containsPoint(qPoint *point) {

        if ( (*point).getX() >= maxX ) return false;
        if ( (*point).getX() < minX ) return false;
        if ( (*point).getY() >= maxY ) return false;
        if ( (*point).getY() < minY ) return false;
        return true;
    }

    bool insideThis(qBoundingBox boundingBox) {
        return ((boundingBox.minX >= minX && boundingBox.maxX <= maxX) && ( boundingBox.minY >= minY && boundingBox.maxY <= maxY));
    }

    bool canContain(qBoundingBox box) {
        return ((box.minX >= this->minX && box.maxX <= this->maxX) && ( box.minY >= this->minY && box.maxY <= this->maxY));
    }

    bool intersectsBox(qBoundingBox boundingBox) {

        if (insideThis(boundingBox) || boundingBox.insideThis(*this)) return true;

        if (maxX < boundingBox.minX || minX > boundingBox.maxX) return false;
        if (maxY < boundingBox.minY || minY > boundingBox.maxY) return false;

        return true;
    }

    static bool equals(qBoundingBox qbb1,qBoundingBox qbb2)
    {
      if( ((qbb1.minX == qbb2.minX) && (qbb1.minY && qbb2.minY)) && ((qbb1.maxX == qbb2.maxX) && (qbb1.maxY && qbb2.maxY)) ) return true;

        return false;
    }

    bool isIn(vector<qBoundingBox> rectangles)
    {
        for(int i=0; i<rectangles.size();i++) {
            if (equals((*this),rectangles[i]))
                return true;
        }
        return false;
    }

    static qBoundingBox* getQBoundingBoxCooridinates(vector<qPoint*> qPoints)
    {
        if (qPoints.empty()) return NULL;
        float minX,maxX,minY,maxY,currentX,currentY,finalX,finalY; int i;
        minX = (*qPoints[0]).getX();
        minY = (*qPoints[0]).getY();
        maxX = (*qPoints[0]).getX();
        maxY = (*qPoints[0]).getY();

        for(i=0;i< qPoints.size();i++){
            currentX = (*qPoints[i]).getX();
            currentY = (*qPoints[i]).getY();
            if(currentX <= minX){
                minX = currentX;
            }else if (currentX >= maxX){
                maxX = currentX;
            }

            if(currentY <= minY){
                minY = currentY;
            }else if(currentY >= maxY){
                maxY = currentY;
            }
        }


        finalX = max(fabs(round(minX)),fabs(round(maxX)));
        finalY = max(fabs(round(minY)),fabs(round(maxY)));


        finalX += finalX/2;
        finalY += finalY/2;


        float finalWidth = finalX*2;
        float finalHeight = finalY*2;
        int originX = 0 - (int)finalX;
        int originY = 0 - (int)finalY;

        return new qBoundingBox(originX,originY,finalWidth,finalHeight);

    }

    static qBoundingBox* getQBoundingBoxCooridinates(vector<qBoundingBox*> qBBoxes)
    {
        if (qBBoxes.empty()) return NULL;
        float minX,maxX,minY,maxY,currentX,currentY,finalX,finalY; int i;
        minX = (*qBBoxes[0]).getMinX();
        minY = (*qBBoxes[0]).getMinY();
        maxX = (*qBBoxes[0]).getMaxX();
        maxY = (*qBBoxes[0]).getMaxY();

        for(i=0;i< qBBoxes.size();i++){
            currentX = (*qBBoxes[i]).getMinX();
            currentY = (*qBBoxes[i]).getMinY();
            if(currentX <= minX){
                minX = currentX;
            }

            if(currentY <= minY){
                minY = currentY;
            }

            currentX = (*qBBoxes[i]).getMaxX();
            currentY = (*qBBoxes[i]).getMaxY();

            if (currentX >= maxX){
                maxX = currentX;
            }

            if(currentY >= maxY){
                maxY = currentY;
            }
        }


        finalX = max(fabs(round(minX)),fabs(round(maxX)));
        finalY = max(fabs(round(minY)),fabs(round(maxY)));


        finalX += finalX/2;
        finalY += finalY/2;

//        finalX += finalX;
//        finalY += finalY;


        float finalWidth = finalX*2;
        float finalHeight = finalY*2;
        int originX = 0 - (int)finalX;
        int originY = 0 - (int)finalY;

        return new qBoundingBox(originX,originY,finalWidth,finalHeight);

    }

    static qBoundingBox* createRectangle(float minX,float minY,float maxX,float maxY)
    {

        qBoundingBox* qbb = new qBoundingBox(qbbID);

        float curHeight = (maxY - minY);
        float curWidth = (maxX - minX);

        qbb->setHeight(curHeight);
        qbb->setWidth(curWidth);
        qbb->setMin(minX,minY);
        qbb->setMax(maxX,maxY);

        return qbb;

    }

    static qBoundingBox* createRectangle(float minX,float minY,float maxX,float maxY,int id)
    {

        qBoundingBox* qbb = new qBoundingBox(id);

        float curHeight = (maxY - minY);
        float curWidth = (maxX - minX);

        qbb->setHeight(curHeight);
        qbb->setWidth(curWidth);
        qbb->setMin(minX,minY);
        qbb->setMax(maxX,maxY);

        return qbb;

    }


    void print(string prefix = "", bool emptyLine = false)
    {
        if(emptyLine)cout<<endl;
//        cout<<prefix<< "qBoundingBox : qPoint | X : "<<this->getX()<<" | Y : "<<this->getY()<<" | ID : "<<this->getId()<<endl;

        cout<<prefix<< "qBoundingBox | minX : "<<this->minX<<" | minY : "<<this->minY<<endl;
        cout<<prefix<< "qBoundingBox | maxX : "<<this->maxX<<" | maxY : "<<this->maxY<<endl;
        cout<<prefix<< "qBoundingBox | ID :"<<this->getId()<<" | Height : "<<this->getHeight()<<" | Width : "<<this->getWidth()<<endl;
    }

};

#endif //IN_MEMORY_SPATIAL_DB_QBOUNDINGBOX_H
