#include "Geometry.h"
#include <map>
class CatlogItem {
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
  CatlogItem(string, string, PointCollection);
  CatlogItem(string, string, RectangleCollection);
  CatlogItem(string, string, PointPointCollection);
  CatlogItem(string, string, RectangleRectangleCollection);
  CatlogItem(string, string, PointRectangleCollection);
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
class Catlog {
  CatlogItem* catlogList;
protected:
  int remove(CatlogItem);
  int insert(CatlogItem);
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