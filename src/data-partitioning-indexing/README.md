R-tree is a self balanced tree  used for spatial searching. It was proposed by Antonin Guttman in 1984 as an expansion of B-tree for multidimensional data. It may be used to store points or volumetric data in order to perform a spatial query. Its dynamic just like a binary tree, which means It's possible to insert new objects or to remove the ones already stored. 

The key idea of the data structure is to group nearby objects and represent them with their minimum bounding rectangle in the next higher level of the tree; the "R" in R-tree is for rectangle. Since all objects lie within this bounding rectangle, a query that does not intersect the bounding rectangle also cannot intersect any of the contained objects. At the leaf level, each rectangle describes a single object; at higher levels the aggregation of an increasing number of objects.

During the Insertion of an object, if the leaf node is full, then there is a splitting strategy that is employed in a way
 - total area of the node is minimized.
 - Overlapping between the two nodes is minimized. Both of these can be conflicting at times. For our code, we used the Linear Split algorithm. 

Search in R tree, which basically means, Given a point q, find all Minimum Bounding Boxes (mbbs) containing q. Process starts from the node and if any of the children have q within them, it recursively searches its children, updating the result each time.


We go through each of the algorithms which are of importance to us in our project:
Algorithm RangeSearch(TypeNode RN, TypeRegion Q) 
/* Finds all rectangles that are stored in an R-tree with root node RN, which are intersected by a query rectangle Q. Answers are stored in the set A */ 
1. if RN is not a leaf node 
2. 	examine each entry e of RN to find those e.mbr that intersect Q 
3. 	foreach such entry e call RangeSearch(e.ptr,Q) 
4. else // RN is a leaf node 
5. 	examine all entries e and find those for which e.mbr intersects Q
6. 	add these entries to the answer set A 
7. Endif


    Algorithm Insert(TypeEntry E, TypeNode RN) 
/* Inserts a new entry E in an R-tree with root node RN */ 
1. Traverse the tree from root RN to the appropriate leaf. At each level, select the node, L, whose MBR will require the minimum area enlargement to cover E.mbr 
2. In case of ties, select the node whose MBR has the minimum area 
3. if the selected leaf L can accommodate E
4. 	Insert E into L 
5. 	Update all MBRs in the path from the root to L, so that all of them cover E.mbr
 6. else // L is already full 
7. 	Let E be the set consisting of all L’s entries and the new entry E Select as seeds two entries e1, e2 ∈ E, where the distance between e1 and e2 is the maximum among all other pairs of entries from E Form two nodes, L1 and L2, where the first contains e1 and the second e2 
8. 	Examine the remaining members of E one by one and assign them to L1 or L2, depending on which of the MBRs of these nodes will require the minimum area enlargement so as to cover this entry 
9. 	if a tie occurs 
10. 		Assign the entry to the node whose MBR has the smaller area 
11. endif 
12. if a tie occurs again 
13. Assign the entry to the node that contains the smaller number of entries 
14. endif 
15. if during the assignment of entries, there remain λ entries to be assigned and the one node contains m − λ entries 
16. Assign all the remaining entries to this node without considering the aforementioned criteria /* so that the node will contain at least m entries */ 
17. endif 
18. Update the MBRs of nodes that are in the path from root to L, so as to cover L1 and accommodate L2 
19. Perform splits at the upper levels if necessary 
20. In case the root has to be split, create a new root 
21. Increase the height of the tree by one
22. Endif


Algorithm Delete(TypeEntry E, TypeNode RN) 
/* Deletes an entry E from an R-tree with root node RN */ 
1. if RN is a leaf node
2. 	search all entries of RN to find E.mbr 
3. else // RN is an internal node 
4. 	Find all entries of RN that cover E.mbr 
5. 	Follow the corresponding subtrees until the leaf L that contains E is found
6. 	Remove E from L
7. endif 
8. Call algorithm CondenseTree(L) /* Figure 1.8 */
9. if the root has only one child /* and it is not a leaf */ 
10. 	Remove the root 
11. 	Set as new root its only child 
12. Endif



Algorithm CondenseTree(TypeNode L) 
/* Given is the leaf L from which an entry E has been deleted. If after the deletion of E, L has fewer than m entries, then remove entirely leaf L and reinsert all its entries. Updates are propagated upwards and the MBRs in the path from root to L are modified (possibly become smaller) */ 
1. Set X = L 
2. Let N be the set of nodes that are going to be removed from the tree (initially, N is empty) 
3. while X is not the root 
4. 	Let ParentX be the father node of X 
5. 	Let EX be the entry of ParentX that corresponds to X 
6. 	if X contains less than m entries 
7. 	Remove EX from ParentX 
8. 	Insert X into N 
9. 	endif 
10.	if X has not been removed 
11. Adjust its corresponding MBR EX.mbr, so as to enclose all rectangles in X /*               EX.mbr may become smaller */ 
12. endif 
13. Set X = ParentX 
14. endwhile 
15. Reinsert all the entries of nodes that are in the set N


In Ubuntu terminal navigate to folder where code is saved and Do the following:
1. sudo apt-get install libboost-all-dev
2. g++ test_bulk.cpp -L/usr/local/lib/ -lboost_filesystem -std=c++11
2. ./a.out


Explanation of the code:

For spatial indexing, we have implemented R-tree using boost library. R-tree is used to store points, rectangles, polygons in-order to do spatial queries. 
Boost provides functions for inserting, searching and deleting. 

Boost header files used:
geometry.hpp
point.hpp
box.hpp
rtee.hpp 


classes used: 
DataIndexingWrapper is the primary class which inherits the spatialIndexInterface class and overrides all the functions of SpatialIndexInterface. 
DataIndexingWrapeer class contains two objects pointDataIndex and RectangleDataIndex.
PointDataIndex class has an object of type rtree and instance of rtree object stores the actual rtree when generated.
We have set the fanout of Rtree as 16 as it takes less time to create Rtree for larger dataset as compared to other fanout values. 


CreateIndex function:
For points, the createIndex function uses the getNext function of class PointCollection to extract the points within the collection and insert them into the Rtree one by one using boost library.
For rectangles, the createIndex function uses the getNext function of class RectangleCollection to extract the collection of rectangles, convert them into box and insert them into the Rtree using boost.


Search function:
For points, SearchPoint function takes Rectangle as an argument and will return all the points that are intersecting or are within or overlap the given boundary. This is performed by using the intersects query given by the boost library. The result of this query is stored in the vcector and converted to pointCollection which is then returned.
For Rectangles, SearchRectangle function takes Rectangle as an argument and will return all the rectangles that are intersecting or are within or overlap the given boundary. This is performed by using the intersects query given by the boost library. The result of this query is packaged to RectangleCollection which is then returned.


Update function- delete+create:
For points, the update function takes PointCollection as an argument. It deletes the Rtree structure by calling the delete function and then calls CreateIndex with the new points to be inserted into the tree. 
For rectangles, the update function takes RectangleCollection as an argument. It deletes the Rtree structure by calling the delete function and then calls CreateIndex with the new rectangles to be inserted into the tree. 
