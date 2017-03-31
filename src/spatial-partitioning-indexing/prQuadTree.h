//
// Created by ravichandran on 18/03/17.
//

#ifndef ADVDBTEST_PRQUADTREE_H
#define ADVDBTEST_PRQUADTREE_H

#include "QuadTreeLib.h"
#include "prQuadNode.h"

class prQuadTree
{

private:
    QPoint XY_POINT;
    QBoundingBox RANGE;

    prQuadNode *root;

public:

    prQuadTree(){}
    prQuadTree(float originX, float originY, float width, float height) {
        float x = originX - width/2;
        float y = originY - height/2;
        QPoint *xyPoint = new QPoint(x,y);
        QBoundingBox *QBB = new QBoundingBox(xyPoint,width,height);
        root = new prQuadNode( *QBB );
    }

    prQuadTree(float width, float height) {
        float x = 0 - width/2;
        float y = 0 - height/2;
        QPoint *xyPoint = new QPoint(x,y);
        QBoundingBox *QBB = new QBoundingBox(xyPoint,width,height);
        root = new prQuadNode( *QBB );
    }

    prQuadNode* getRoot() {
        return root;
    }

    bool insert(QPoint *xyPoint) {

        return (*root).insert(xyPoint);
    }

    bool insert(float x, float y) {
        QPoint *xyPoint = new QPoint(x,y);

        return (*root).insert(xyPoint);
    }

    bool insert(float x, float y, int id) {
        QPoint *xyPoint = new QPoint(x,y,id);

        return (*root).insert(xyPoint);
    }

    void deleteRoot()
    {
        if(root == NULL) return;

        root->deleteNode();

    }


    void print(string prefix = "", bool emptyLine = false)
    {
        if(emptyLine) cout<<endl;
        cout<<prefix<< "Root Node | ";
        if(root!=NULL)
        {
            print(root,"* ",true);
        }


    }

    void print(prQuadNode *node, string prefix = "", bool emptyLine = false)
    {
        if(node!=NULL)
        {
//            if(node->qbb.getMinX()>=0 && node->qbb.getMinY()>=0)
//            {
//                node->print(prefix,true);
//            }
            node->print(prefix,true);

            if(node->prqnNE != NULL && node->prqnNW != NULL && node->prqnSE != NULL && node->prqnSW != NULL)
            {
                prefix += "\t";
                print(node->prqnNW,prefix + " | NW |",true);
                print(node->prqnNE,prefix + " | NE |",true);
                print(node->prqnSW,prefix + " | SW |",true);
                print(node->prqnSE,prefix + " | SE |",true);

            }
        }


    }

    vector<QPoint> queryRange(float x, float y, float width, float height) {
        vector<QPoint> vQPoint;
        if (root == NULL)
            return vQPoint;

        XY_POINT.set(x,y);
        RANGE.set(&XY_POINT,width,height);

        vector<QPoint> pointsInRange;
        root->queryRange(RANGE,pointsInRange);
        return pointsInRange;
    }

};



#endif //ADVDBTEST_PRQUADTREE_H
