# In-Memory-Spatial-DB

## Introduction
The following application is designed by 5 separate teams as part of the group project for CSE 591, Advances in Database class. Each team is responsible for four different modules and integration. The 5 modules of the designed database are:
```bashp
Data Storage
Query Processing
Spatial Index
Data Index
Modules Integration
```
Application is designed to work independent of each other modules if required. The code is written in C++ with a common interface that brings all different modules together. In future, more modules can be implemented if the standard integration norms are followed. These standards are briefly described below in Integration modules section and more details can be found in integration document.
The data used for the application is obtained from http://spatialhadoop.cs.umn.edu/datasets.html

### How It Works
The system is composed of four main modules, namely query processing (src/query-processing/README), data storage (src/data-storage/README), spatial indexing (src/spatial-partitioning-indexing/README) and data partitioning indexing (src/data-partitioning-indexing/README). The approach to the project was to define the interface to each module prior to its development, and modify as necessary as the project begins to come together. 
All modules are communicating with each other as necessary, and is not controlled by a master module who takes the input and output of each module and passes it along until the query is completely executed. For example, the query processing team 

## Installation
The code is written in C++. To run the code version 6.3.0 or up is required. 

To compile the code, execute the following command from src/integration:
```bashp
sh run.sh
```
To run the system, first compile it as mentioned above, and then execute the following command from src/integration:
```bashp
./a.out
```

## Modules
This section describes different modules from integration perspective. Mentioned below is the brief description of each module and their implemented functions. All these methods are accessible to and from integration team and other modules. Internal working and the methods will be described in the individual module description. 

Index Interface:  
* Method name -> searchPoint  
&nbsp;	Input -> Rectangle diagonalCoords  
&nbsp;	Output -> PointCollection  
* Method name -> searchRectangle  
&nbsp;	Input -> Rectangle diagonalCoords  
&nbsp;	Output -> PointCollection  
* Method name -> createIndex  
&nbsp;	Input -> PointCollection points  
&nbsp;	Output -> void  
* Method name -> createIndex  
&nbsp;	Input -> RectangleCollection rectangles  
&nbsp;	Output -> void  
* Method name -> update  
&nbsp;	Input -> PointCollection points  
&nbsp;	Output -> Boolean  
* Method name -> update  
&nbsp;	Input -> RectangleCollection rectangles  
&nbsp;	Output -> Boolean  
* Method name -> deleteIndex  
&nbsp;	Input -> void  
&nbsp;	Output -> Boolean  

Data Storage Interface:  
* Method name -> loadData   
&nbsp;	Input -> String dbName, String tableName, String geomType, String fileName, Int collectionStructure    
&nbsp;	Output -> Boolean status   
* Method name -> insertData  
&nbsp;	Input -> PointCollection pointsRepo, Point pointToInsert    
&nbsp;	Output -> Boolean status   
* Method name -> insertData  
&nbsp;	Input -> RectangleCollection rectanglesRepo, Rectangle rectangleToInsert  
&nbsp;	Output -> Boolean status  
* Method name -> insertDataBulk  
&nbsp;	Input -> PointCollection pointsRepo, PointCollection pointsToInsert  
&nbsp;	Output -> Boolean status   
* Method name -> insertDataBulk  
&nbsp;	Input -> RectangleCollection rectanglesRepo, RectangleCollection rectanglesToInsert   
&nbsp;	Output -> Boolean status   
* Method name -> deletePoint  
&nbsp;	Input -> PointCollection pointsRepo, Point point  
&nbsp;	Output -> Boolean status  
* Method name -> deleteRectangle  
&nbsp;	Input -> RectangleCollection rectanglesRepo, Rectangle rectangle  
&nbsp;	Output -> Boolean status  
* Method name -> getPointByUUID  
&nbsp;	Input -> String tableName, Int objectId  
&nbsp;	Output -> Point point  
* Method name -> getRectangleByUUID  
&nbsp;	Input -> String tableName, Int objectId  
&nbsp;	Output -> Rectangle rectangle  
* Method name -> getPointPointByUUID  
&nbsp;	Input -> String tableName, Int objectId  
&nbsp;	Output -> PointPoint pointPoint  
* Method name -> getPointRectangleByUUID  
&nbsp;	Input -> String tableName, Int objectId  
&nbsp;	Output -> PointRectangle pointRectangle  
* Method name -> getRectangleRectangleByUUID  
&nbsp;	Input -> String tableName,Int objectId  
&nbsp;	Output -> RectangleRectangle rectangleRectangle  

Query Processing Interface:  
* Method name -> processQuery  
&nbsp;	Input -> QueryTree queryTree  
&nbsp;	Output -> QueryResult object  

## Query Structure and Examples
### Load queries
LOAD <data_type> <database_name> <table_name> <file_path> <collection_structure_type>

Four types of collection structures are supported - unsorted, sortedx, sortedy, hilbert.
```
LOAD POINT adb pts pointsfile.txt unsorted
LOAD RECTANGLE adb rects rectfile.txt sortedx
```
### Insert queries
INSERT <data_type> <database_name> <table_name> <param>
```
INSERT POINT adb pts -88 32
INSERT RECTANGLE adb rects 2 2 3 2
```

### Create index queries
CREATE DATA-INDEX <data_type> <database_name> <table_name>
```
CREATE DATA-INDEX POINT adb pts
CREATE DATA-INDEX RECTANGLE adb rects
```

CREATE SPATIAL-INDEX <data_type> <database_name> <table_name>
```
CREATE SPATIAL-INDEX POINT adb pts
CREATE SPATIAL-INDEX RECTANGLE adb rects
```

### Select queries
SELECT [left_branch][root][right_branch]

In the above mentioned SELECT query, left_branch will be:  
<data_type> <database_name> <table_name> | <operation_name_1>:<operation_params_1>

In the above mentioned SELECT query, root will be:  
<join_type|join_params_colon_seperated>

In the above mentioned SELECT query, right_branch will be:  
<data_type> <database_name> <table_name> | <operation_name_1>:<operation_params_1>

### Range queries
Range queries are those that operate on a single collection, and have only the left branch populated, while the root and right branches are empty.
```
SELECT [POINT adb pts|filterDistanceGE:5:0:0] [] []
SELECT [RECTANGLE adb rects|filterDistanceLT:50:0:0] [] []
SELECT [POINT adb pts|filterDistanceGT:5:-88:32] [] [|]
SELECT [RECTANGLE adb rects|filterDistanceLE:10:-88:32] [] [|]
```

### Join queries
Join queries operate on two collections which can either be both points and both rectangles, or one point collection and one rectangle collection. 
Three types of joins are supported by this system - Range Join, Distance Join and KNN Join. Range Join takes no parameters, while distance join takes requires the distance value as parameter, and KNN join requires the value of K as parameter.
```
SELECT [POINT adb pts1|filterDistanceGE:5:0:0] [distanceJoin:500] [POINT adb pts2|filterDistanceGT:5:0:0]
SELECT [POINT adb pts|filterDistanceGE:5:0:0] [rangeJoin] [RECTANGLE adb rects|filterDistanceGT:5:0:0]
SELECT [RECTANGLE adb rects1|filterDistanceGE:5:0:0] [knnJoin:1] [RECTANGLE adb rects2|filterDistanceGT:5:0:0]
```

### Select queries with Index
The system also allows users to specify what kind of index has to be used for range and join queries. For join queries, there is support for the following formats:
1. Both branches with the same type of index (data/spatial).
2. One branch with index (data/spatial) and the other branch without index.
3. One branch with data index and the other branch with spatial index.

The structure of select queries with index is as follows:
SELECT [left_branch_with_index][root][right_branch_with_index]

In the above mentioned SELECT query, left_branch will be:  
<data_type> <database_name> <table_name> <index_type>| <operation_name_1>:<operation_params_1>

In the above mentioned SELECT query, root will be:  
<join_type|join_params_colon_seperated>

In the above mentioned SELECT query, right_branch will be:  
<data_type> <database_name> <table_name> <index_type>| <operation_name_1>:<operation_params_1>

where <index_type> is an optional parameter which can take the values DATA-INDEX or SPATIAL-INDEX

```
SELECT [POINT adb pts DATA-INDEX|filterDistanceGE:5:0:0] [] []
SELECT [POINT adb pts SPATIAL-INDEX|filterDistanceGE:5:0:0] [] []
SELECT [POINT adb pts1 DATA-INDEX|filterDistanceGE:5:0:0] [distanceJoin:500] [POINT adb pts2 DATA-INDEX|filterDistanceGT:5:0:0]
SELECT [POINT adb pts SPATIAL-INDEX|filterDistanceGE:5:0:0] [rangeJoin] [RECTANGLE adb rects SPATIAL-INDEX|filterDistanceGT:5:0:0]
SELECT [RECTANGLE adb rects1 SPATIAL-INDEX|filterDistanceGE:5:0:0] [rangeJoin] [RECTANGLE adb rects2 DATA-INDEX|filterDistanceGT:5:0:0]
SELECT [POINT adb pts1|filterDistanceGE:5:0:0] [distanceJoin:500] [POINT adb pts2 DATA-INDEX|filterDistanceGT:5:0:0]
SELECT [POINT adb pts SPATIAL-INDEX|filterDistanceGE:5:0:0] [rangeJoin] [RECTANGLE adb rects|filterDistanceGT:5:0:0]
```
