#include "spatial-index-interface.h"
#include <map>
class CatalogItem {
  string dbName, tableName;
  PointCollection points;
  RectangleCollection rectangles;
  PointPointCollection pointsPoints;
  RectangleRectangleCollection rectanglesRectangles;
  PointRectangleCollection pointsRectangles;
  SpatialIndexInterface spatialIndexObject; //Handle for spatial partitioned indexed object
  SpatialIndexInterface dataIndexObject;  //Handle for data Indexed object
  map<string, float> statistics;
protected:
  void setStatistic(string, float);
public:
  CatalogItem(string, string);
  CatalogItem(string, string, PointCollection);
  CatalogItem(string, string, RectangleCollection);
  CatalogItem(string, string, PointPointCollection);
  CatalogItem(string, string, RectangleRectangleCollection);
  CatalogItem(string, string, PointRectangleCollection);
  float getStatistic(string);
  bool hasSpatialIndex();
  bool hasDataIndex();
  void addSpatialIndex(SpatialIndexInterface);
  void addDataIndex(SpatialIndexInterface);
  PointCollection getPointCollection();
  RectangleCollection getRectangleCollection();
  PointPointCollection getPointPointCollection();
  PointRectangleCollection getPointRectangleCollection();
  RectangleRectangleCollection getRectangleRectangleCollection();
  vector<SpatialIndexInterface> getIndexedObjects();  
};

//To be defined as a Singleton Class.
class Catalog {
  CatalogItem* catalogList;
protected:
  int remove(CatalogItem);
  int insert(CatalogItem);
public:
  vector<SpatialIndexInterface> getSpatialIndexedPointCollections();
  vector<SpatialIndexInterface> getDataIndexedPointCollections();
  vector<SpatialIndexInterface> getSpatialIndexedRectangleCollections();
  vector<SpatialIndexInterface> getDataIndexedRectangleCollections();
  PointCollection getPointCollectionsWithoutIndex();
  RectangleCollection getRectangleCollectionsWithoutIndex();
  PointCollection getPointCollectionByName(string);
  RectangleCollection getRectangleCollectionByName(string);
};
