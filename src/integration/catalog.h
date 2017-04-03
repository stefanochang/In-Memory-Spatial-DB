#include "spatial-index-interface.h"
#include <map>
class CatalogItem {
  string dbName, tableName;
  int collectionType;
  PointCollection* points;
  RectangleCollection* rectangles;
  PointPointCollection* pointsPoints;
  RectangleRectangleCollection* rectanglesRectangles;
  PointRectangleCollection* pointsRectangles;
  SpatialIndexInterface* spatialIndexObject; //Handle for spatial partitioned indexed object
  SpatialIndexInterface* dataIndexObject;  //Handle for data Indexed object
  map<string, float> statistics;
protected:
  void setStatistic(string, float);
public:
  CatalogItem(string, string, int);
  CatalogItem(string, string, int, PointCollection*);
  CatalogItem(string, string, int, RectangleCollection*);
  CatalogItem(string, string, int, PointPointCollection*);
  CatalogItem(string, string, int, RectangleRectangleCollection*);
  CatalogItem(string, string, int, PointRectangleCollection*);
  string getDBName();
  string getTableName();
  float getStatistic(string);
  bool hasSpatialIndex();
  bool hasDataIndex();
  SpatialIndexInterface* getSpatialIndex();
  SpatialIndexInterface* getDataIndex();
  void addSpatialIndex(SpatialIndexInterface*);
  void addDataIndex(SpatialIndexInterface*);
  PointCollection* getPointCollection();
  RectangleCollection* getRectangleCollection();
  PointPointCollection* getPointPointCollection();
  PointRectangleCollection* getPointRectangleCollection();
  RectangleRectangleCollection* getRectangleRectangleCollection();
  vector<SpatialIndexInterface*> getIndexObjects();  
};

//To be defined as a Singleton Class.
class Catalog {
  vector<CatalogItem*> catalogList;  
public:
  CatalogItem* getCatalogItem(string, string);
  int remove(string, string);
  int insert(CatalogItem*);
  SpatialIndexInterface* getSpatialIndexedCollection(string, string);
  SpatialIndexInterface* getDataIndexedCollection(string, string);
  /*
  vector<SpatialIndexInterface> getSpatialIndexedPointCollections();
  vector<SpatialIndexInterface> getDataIndexedPointCollections();
  vector<SpatialIndexInterface> getSpatialIndexedRectangleCollections();
  vector<SpatialIndexInterface> getDataIndexedRectangleCollections();
  */
  PointCollection* getPointCollectionByName(string, string);
  RectangleCollection* getRectangleCollectionByName(string, string);
};
