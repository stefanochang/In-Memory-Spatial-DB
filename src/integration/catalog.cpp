#ifndef CATALOG_H
#include "catalog.h"
#endif

using namespace std;

CatalogItem::CatalogItem(string dbName, string tableName, int collectionType) {
    this->dbName = dbName.c_str();
    this->tableName = tableName.c_str();   
    this->collectionType = collectionType;
}

CatalogItem::CatalogItem(string dbName, string tableName, int collectionType, PointCollection* pointCollection) {
    CatalogItem(dbName, tableName, collectionType);
    this->points = pointCollection;
}

CatalogItem::CatalogItem(string dbName, string tableName, int collectionType, RectangleCollection* rectangleCollection) {
	CatalogItem(dbName, tableName, collectionType);
    this->rectangles = rectangleCollection;
}

CatalogItem::CatalogItem(string dbName, string tableName, int collectionType, PointPointCollection* pointPointCollection) {
	CatalogItem(dbName, tableName, collectionType);
    this->pointsPoints = pointPointCollection;
}

CatalogItem::CatalogItem(string dbName, string tableName, int collectionType, RectangleRectangleCollection* rectangleRectangleCollection) {
	CatalogItem(dbName, tableName, collectionType);
    this->rectanglesRectangles = rectangleRectangleCollection;
}

CatalogItem::CatalogItem(string dbName, string tableName, int collectionType, PointRectangleCollection* pointRectangleCollection) {
	CatalogItem(dbName, tableName, collectionType);
    this->pointsRectangles = pointRectangleCollection;
}

string CatalogItem::getDBName() {
	return this->dbName;
}

string CatalogItem::getTableName() {
	return this->tableName;
}

float CatalogItem::getStatistic(string statistic) {
	if(statistics.find(statistic) == statistics.end()) {
		return -1.0;
	}
	return statistics[statistic];
}

bool CatalogItem::hasSpatialIndex() {
	if(spatialIndexObject != NULL)
  		return true;
  	else
  		return false;
}

bool CatalogItem::hasDataIndex() {
	if(dataIndexObject != NULL)
  		return true;
  	else
  		return false;
}

SpatialIndexInterface* CatalogItem::getSpatialIndex() {
	if (spatialIndexObject != NULL) {
		return spatialIndexObject;
	}
	return NULL;
}

SpatialIndexInterface* CatalogItem::getDataIndex() {
	if (dataIndexObject != NULL) {
		return dataIndexObject;
	}
	return NULL;
}

void CatalogItem::addSpatialIndex(SpatialIndexInterface* spatialIndex) {
	this->spatialIndexObject = spatialIndex;
}

void CatalogItem::addDataIndex(SpatialIndexInterface* dataIndex) {
	this->dataIndexObject = dataIndex;
}

PointCollection* CatalogItem::getPointCollection() {
	return points;
}

RectangleCollection* CatalogItem::getRectangleCollection() {
  	return rectangles;
}

PointPointCollection* CatalogItem::getPointPointCollection() {
	return pointsPoints;
}

PointRectangleCollection* CatalogItem::getPointRectangleCollection() {
	return pointsRectangles;
}

RectangleRectangleCollection* CatalogItem::getRectangleRectangleCollection() {
	return rectanglesRectangles;
}

vector<SpatialIndexInterface*> CatalogItem::getIndexObjects() {
	vector<SpatialIndexInterface*> indexObjects;
	if(dataIndexObject != NULL)
		indexObjects.push_back(dataIndexObject);
	if(spatialIndexObject != NULL)
		indexObjects.push_back(spatialIndexObject);
	return indexObjects;
}

CatalogItem* Catalog::getCatalogItem(string dbName, string tableName) {
	vector<CatalogItem*>::iterator it;
	for(it = catalogList.begin();it < catalogList.end(); ++it) {
		if(((*it)->getDBName() == dbName) && ((*it)->getTableName() == tableName)) {
			return *it;
		}
	}
	return NULL;
}

Catalog* Catalog::catalogInstance = NULL;

Catalog* Catalog::Instance() {
	if(!catalogInstance) {
		catalogInstance = new Catalog;
	}
	return catalogInstance;
}

int Catalog::insert(CatalogItem* catalogitem) {
	catalogList.push_back(catalogitem);
	return 1;
}

int Catalog::remove(string dbName, string tableName) {
	vector<CatalogItem*>::iterator it;
	for(it = catalogList.begin();it < catalogList.end(); ++it) {
		if(((*it)->getDBName() == dbName) && ((*it)->getTableName() == tableName)) {
			catalogList.erase(it);
			--it;
			return 1;
		}
	}
	return -1;
}

PointCollection* Catalog::getPointCollectionByName(string dbName, string tableName) {
	vector<CatalogItem*>::iterator it;
	for(it = catalogList.begin();it < catalogList.end(); ++it) {
		if(((*it)->getDBName() == dbName) && ((*it)->getTableName() == tableName) 
			&& ((*it)->getPointCollection() != NULL)) {
			return (*it)->getPointCollection();
		}
	}
	return NULL;
}

RectangleCollection* Catalog::getRectangleCollectionByName(string dbName, string tableName) {
	vector<CatalogItem*>::iterator it;
	for(it = catalogList.begin(); it < catalogList.end(); ++it) {
		if(((*it)->getDBName() == dbName) && ((*it)->getTableName() == tableName) 
			&& ((*it)->getRectangleCollection() != NULL)) {
			return (*it)->getRectangleCollection();
		}
	}
	return NULL;
}


SpatialIndexInterface* Catalog::getSpatialIndexedCollection(string dbName, string tableName) {
	vector<CatalogItem*>::iterator it;
	for(it = catalogList.begin(); it < catalogList.end(); ++it) {
		if(((*it)->getDBName() == dbName) && ((*it)->getTableName() == tableName) 
			&& ((*it)->getSpatialIndex() != NULL)) {
			return (*it)->getSpatialIndex();
		}
	}
	return NULL;
}

SpatialIndexInterface* Catalog::getDataIndexedCollection(string dbName, string tableName) {
	vector<CatalogItem*>::iterator it;
	for(it = catalogList.begin(); it < catalogList.end(); ++it) {
		if(((*it)->getDBName() == dbName) && ((*it)->getTableName() == tableName) 
			&& ((*it)->getDataIndex() != NULL)) {
			return (*it)->getDataIndex();
		}
	}
	return NULL;
}

int Catalog::getCatalogSize() {
	int itemCount = 0;
	vector<CatalogItem*>::iterator it;
	for(it = catalogList.begin(); it < catalogList.end(); ++it) {
		itemCount += 1;
	}
	return itemCount;
}
