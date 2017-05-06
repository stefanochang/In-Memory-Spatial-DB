# In-Memory-Spatial-DB

## Introduction
This is a fully functional prototype of a database system that resides entirely in-memory, optimized specifically for efficient storage, management and processing of geo-spatial data. The application was designed and implemented by five separate teams as part of the group project for CSE 591: Advanced Database Systems class. Each team is responsible for four different modules and integration. The five modules of the designed database system are:
```bashp
Data Storage
Query Processing
Spatial Index
Data Index
Modules Integration
```
The code is written in C++ with a common interface that brings all different modules together. In future, more modules can be implemented if the standard integration norms are followed. These standards are briefly described below in Integration modules section and more details can be found in the integration document.
The data used for the application is obtained from http://spatialhadoop.cs.umn.edu/datasets.html

## How It Works
The system is composed of four main modules, namely query processing (src/query-processing/README), data storage (src/data-storage/README), spatial indexing (src/spatial-partitioning-indexing/README) and data partitioning indexing (src/data-partitioning-indexing/README). The approach to the project was to define the interface to each module prior to its development, and modify as necessary as the project begins to come together. 
All modules are communicating with each other as necessary, and is not controlled by a master module who takes the input and output of each module and passes it along until the query is completely executed.

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
SELECT [left_branch] [root] [right_branch]

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

### Select queries with index
The system also allows users to specify what kind of index has to be used for range and join queries. For join queries, there is support for the following formats:
1. Both branches with the same type of index (data/spatial).
2. One branch with index (data/spatial) and the other branch without index.
3. One branch with data index and the other branch with spatial index.

The structure of select queries with index is as follows:
SELECT [left_branch] [root] [right_branch]

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
