# Query Processing module.

This module accepts a Query Tree as input and executes it based on the predicates, joins and data sources mentioned in the query.

To call query processing module include "integration/query-processing.h"

```
include "integration/query-processing.h"
```

Call `processQuery(QueryTree queryTree)` method of `QueryProcessing` class.

## Structure of QueryTree

```
class QueryTree {
    char rootType;
    float rootParam;
    vector<Filter> leftBranch;
    PointCollection leftDataPoint;
    RectangleCollection leftDataRect;
    vector<Filter> rightBranch;
    PointCollection rightDataPoint;
    RectangleCollection rightDataRect;
}
```

### Each member of the above class can accept follwing values:
In order to make the query processing more memory efficient, we use macros of single character to denote certain operations.
For example:

```
For Simple  'select', 'filterBy', and 'objectsInRange' queries, root can be empty, so the root type is specified by: 
	1. rootType = NO_JOIN
For 'Distance Join':
	2. rootType = DISTANCE_JOIN
For 'KNN Join queries':
	3. rootType = KNN_JOIN
For 'Range Join":
	4. rootType = RANGE_JOIN
```	
Where NO_JOIN, RANGE_JOIN, KNN_JOIN, and DISTANCE_JOIN are single char macros defined at the beginning of the file:
```
#define NO_JOIN '1'
#define RANGE_JOIN '2'
#define KNN_JOIN '3'
#define DISTANCE_JOIN '4'
```

### A branch can have multiple levels. Each level can have combination of following structure. If you are using
Similarly, for the "filterBy" operations, we have defined a set of single char macros at the beginning of the file which can be used to save some memory footprint during the in-memory operations. Operations of filterBy go like this: 
```
Defined Macros:
#define FILTER_BY_AREA_LT 'a'
#define FILTER_BY_AREA_LE 'b'
#define FILTER_BY_AREA_EQ 'c'
#define FILTER_BY_AREA_GT 'd'
#define FILTER_BY_AREA_GE 'e'

#define FILTER_BY_DISTANCE_LT 'f'
#define FILTER_BY_DISTANCE_LE 'g'
#define FILTER_BY_DISTANCE_EQ 'h'
#define FILTER_BY_DISTANCE_GT 'i'
#define FILTER_BY_DISTANCE_GE 'j'

1. filterBy
	Area on RectangeCollection
	(OLDER VERSION)
		a. Filter by area 
			{ “filterBy”, “area”, op, value }
			Example: { “filterBy”, “area”, “le”, “10” }
	(NEWER VERSION)
		a. Filter by area, le, 10
		{FILTER_BY_AREA_LE, "10"}
		
	Distance on PointCollection & RectangleCollection:
		b. point:
		(OLDER VERSION)
			{ “filterBy”, “distance”, op, dist_value, x, y }
			Example: { “filterBy”, “distance”, “ge”, “15”, “2”, “3.3” }
		(NEWER VERSION)	
			{FILTER_BY_DISTANCE_GE, "15", "2","3.3"}
			
		c. rectangle
		(OLDER VERSION)
			{ “filterBy”, “distance”, op, dist_value, x1, y1, x2, y2 }
			Example: { “filterBy”, “distance”, “gt”, “25.6”, “2.5”, “2.5”, “3”, “1” }
		op can be any of: “lt”, ”gt”, ”le”, ”ge”, ”eq”
		
		(NEWER VERSION)	
			{FILTER_BY_DISTANCE_GT, “25.6”, “2.5”, “2.5”, “3”, “1” }
```
The same is the case for kNN and objectsInRange as well but the only difference here is that, instead of single char macros, they're integer macros.
```
Defined Macro:
#define KNN 11

2. kNN
	a. For PointCollection:
	(OLDER VERSION)
		{ “kNN”, k, x, y } // where k is any int value
		Example: { “kNN”, k, “2”, “3.3” }
		
	(NEWER VERSION)	
		{ 11, k, x, y } // where k is any int value
		Example: { 11, k, “2”, “3.3” }
		
	b. For RectangleCollection:
	(OLDER VERSION)
		{ “kNN”, k, x1, y1, x2, y2 } // where k is any int value
		Example: { “kNN”, k, “25.6”, “2.5”, “2.5”, “3”, “1” }
		
	(NEWER VERSION)	
		{ 11, k, x1, y1, x2, y2 } // where k is any int value
		Example: { 11, k, “25.6”, “2.5”, “2.5”, “3”, “1” }

Defined Macro:
#define OBJECTS_IN_RANGE 12

3. objectsInRange
	(OLDER VERSION)
	{ “objectsInRange”, “pt1”, “pt2”, “pt3”, “pt4” }
	
	(NEWER VERSION)
	{ 12, “pt1”, “pt2”, “pt3”, “pt4” }
```

### At any given time, either of Rectangle or Point should be assigned i.e.,

LEFT TREE | RIGHT TREE
---------- | -----------
leftDataPoint = <data_source> leftDataRect = <empty_collection>| rightDataPoint = <data_source> rightDataRect = <empty_collection>
OR | OR
leftDataPoint = <empty_collection> leftDataRect = <data_source> | rightDataPoint = <empty_collection> rightDataRect = <data_source>



Demo of the module available at https://www.youtube.com/watch?v=Z-2SC0yNU0s 













