//
// Created by ravichandran on 19/03/17.
//

#ifndef IN_MEMORY_SPATIAL_DB_MXCIFQUADNODE_H
#define IN_MEMORY_SPATIAL_DB_MXCIFQUADNODE_H

#include "quadTreeLib.h"
#include "qBoundingBox.h"

class mxcifQuadNode
{
private:

    int leafCapacity;
    int height;

protected:

    qBoundingBox qbb;
    vector<qBoundingBox> rectangles;
    vector<qBoundingBox> overFlowRectangles;



public:

    mxcifQuadNode *mxqnNW;
    mxcifQuadNode *mxqnNE;
    mxcifQuadNode *mxqnSW;
    mxcifQuadNode *mxqnSE;




    mxcifQuadNode() {}
    mxcifQuadNode(qBoundingBox QBB)
    {
        this->height = 0;
        this->leafCapacity = 4;
        (*this).qbb = QBB;
        (*this).mxqnNW = NULL;
        (*this).mxqnNE = NULL;
        (*this).mxqnSW = NULL;
        (*this).mxqnSE = NULL;

    }

    mxcifQuadNode(qBoundingBox QBB, int leafCapacity)
    {
        this->height = 0;
        this->leafCapacity = leafCapacity;
        (*this).qbb = QBB;
        (*this).mxqnNW = NULL;
        (*this).mxqnNE = NULL;
        (*this).mxqnSW = NULL;
        (*this).mxqnSE = NULL;

    }
    mxcifQuadNode(qBoundingBox QBB, int leafCapacity,int height)
    {
        this->height = height;
        this->leafCapacity = leafCapacity;
        (*this).qbb = QBB;
        (*this).mxqnNW = NULL;
        (*this).mxqnNE = NULL;
        (*this).mxqnSW = NULL;
        (*this).mxqnSE = NULL;

    }
    mxcifQuadNode(int originX, int originY, float width, float height)
    {
        this->height = 0;
        this->leafCapacity = 4;
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
//        if (!qbb.intersectsBox(*box))
        if (!qbb.canContain(*box))
            return false; // object cannot be added
//        TODO - Spatial Indexing Team - Rectangles contains logic,check if a bounding box is contained within given rectangles vector of mxcifquadnode
//        if(box->isIn(rectangles))
//            return true;

        if (( isLeaf() && rectangles.size() < leafCapacity )  || ( height == 25 ) )
        {
            rectangles.push_back(*box);
            return true;
        }


        if ( isLeaf() && height < 25)
        {
            subdivide();
        }

        bool inserted = insertIntoChildren(box);


        if (!inserted) {
            // Couldn't insert into children so insert into overflow
            overFlowRectangles.push_back(*box);
            return true;
        }
        return inserted;
    }


    bool insertIntoChildren(qBoundingBox *box)
    {
        if (this->mxqnNW->qbb.canContain(*box) && this->mxqnNW->insert(box)) return true;

        if (this->mxqnNE->qbb.canContain(*box) && this->mxqnNE->insert(box)) return true;

        if (this->mxqnSW->qbb.canContain(*box) && this->mxqnSW->insert(box)) return true;

        if (this->mxqnSE->qbb.canContain(*box) && this->mxqnSE->insert(box)) return true;

        return false;
    }

    void subdivide()
    {
        float h = qbb.getHeight()/2;
        float w = qbb.getWidth()/2;
        //min width and min height check
        if (w < 1 || h < 1) return ;

        float current_x = qbb.getX() + w;
        float current_y = qbb.getY() + h;

        int cur_height = this->height + 1;


        qPoint *pNW = new qPoint(current_x-w,current_y);
        qBoundingBox *qbbNW = new qBoundingBox( pNW, w, h);
        this->mxqnNW = new mxcifQuadNode(*qbbNW,this->leafCapacity,cur_height);


        qPoint *pNE = new qPoint(current_x,current_y);
        qBoundingBox *qbbNE = new qBoundingBox( pNE, w, h);
        this->mxqnNE = new mxcifQuadNode(*qbbNE,this->leafCapacity,cur_height);


        qPoint *pSW = new qPoint(current_x-w,current_y-h);
        qBoundingBox *qbbSW =new qBoundingBox( pSW, w, h);
        this->mxqnSW = new mxcifQuadNode(*qbbSW,this->leafCapacity,cur_height);


        qPoint *pSE = new qPoint(current_x,current_y-h);
        qBoundingBox *qbbSE =new qBoundingBox( pSE, w, h);
        this->mxqnSE = new mxcifQuadNode(*qbbSE,this->leafCapacity,cur_height);

        for (int i=0; i<rectangles.size(); i++)
        {
            if(!insertIntoChildren(&rectangles[i]))
            {
                overFlowRectangles.push_back(rectangles[i]);
            }
        }

        rectangles.clear();

    }

    bool subdivide(qBoundingBox *box)
    {
        float h = qbb.getHeight()/2;
        float w = qbb.getWidth()/2;
        //min width and min height check
        if (w < 1 || h < 1) return false;

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

        for (int i=0; i<overFlowRectangles.size(); i++)
        {
            if (range.intersectsBox(overFlowRectangles[i]))
                rectsInRange.push_back(overFlowRectangles[i]);
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
        if(this->mxqnNW != NULL){this->mxqnNW->deleteNode();delete this->mxqnNW;}
        if(this->mxqnNE != NULL){this->mxqnNE->deleteNode();delete this->mxqnNE;}
        if(this->mxqnSW != NULL){this->mxqnSW->deleteNode();delete this->mxqnSW;}
        if(this->mxqnSE != NULL){this->mxqnSE->deleteNode();delete this->mxqnSE;}

        delete this;

    }

    void rectanglesPrint()
    {
        cout<<"\n\tRectangles Print - Start\n"<<endl;
        for (int i=0; i<rectangles.size(); i++)
            rectangles[i].print("\t\t");
        cout<<"\n\tRectangles Print - End"<<endl;
    }

    void overFlowRectanglesPrint()
    {
        cout<<"\n\tOverFlow Rectangles Print - Start\n"<<endl;
        for (int i=0; i<overFlowRectangles.size(); i++)
            overFlowRectangles[i].print("\t\t");
        cout<<"\n\tOverFlow Rectangles Print - End"<<endl;
    }



    void print(string prefix = "", bool emptyLine = true)
    {
        if(emptyLine) cout<<endl;
        cout<<prefix<< "mxcifQuadNode | height : "<<this->height<<endl;
        cout<<prefix<< "mxcifQuadNode | ";
        this->qbb.print("\t\t",true);
        cout<<prefix<< "mxcifQuadNode | rectangles Size = "<<this->rectangles.size()<<" | overFlowRectangles Size = "<<this->overFlowRectangles.size();
        if(rectangles.size()>0)rectanglesPrint();
        if(overFlowRectangles.size()>0)overFlowRectanglesPrint();

    }

};

#endif //IN_MEMORY_SPATIAL_DB_MXCIFQUADNODE_H
