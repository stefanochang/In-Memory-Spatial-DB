//
// Created by ravichandran on 17/03/17.
//

#ifndef ADVDBTEST_QPOINT_H
#define ADVDBTEST_QPOINT_H

#include "QuadTreeLib.h"

using namespace std;

int qpID = -333;

class QPoint {
    float x;
    float y;
    int id;
public:
    QPoint() {}
    QPoint(float x, float y)
    {   this->set(x,y);
        this->setId(qpID);
    }
    QPoint(float x, float y, int id)
    {   this->set(x,y);
        this->setId(id);
    }

    void setId(int id){
        this->id = id;
    }

    void setX(float x){
        this->x = x;
    }

    void setY(float y){
        this->y = y;
    }

    virtual void set(float x,float y)
    {
        this->setX(x);
        this->setY(y);
    }

    virtual void set(float x,float y,int id)
    {
        this->set(x,y);
        this->setId(id);
    }

    float getX()
    {
        return x;
    }

    float getY()
    {
        return y;
    }

    int getId()
    {
        return id;
    }

    bool isIn(vector<QPoint> points)
    {
        for(int i=0; i<points.size();i++) {
            if (points[i].x == this->x && points[i].y == this->y)
                return true;
        }
        return false;
    }

    void print(string prefix = "", bool emptyLine = false)
    {
        if(emptyLine)cout<<endl;
        cout<<prefix<< "Point | X : "<<this->getX()<<" | Y : "<<this->getY()<<" | ID : "<<this->getId()<<endl;
    }
};


#endif //ADVDBTEST_QPOINT_H