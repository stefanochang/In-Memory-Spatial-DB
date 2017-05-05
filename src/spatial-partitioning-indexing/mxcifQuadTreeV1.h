//
// Created by ravichandran on 19/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_MXCIFQUADTREEV1_H
#define IN_MEMORY_SPATIAL_DB_MXCIFQUADTREEV1_H

#include "quadTreeLib.h"
#include "mxcifQuadNodeV1.h"

class mxcifQuadTreeV1
{

private:
    qPoint XY_POINT;
    qBoundingBox RANGE;
    mxcifQuadNodeV1 *root;


public:

    mxcifQuadTreeV1(){}
    mxcifQuadTreeV1(float originX, float originY, float width, float height, int leafCapacity)
    {
        float x = originX - width/2;
        float y = originY - height/2;
        qPoint *xyPoint = new qPoint(x,y);
        qBoundingBox *QBB = new qBoundingBox(xyPoint,width,height);
        root = new mxcifQuadNodeV1( *QBB , leafCapacity);
    }

    mxcifQuadTreeV1(float width, float height, int leafCapacity)
    {
        float x = 0 - width/2;
        float y = 0 - height/2;
        qPoint *xyPoint = new qPoint(x,y);
        qBoundingBox *QBB = new qBoundingBox(xyPoint,width,height);
        root = new mxcifQuadNodeV1( *QBB , leafCapacity);
    }

    mxcifQuadTreeV1(qBoundingBox *qbb , int leafCapacity)
    {
        root = new mxcifQuadNodeV1( *qbb , leafCapacity);
    }

    mxcifQuadNodeV1* getRoot() { return root; }


    bool insert(float x, float y, float width, float height) {
        qBoundingBox *QBB = new qBoundingBox(x, y, width, height);
        return (*root).insert(QBB);
    }

    bool insert(float x, float y, float width, float height,int id) {
        qBoundingBox *QBB = new qBoundingBox(x, y, width, height, id);
        return (*root).insert(QBB);
    }

    bool insert(float width, float height)
    {
        float x = 0;
        float y = 0;
        qPoint *xyPoint = new qPoint(x,y);
        qBoundingBox *QBB = new qBoundingBox(xyPoint,width,height);
        return (*root).insert(QBB);
    }

    bool insert(qBoundingBox *QBB)
    {
        return (*root).insert(QBB);
    }

    void deleteRoot()
    {
        if(root == NULL) return;

        root->deleteNode();

        delete this;

    }

    vector<qBoundingBox> queryRange(float x, float y, float width, float height)
    {

        vector<qBoundingBox> vQPoint;
        if (root == NULL)return vQPoint;

        XY_POINT.set(x,y);
        RANGE.set(&XY_POINT,width,height);



        vector<qBoundingBox> rectsInRange;
        root->queryRange(RANGE,rectsInRange);
        return rectsInRange;
    }

    void print(string prefix = "", bool emptyLine = false)
    {
        if(emptyLine) cout<<endl;
        cout<<prefix<< "Root Node | ";
        if(root!=NULL)
        {
            print(root,"*",true);
        }


    }

    void print(mxcifQuadNodeV1 *node, string prefix = "", bool emptyLine = false)
    {
        if(node!=NULL)
        {
//            if(node->qbb.getMinX()>=0 && node->qbb.getMinY()>=0)
//            {
//                node->print(prefix,true);
//            }
            node->print(prefix,true);

            if(node->mxqnNE != NULL && node->mxqnNW != NULL && node->mxqnSE != NULL && node->mxqnSW != NULL)
            {
                prefix += "\t";
                print(node->mxqnNW,prefix + " | NW |",true);
                print(node->mxqnNE,prefix + " | NE |",true);
                print(node->mxqnSW,prefix + " | SW |",true);
                print(node->mxqnSE,prefix + " | SE |",true);

            }
        }


    }

};

#endif //IN_MEMORY_SPATIAL_DB_MXCIFQUADTREEV1_H
