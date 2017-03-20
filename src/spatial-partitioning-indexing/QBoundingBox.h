//
// Created by ravichandran on 18/03/17.
//

#ifndef ADVDBTEST_QBOUNDINGBOX_H
#define ADVDBTEST_QBOUNDINGBOX_H

#include "QuadTreeLib.h"
#include "QPoint.h"

using namespace std;
int qbbID = -333;

class QBoundingBox : public QPoint
{
private:
     float height;
     float width;

     float minX;
     float minY;
     float maxX;
     float maxY;


public:

    QBoundingBox(){}


    QBoundingBox(float width, float height):QPoint(0,0,qbbID)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin(0,0);
        this->setMax(width,height);
    }

    QBoundingBox(int originX, int originY, float width, float height):QPoint(originX,originY,qbbID)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin(originX,originY);
        this->setMax(originX + width,originY + height);

    }

    QBoundingBox(int originX, int originY, float width, float height,int id):QPoint(originX,originY,id)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin(originX,originY);
        this->setMax(originX + width,originY + height);

    }

    QBoundingBox(QPoint *downLeft, float width, float height):QPoint((*downLeft).getX(),(*downLeft).getY(),(*downLeft).getId())
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin((*downLeft).getX(),(*downLeft).getY());
        this->setMax((*downLeft).getX() + width,(*downLeft).getY() + height);
    }


    float getMinX() {
        return minX;
    }

    float getMinY() {
        return minY;
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

    void set(QPoint (*downLeft), float width, float height)
    {
        this->setHeight(height);
        this->setWidth(width);
        this->setMin((*downLeft).getX(),(*downLeft).getY());
        this->setMax((*downLeft).getX() + width,(*downLeft).getY() + height);
    }


    bool containsPoint(QPoint *point) {

        if ( (*point).getX() >= maxX ) return false;
        if ( (*point).getX() < minX ) return false;
        if ( (*point).getY() >= maxY ) return false;
        if ( (*point).getY() < minY ) return false;
        return true;
    }

    bool insideThis(QBoundingBox boundingBox) {
        return ((boundingBox.minX >= minX && boundingBox.maxX <= maxX) && ( boundingBox.minY >= minY && boundingBox.maxY <= maxY));
    }

     bool intersectsBox(QBoundingBox boundingBox) {

        if (insideThis(boundingBox) || boundingBox.insideThis(*this)) return true;

        if (maxX < boundingBox.minX || minX > boundingBox.maxX) return false;
        if (maxY < boundingBox.minY || minY > boundingBox.maxY) return false;

        return true;
    }

    void print(string prefix = "", bool emptyLine = false)
    {
        if(emptyLine)cout<<endl;
        cout<<prefix<< "QBoundingBox : QPoint | X : "<<this->getX()<<" | Y : "<<this->getY()<<" | ID : "<<this->getId()<<endl;
        cout<<prefix<< "QBoundingBox | Height : "<<this->getHeight()<<" | Width : "<<this->getWidth()<<endl;
        cout<<prefix<< "QBoundingBox | minX : "<<this->minX<<" | minY : "<<this->minY<<endl;
        cout<<prefix<< "QBoundingBox | maxX : "<<this->maxX<<" | maxY : "<<this->maxY<<endl;
    }

};

#endif //ADVDBTEST_QBOUNDINGBOX_H
