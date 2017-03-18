
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
using namespace std;
int loadData(string dbName, string tableName, int geomtype, string filepath, int collectionStruct)
{
	FILE *fp;
	float x, y;
	geometry *g;
	point *pnt;
	list l;
	fp = fopen(filepath.c_str(), "r");
	if(fp == NULL)
	{
		return 0;
	}
	while(fscanf(fp, "%f,%f\n", &x, &y) == 2)
	{
		printf("x:%f    y:%f\n",x,y);
		g = (geometry *)malloc(sizeof(geometry));
		pnt = (point *)malloc(sizeof(point));
		g->pnt = pnt;
		l.appendLast(g);
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

bool insertDataBulk(list pointsRepo, list pointsToInsert) {
	record * pointsToInsertPointer = pointsToInsert.head;
// need type of geometry if we continue to use lists
	while(pointsToInsertPointer != null) {
		insertData(pointsRepo, pointsToInsertPointer->geom->pnt);
		pointsToInsertPointer = pointsToInsertPointer->next;
	}

	return true;
}
