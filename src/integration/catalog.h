#include "geometry-collection.h"
//#include "spatial-index-interface.h"
#include <map>
class CatalogItem {
  string dbName, tableName;
  PointCollection points;
  RectangleCollection rectangles;
  PointPointCollection pointsPoints;
  RectangleRectangleCollection rectanglesRectangles;
  PointRectangleCollection pointsRectangles;
  /** TO DO: tackle redundancy **/
  //SpatialIndex spatialIndexObject //Handle for spatial partitioned indexed object
  //SpatialIndex dataIndexObject  //Handle for data Indexed object
  map<string, float> statistics;
protected:
  void setStatistic(string, float);
public:
  CatalogItem(string, string, PointCollection);
  CatalogItem(string, string, RectangleCollection);
  CatalogItem(string, string, PointPointCollection);
  CatalogItem(string, string, RectangleRectangleCollection);
  CatalogItem(string, string, PointRectangleCollection);
  float getStatistic(string);
  bool hasSpatialIndex();
  bool hasDataIndex();
  PointCollection getPointCollection();
  RectangleCollection getRectangleCollection();
  PointPointCollection getPointPointCollection();
  PointRectangleCollection getPointRectangleCollection();
  RectangleRectangleCollection getRectangleRectangleCollection();
  //getIndexedObjects();
};

//To be defined as a Singleton Class.
class Catalog {
  CatalogItem* catalogList;
protected:
  int remove(CatalogItem);
  int insert(CatalogItem);
  //storeIndex()
public:
  /*
  getSpatialIndexedPointCollections();
  getDataIndexedPointCollections();
  getSpatialIndexedRectangleCollections();
  getDataIndexedRectangleCollections();
  getPointCollectionsWithoutIndex();
  getRectangleCollectionsWithoutIndex();
  getCollectionByName();
  */
};
