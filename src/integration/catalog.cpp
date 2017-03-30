#include "catalog.h"

CatalogItem::CatalogItem(string dbName, string tableName) {
    this->dbName = dbName.c_str();
    this->tableName = tableName.c_str();   
}
/*
CatalogItem::CatalogItem(string dbName, string tableName, PointCollection pointCollection) {
    CatalogItem(dbName, tableName);
    this->points = pointCollection;
}

Catalog::CatalogItem(string, string, RectangleCollection);
Catalog::CatalogItem(string, string, PointPointCollection);
Catalog::CatalogItem(string, string, RectangleRectangleCollection);
Catalog::CatalogItem(string, string, PointRectangleCollection);
float Catalog::getStatistic(string);
*/