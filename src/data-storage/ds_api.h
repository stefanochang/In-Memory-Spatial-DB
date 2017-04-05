
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "../integration/catalog.h"

using namespace std;

//Initial data load supported for Points and Rectangles

int loadData(string dbName, string tableName, int geomtype, string filepath, int collectionStruct)
{
	FILE *fp;
	float x, y, x1, y1;
	geometry *g;
	point *pnt;
	rectangle *rct;
	PointCollection *pntcollection;
	RectangleCollection *rectanglecollection;
	CatalogItem *catItem;
	fp = fopen(filepath.c_str(), "r");
	if(fp == NULL)
	{
		return 0;
	}
	if(geomtype == TYPE_POINT)
	{
		pntcollection = new PointCollection();
		while(fscanf(fp, "%f,%f\n", &x, &y) == 2)
		{
			g = (geometry *)malloc(sizeof(geometry));
			pnt = (point *)malloc(sizeof(point));
			pnt->x = x;
			pnt->y = y;
			g->pnt = pnt;
			pntcollection->appendLast(g);
		}
		catItem = new CatalogItem(dbName, tableName, (PointCollection *)pntcollection);
	}
	else if(geomtype == TYPE_RECTANGLE)
	{
		rectanglecollection = new RectangleCollection();
		while(fscanf(fp, "%f,%f,%f,%f\n", &x, &y, &x1, &y1) == 4)
		{
			g = (geometry *)malloc(sizeof(geometry));
			rct = (rectangle *)malloc(sizeof(rectangle));
			rct->top_x = x;
			rct->top_y = y;
			rct->bottom_x = x1;
			rct->bottom_y = y1;
			g->rec = rct;
			rectanglecollection->appendLast(g);
		}
		catItem = new CatalogItem(dbName, tableName, (RectangleCollection *)rectanglecollection);
	}
	else
	{
		return 0;
	}
	Catalog.insert(catItem);

	return 1;
}

// Insert a single point
bool insertData(list pointsRepo, Point pointToInsert)
{
	geometry *g;
	point *pnt;
	g = (geometry *)malloc(sizeof(geometry));
	pnt = (point *)malloc(sizeof(point));
	g->pnt = pnt;
	g->pnt->x = pointToInsert.getCoordinates()[0];
	g->pnt->y = pointToInsert.getCoordinates()[1];
	pointsRepo.appendLast(g);
	return true;
}

//insert a single rectangle
bool insertData(list rectanglesRepo, Rectangle rectangleToInsert)
{
	geometry *g;
	rectangle *rec;
	g = (geometry *)malloc(sizeof(geometry));
	rec = (rectangle *)malloc(sizeof(rectangle));
	g->rec = rec;
	g->rec->top_x = rectangleToInsert.getCoordinates()[0];
	g->rec->top_y = rectangleToInsert.getCoordinates()[1];
	g->rec->bottom_x = rectangleToInsert.getCoordinates()[2];
	g->rec->bottom_y = rectangleToInsert.getCoordinates()[3];
	rectanglesRepo.appendLast(g);
	return true;
}


//insert a single pointpoint
bool insertData(list pointpointrepo, PointPoint pntpntToInsert)
{
	geometry *g;
	pointpoint *pntpnt;
	g = (geometry *)malloc(sizeof(geometry));
	pntpnt = (pointpoint *)malloc(sizeof(pointpoint));
	g->pntpnt = pntpnt;
	g->pntpnt->point1.x = pntpntToInsert.getCoordinates()[0];
	g->pntpnt->point1.y = pntpntToInsert.getCoordinates()[1];
	g->pntpnt->point2.x = pntpntToInsert.getCoordinates()[2];
	g->pntpnt->point2.y = pntpntToInsert.getCoordinates()[3];
	pointpointrepo.appendLast(g);
	return true;
}

//insert a single PointRectangle
bool insertData(list recpointrepo, PointRectangle pntrectangleToInsert)
{
	geometry *g;
	pointrectangle *pntrec;
	g = (geometry *)malloc(sizeof(geometry));
	pntrec = (pointrectangle *)malloc(sizeof(pointrectangle));
	g->pntrec = pntrec;
	g->pntrec->point1.x = pntrectangleToInsert.getCoordinates()[0];
	g->pntrec->point1.y = pntrectangleToInsert.getCoordinates()[1];
	g->pntrec->rec.top_x = pntrectangleToInsert.getCoordinates()[2];
	g->pntrec->rec.top_y = pntrectangleToInsert.getCoordinates()[3];
	g->pntrec->rec.bottom_x = pntrectangleToInsert.getCoordinates()[4];
	g->pntrec->rec.bottom_y = pntrectangleToInsert.getCoordinates()[5];
	recpointrepo.appendLast(g);
	return true;
}

//insert a single RectangleRectangle
bool insertData(list recrectanglesRepo, RectangleRectangle recrectangleToInsert)
{
	geometry *g;
	rectanglerectangle *recrec;
	g = (geometry *)malloc(sizeof(geometry));
	recrec = (rectanglerectangle *)malloc(sizeof(rectanglerectangle));
	g->recrec = recrec;
	g->recrec->rec1.top_x = recrectangleToInsert.getCoordinates()[0];
	g->recrec->rec1.top_y = recrectangleToInsert.getCoordinates()[1];
	g->recrec->rec1.bottom_x = recrectangleToInsert.getCoordinates()[2];
	g->recrec->rec1.bottom_y = recrectangleToInsert.getCoordinates()[3];
	g->recrec->rec2.top_x = recrectangleToInsert.getCoordinates()[4];
	g->recrec->rec2.top_y = recrectangleToInsert.getCoordinates()[5];
	g->recrec->rec2.bottom_x = recrectangleToInsert.getCoordinates()[6];
	g->recrec->rec2.bottom_y = recrectangleToInsert.getCoordinates()[7];
	recrectanglesRepo.appendLast(g);
	return true;
}

//insert a list of items
bool insertDataBulk(list repo, list geometryToInsert)
{
	record * geometryToInsertPointer = geometryToInsert.getHead();

	do{
		switch(repo.getType()) {
			case TYPE_POINT: insertData(repo, *(new Point(geometryToInsertPointer->geom->pnt->x, geometryToInsertPointer->geom->pnt->y))); break;
			case TYPE_RECTANGLE: insertData(repo, *(new Rectangle(geometryToInsertPointer->geom->rec->top_x, geometryToInsertPointer->geom->rec->top_y,geometryToInsertPointer->geom->rec->bottom_x, geometryToInsertPointer->geom->rec->bottom_y))); break;
			case TYPE_RECTANGLERECTANGLE: insertData(repo, *(new RectangleRectangle(geometryToInsertPointer->geom->recrec->rec1.top_x, geometryToInsertPointer->geom->recrec->rec1.top_y,geometryToInsertPointer->geom->recrec->rec1.bottom_x, geometryToInsertPointer->geom->recrec->rec1.bottom_y, geometryToInsertPointer->geom->recrec->rec2.top_x, geometryToInsertPointer->geom->recrec->rec2.top_y,geometryToInsertPointer->geom->recrec->rec2.bottom_x, geometryToInsertPointer->geom->recrec->rec2.bottom_y))); break;
			case TYPE_POINTPOINT: insertData(repo, *(new PointPoint(geometryToInsertPointer->geom->pntpnt->point1.x, geometryToInsertPointer->geom->pntpnt->point1.y, geometryToInsertPointer->geom->pntpnt->point2.x, geometryToInsertPointer->geom->pntpnt->point2.y))); break;
			case TYPE_POINTRECTANGLE: insertData(repo, *(new PointRectangle(geometryToInsertPointer->geom->pntrec->point1.x, geometryToInsertPointer->geom->pntrec->point1.y, geometryToInsertPointer->geom->pntrec->rec.top_x, geometryToInsertPointer->geom->pntrec->rec.top_y,geometryToInsertPointer->geom->pntrec->rec.bottom_x, geometryToInsertPointer->geom->pntrec->rec.bottom_y))); break;
			default: return false;
		}

		geometryToInsertPointer = geometryToInsertPointer->next;
	}while(geometryToInsertPointer != geometryToInsert.getHead());
	return true;
}

//delete item with id equals geomid
bool deleteData(list repo, int geomId){
	return repo.deleteByUUID(geomId);
}
