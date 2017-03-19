
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "constants.h"

using namespace std;
int loadData(string dbName, string tableName, int geomtype, string filepath, int collectionStruct)
{
	FILE *fp;
	float x, y, x1, y1;
	geometry *g;
	point *pnt;
	rectangle *rct;
	list l;
	fp = fopen(filepath.c_str(), "r");
	if(fp == NULL)
	{
		return 0;
	}
	if(geomtype == TYPE_POINT)
	{

		while(fscanf(fp, "%f,%f\n", &x, &y) == 2)
		{
			//printf("x:%f    y:%f\n",x,y);
			g = (geometry *)malloc(sizeof(geometry));
			pnt = (point *)malloc(sizeof(point));
			pnt->x = x;
			pnt->y = y;
			g->pnt = pnt;
			l.appendLast(g);
		}
	}
	else if(geomtype == TYPE_RECTANGLE)
	{
		while(fscanf(fp, "%f,%f,%f,%f\n", &x, &y, &x1, &y1) == 4)
		{
			//printf("x:%f    y:%f\n",x,y);
			g = (geometry *)malloc(sizeof(geometry));
			rct = (rectangle *)malloc(sizeof(rectangle));
			rct->top_x = x;
			rct->top_y = y;
			rct->bottom_x = x1;
			rct->bottom_y = y1;
			g->rec = rct;
			l.appendLast(g);
		}
	}
	else
	{
		return 0;
	}

	return 1;
}
bool insertData(list pointsRepo, point pointToInsert){
	geometry *g;
	point *pnt;
	g = (geometry *)malloc(sizeof(geometry));
	pnt = (point *)malloc(sizeof(point));
	g->pnt = pnt;
	pointsRepo.appendLast(g);
	return true;
}
bool insertData(list rectanglesRepo, rectangle rectangleToInsert){
	geometry *g;
	rectangle *rec;
	g = (geometry *)malloc(sizeof(geometry));
	rec = (rectangle *)malloc(sizeof(rectangle));
	g->rec = rec;
	rectanglesRepo.appendLast(g);
	return true;
}

bool insertDataBulk(list repo, list geometryToInsert) {
	record * geometryToInsertPointer = geometryToInsert.getHead();

	while(geometryToInsertPointer != NULL) {
		switch(repo.getType()) {
			case TYPE_POINT: insertData(repo, *(geometryToInsertPointer->geom->pnt)); break;
			case TYPE_RECTANGLE: insertData(repo, *(geometryToInsertPointer->geom->rec)); break;
		}

		geometryToInsertPointer = geometryToInsertPointer->next;
	}

	return true;
}
