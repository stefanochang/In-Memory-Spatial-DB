//
// Created by ravichandran on 18/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_PRQUADNODE_H
#define IN_MEMORY_SPATIAL_DB_PRQUADNODE_H

#include "quadTreeLib.h"
#include "qBoundingBox.h"

class prQuadNode
{

private:

    int leafCapacity;
//    int maxHeight;
    int height;

protected:

    qBoundingBox qbb;
    vector<qPoint> points;
    vector<prQuadNode*> nodes;


public:


    prQuadNode() {}
    prQuadNode(qBoundingBox QBB, int leafCapacity)
    {
        this->height = 0;
        this->leafCapacity = leafCapacity;
        (*this).qbb = QBB;

    }

    prQuadNode(qBoundingBox QBB, int leafCapacity, int height)
    {
        this->height = height;
        this->leafCapacity = leafCapacity;
        (*this).qbb = QBB;

    }
    prQuadNode(int originX, int originY, float width, float height)
    {
        this->height = 0;
        this->leafCapacity = 4;
        (*this).qbb = *( new qBoundingBox(originX, originY, width, height) );

    }

    prQuadNode* returnNodeAtIndex(int index)
    {
        if ( nodes.size() == 0) return NULL;
        return nodes.at(index);
    }

    prQuadNode* nodeNW()
    {
        return returnNodeAtIndex(0);
    }

    prQuadNode* nodeNE()
    {
        return returnNodeAtIndex(1);
    }

    prQuadNode* nodeSW()
    {
        return returnNodeAtIndex(2);
    }

    prQuadNode* nodeSE()
    {
        return returnNodeAtIndex(3);
    }

    bool isLeaf()
    {
        return ( nodeNW() == NULL && nodeNE() == NULL && nodeSW() == NULL && nodeSE() == NULL);
    }


    bool insert(qPoint *point)
    {

        if ( !qbb.containsPoint(point) ) return false;

//        if (isLeaf() && point->isIn(points) ) return false;

        if (( isLeaf() && points.size() < leafCapacity )  || ( height == 25 ) )
        {
            points.push_back(*point);
            return true;
        }

        if ( isLeaf() && height < 25 )
        {
            subdivide();
        }

        return insertIntoChildren(point);
    }


    bool insertIntoChildren(qPoint *point)
    {

        if (nodeNW()->insert(point)) return true;
        if (nodeNE()->insert(point)) return true;
        if (nodeSW()->insert(point)) return true;
        if (nodeSE()->insert(point)) return true;

    return false;
    }


    void subdivide()
    {
        float h = qbb.getHeight()/2;
        float w = qbb.getWidth()/2;

        float current_x = qbb.getX() + w;
        float current_y = qbb.getY() + h;

        int cur_height = this->height + 1;

        qPoint *pNW = new qPoint(current_x-w,current_y);
        qBoundingBox *qbbNW = new qBoundingBox( pNW, w, h);
        nodes.push_back(new prQuadNode(*qbbNW,leafCapacity,cur_height));


        qPoint *pNE = new qPoint(current_x,current_y);
        qBoundingBox *qbbNE = new qBoundingBox( pNE, w, h);
        nodes.push_back(new prQuadNode(*qbbNE,leafCapacity,cur_height));


        qPoint *pSW = new qPoint(current_x-w,current_y-h);
        qBoundingBox *qbbSW = new qBoundingBox( pSW, w, h);
        nodes.push_back(new prQuadNode(*qbbSW,leafCapacity,cur_height));


        qPoint *pSE = new qPoint(current_x,current_y-h);
        qBoundingBox *qbbSE = new qBoundingBox( pSE, w, h);
        nodes.push_back(new prQuadNode(*qbbSE,leafCapacity,cur_height));


        for (int i=0; i<points.size(); i++)
            insertIntoChildren(&points[i]);

        points.clear();
    }

     void queryRange(qBoundingBox range, vector<qPoint> &pointsInRange) {

        if (!(*this).qbb.intersectsBox(range))
            return;


        if (isLeaf()) {
            for (int i=0; i<points.size(); i++)
            {
                if (range.containsPoint(&points[i]))
                    pointsInRange.push_back(points[i]);
            }
            return;
        }

         this->nodeNW()->queryRange(range,pointsInRange);
         this->nodeNE()->queryRange(range,pointsInRange);
         this->nodeSW()->queryRange(range,pointsInRange);
         this->nodeSE()->queryRange(range,pointsInRange);
    }

    void deleteNode()
    {
        if(this->nodeNW() != NULL){this->nodeNW()->deleteNode();delete this->nodeNW();}
        if(this->nodeNE() != NULL){this->nodeNE()->deleteNode();delete this->nodeNE();}
        if(this->nodeSW() != NULL){this->nodeSW()->deleteNode();delete this->nodeSW();}
        if(this->nodeSE() != NULL){this->nodeSE()->deleteNode();delete this->nodeSE();}

        delete this;

    }

    void pointsPrint()
    {
        cout<<endl;
        for (int i=0; i<points.size(); i++)
            points[i].print("\t\t");
        cout<<endl;
    }



    void print(string prefix = "", bool emptyLine = false)
    {
        if(emptyLine) cout<<endl;
        cout<<prefix<< "prQuadNode | height : "<<this->height<<endl;
        cout<<prefix<< "prQuadNode | ";
        this->qbb.print("\t\t",true);
        cout<<prefix<< "prQuadNode | points -> "<<this->points.size();
        if(points.size()>0)pointsPrint();

    }

};



#endif //IN_MEMORY_SPATIAL_DB_PRQUADNODE_H
