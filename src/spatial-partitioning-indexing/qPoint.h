//
// Created by ravichandran on 17/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_QPOINT_H
#define IN_MEMORY_SPATIAL_DB_QPOINT_H


#include "quadTreeLib.h"

using namespace std;


int qpID = -333;

class qPoint {
    float x;
    float y;
    int id;
public:
    qPoint() {}
    qPoint(float x, float y)
    {   this->set(x,y);
        this->setId(qpID);
    }
    qPoint(float x, float y, int id)
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

    bool isIn(vector<qPoint> points)
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


#endif //IN_MEMORY_SPATIAL_DB_QPOINT_H