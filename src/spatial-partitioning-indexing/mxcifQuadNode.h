//
// Created by ravichandran on 19/03/17.
//

#ifndef ADVDBTEST_MXCIFQUADNODE_H
#define ADVDBTEST_MXCIFQUADNODE_H

#include "QuadTreeLib.h"
#include "QBoundingBox.h"

class mxcifQuadNode
{
protected:
    
    int minHeight;
    int minWidth;


public:

    QBoundingBox qbb;
    vector<QBoundingBox> rectangles;
    mxcifQuadNode *mxqnNW;
    mxcifQuadNode *mxqnNE;
    mxcifQuadNode *mxqnSW;
    mxcifQuadNode *mxqnSE;


    mxcifQuadNode() {}
    mxcifQuadNode(QBoundingBox QBB)
    {
        minHeight = 0;
        minWidth = 0;
        (*this).qbb = QBB;
        (*this).mxqnNW = NULL;
        (*this).mxqnNE = NULL;
        (*this).mxqnSW = NULL;
        (*this).mxqnSE = NULL;

    }
    mxcifQuadNode(int originX, int originY, float width, float height)
    {
        minHeight = 0;
        minWidth = 0;
        QBoundingBox *QBB = new QBoundingBox(originX, originY, width, height);
        (*this).qbb = *QBB;
        (*this).mxqnNW = NULL;
        (*this).mxqnNE = NULL;
        (*this).mxqnSW = NULL;
        (*this).mxqnSE = NULL;

    }

    bool isLeaf() {
        return (mxqnNW == NULL && mxqnNE == NULL && mxqnSW == NULL && mxqnSE == NULL);
    }


    bool insert(QBoundingBox * box)
    {

        // Ignore objects which do not belong in this quad tree
        if (!qbb.intersectsBox(*box))
            return false; // object cannot be added
//        if (rectangles.contains(box))
//            return true; // already exists

        // Subdivide then add the objects to whichever node will accept it
        if (isLeaf())
            subdivide(box);

        bool inserted = false;
        if (isLeaf()) {
            rectangles.push_back(*box);
            inserted = true;
        } else {
            inserted = insertIntoChildren(box);
        }

        if (!inserted) {
            // Couldn't insert into children (it could strattle the bounds of the box)
            rectangles.push_back(*box);
            return true;
        }
        return true;
    }


    bool insertIntoChildren(QBoundingBox *box)
    {
        if (mxqnNW->qbb.insideThis(*box) && mxqnNW->insert(box)) return true;
        if (mxqnNE->qbb.insideThis(*box) && mxqnNE->insert(box)) return true;
        if (mxqnSW->qbb.insideThis(*box) && mxqnSW->insert(box)) return true;
        if (mxqnSE->qbb.insideThis(*box) && mxqnSE->insert(box)) return true;
        return false;
    }

    bool subdivide(QBoundingBox *box)
    {
        float h = qbb.getHeight()/2;
        float w = qbb.getWidth()/2;
        if (w<minWidth || h<minHeight) return false;

        float current_x = qbb.getX() + w;
        float current_y = qbb.getY() + h;


        QPoint *pNW = new QPoint(current_x-w,current_y);
        QBoundingBox *qbbNW = new QBoundingBox( pNW, w, h);
        this->mxqnNW = new mxcifQuadNode(*qbbNW);


        QPoint *pNE = new QPoint(current_x,current_y);
        QBoundingBox *qbbNE = new QBoundingBox( pNE, w, h);
        this->mxqnNE = new mxcifQuadNode(*qbbNE);


        QPoint *pSW = new QPoint(current_x-w,current_y-h);
        QBoundingBox *qbbSW =new QBoundingBox( pSW, w, h);
        this->mxqnSW = new mxcifQuadNode(*qbbSW);


        QPoint *pSE = new QPoint(current_x,current_y-h);
        QBoundingBox *qbbSE =new QBoundingBox( pSE, w, h);
        this->mxqnSE = new mxcifQuadNode(*qbbSE);


        return insertIntoChildren(box);
    }

    void queryRange(QBoundingBox range, vector<QBoundingBox> &rectsInRange) {
        // Automatically abort if the range does not collide with this quad
        if (!(*this).qbb.intersectsBox(range))
            return;

        // Check objects at this level
        for (int i=0; i<rectangles.size(); i++)
        {
            if (range.intersectsBox(rectangles[i]))
                rectsInRange.push_back(rectangles[i]);
        }

        // Otherwise, add the objects from the children
        if (!isLeaf()) {
            this->mxqnNW->queryRange(range,rectsInRange);
            this->mxqnNE->queryRange(range,rectsInRange);
            this->mxqnSW->queryRange(range,rectsInRange);
            this->mxqnSE->queryRange(range,rectsInRange);
        }
    }

    void rectanglesPrint()
    {
        cout<<endl;
        for (int i=0; i<rectangles.size(); i++)
            rectangles[i].print("\t\t");
        cout<<endl;
    }



    void print(string prefix = "", bool emptyLine = false)
    {
        if(emptyLine) cout<<endl;
//        cout<<prefix<< "mxcifQuadNode | minheight : "<<this->minHeight<<" | minWidth : "<<this->minWidth<<endl;
        cout<<prefix<< "mxcifQuadNode | ";
        this->qbb.print("\t\t",true);
        cout<<prefix<< "mxcifQuadNode | rectangles -> "<<this->rectangles.size();
        if(rectangles.size()>0)rectanglesPrint();

    }

};

#endif //ADVDBTEST_MXCIFQUADNODE_H
