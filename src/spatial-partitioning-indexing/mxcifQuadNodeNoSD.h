//
// Created by ravichandran on 19/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_MXCIFQUADNODE_H
#define IN_MEMORY_SPATIAL_DB_MXCIFQUADNODE_H

#include "quadTreeLib.h"
#include "qBoundingBox.h"

class mxcifQuadNode
{
protected:
    
    int minHeight;
    int minWidth;


public:

    qBoundingBox qbb;
    vector<qBoundingBox> rectangles;
    mxcifQuadNode *mxqnNW;
    mxcifQuadNode *mxqnNE;
    mxcifQuadNode *mxqnSW;
    mxcifQuadNode *mxqnSE;


    mxcifQuadNode() {}
    mxcifQuadNode(qBoundingBox QBB)
    {
        minHeight = 1;
        minWidth = 1;
        (*this).qbb = QBB;
        (*this).mxqnNW = NULL;
        (*this).mxqnNE = NULL;
        (*this).mxqnSW = NULL;
        (*this).mxqnSE = NULL;

    }
    mxcifQuadNode(int originX, int originY, float width, float height)
    {
        minHeight = 1;
        minWidth = 1;
        qBoundingBox *QBB = new qBoundingBox(originX, originY, width, height);
        (*this).qbb = *QBB;
        (*this).mxqnNW = NULL;
        (*this).mxqnNE = NULL;
        (*this).mxqnSW = NULL;
        (*this).mxqnSE = NULL;

    }

    bool isLeaf() {
        return (mxqnNW == NULL && mxqnNE == NULL && mxqnSW == NULL && mxqnSE == NULL);
    }


    bool insert(qBoundingBox * box)
    {

        // Ignore objects which do not belong in this quad tree
        if (!qbb.intersectsBox(*box))
            return false; // object cannot be added
//        TODO - Spatial Indexing Team - Rectangles contains logic,check if a bounding box is contained within given rectangles vector of mxcifquadnode
        if(box->isIn(rectangles))
            return true;

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
            // Couldn't insert into children
            rectangles.push_back(*box);
            return true;
        }
        return true;
    }


    bool insertIntoChildren(qBoundingBox *box)
    {
        if (mxqnNW->qbb.insideThis(*box) && mxqnNW->insert(box)) return true;
        if (mxqnNE->qbb.insideThis(*box) && mxqnNE->insert(box)) return true;
        if (mxqnSW->qbb.insideThis(*box) && mxqnSW->insert(box)) return true;
        if (mxqnSE->qbb.insideThis(*box) && mxqnSE->insert(box)) return true;
        return false;
    }

    bool subdivide(qBoundingBox *box)
    {
        float h = qbb.getHeight()/2;
        float w = qbb.getWidth()/2;
        if (w<minWidth || h<minHeight) return false;

        float current_x = qbb.getX() + w;
        float current_y = qbb.getY() + h;


        qPoint *pNW = new qPoint(current_x-w,current_y);
        qBoundingBox *qbbNW = new qBoundingBox( pNW, w, h);
        this->mxqnNW = new mxcifQuadNode(*qbbNW);


        qPoint *pNE = new qPoint(current_x,current_y);
        qBoundingBox *qbbNE = new qBoundingBox( pNE, w, h);
        this->mxqnNE = new mxcifQuadNode(*qbbNE);


        qPoint *pSW = new qPoint(current_x-w,current_y-h);
        qBoundingBox *qbbSW =new qBoundingBox( pSW, w, h);
        this->mxqnSW = new mxcifQuadNode(*qbbSW);


        qPoint *pSE = new qPoint(current_x,current_y-h);
        qBoundingBox *qbbSE =new qBoundingBox( pSE, w, h);
        this->mxqnSE = new mxcifQuadNode(*qbbSE);


        return insertIntoChildren(box);
    }

    void queryRange(qBoundingBox range, vector<qBoundingBox> &rectsInRange) {

        if (!(*this).qbb.intersectsBox(range))
            return;


        for (int i=0; i<rectangles.size(); i++)
        {
            if (range.intersectsBox(rectangles[i]))
                rectsInRange.push_back(rectangles[i]);
        }


        if (!isLeaf()) {
            this->mxqnNW->queryRange(range,rectsInRange);
            this->mxqnNE->queryRange(range,rectsInRange);
            this->mxqnSW->queryRange(range,rectsInRange);
            this->mxqnSE->queryRange(range,rectsInRange);
        }
    }

    void deleteNode()
    {
        if(this->mxqnNW != NULL)this->mxqnNW->deleteNode();
        if(this->mxqnNE != NULL)this->mxqnNE->deleteNode();
        if(this->mxqnSW != NULL)this->mxqnSW->deleteNode();
        if(this->mxqnSE != NULL)this->mxqnSE->deleteNode();

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

#endif //IN_MEMORY_SPATIAL_DB_MXCIFQUADNODE_H
