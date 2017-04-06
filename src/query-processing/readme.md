# Query Processing module.

This module accepts a Query Tree as input and executes it based on the predicates, joins and data sources mentioned in the query.

## Structure of QueryTree

```
Class QueryTree{
	vector<string> root;
	vector<vector<string>> leftBranch;
	PointCollection leftDataPoint;
	RectangleCollection leftDataRect;
	vector<vector<string>> rightBranch;
	PointCollection rightDataPoint;
	RectangleCollection rightDataRect;
}
```

### Each member of the above class can accept follwing values:
A root can accept following values:

```
For Simple  'select', 'filterBy', and 'objectsInRange' queries, root can be empty: 
	1.	root = { “” }
For 'Distance Join':
	2. root = { “distanceJoin”, distance } // where distance is any float value
		* Example: { “distanceJoin”, “5.05”}
For 'KNN Join queries':
	3. { “knnJoin”, k } // where k is any int value
		* Example: { “knnJoin”, “5” }
For 'Range Join":
	4. { “rangeJoin” }
```

###A branch can have multiple levels. Each level can have combination of following structure. If you are using

```
1. filterBy
	Area on RectangeCollection
		a. Filter by area
			{ “filterBy”, “area”, op, value }
			Example: { “filterBy”, “area”, “le”, “10” }
	Distance on PointCollection & RectangleCollection:
		b. point:
			{ “filterBy”, “distance”, op, dist_value, x, y }
			Example: { “filterBy”, “distance”, “ge”, “15”, “2”, “3.3” }
		c. rectangle
			{ “filterBy”, “distance”, op, dist_value, x1, y1, x2, y2 }
			Example: { “filterBy”, “distance”, “eq”, “25.6”, “2.5”, “2.5”, “3”, “1” }
		op can be any of: “lt”, ”gt”, ”le”, ”ge”, ”eq”

2. kNN
	a. For PointCollection:
		{ “kNN”, k, x, y } // where k is any int value
		Example: { “kNN”, k, “2”, “3.3” }
	b. For RectangleCollection:
		{ “kNN”, k, x1, y1, x2, y2 } // where k is any int value
		Example: { “kNN”, k, “25.6”, “2.5”, “2.5”, “3”, “1” }

3. objectsInRange
	{ “objectsInRange”, “pt1”, “pt2”, “pt3”, “pt4” }
```

###At any given time, either of Rectangle or Point should be assigned i.e.,

LEFT TREE | RIGHT TREE
---------- | -----------
leftDataPoint = <data_source> | rightDataPoint = <data_source>
leftDataRect = <empty_collection> | rightDataRect = <empty_collection>
OR | OR
leftDataPoint = <empty_collection> | rightDataPoint = <empty_collection>
leftDataRect = <data_source> | rightDataRect = <data_source>














