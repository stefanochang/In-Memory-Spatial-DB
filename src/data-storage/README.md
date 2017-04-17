# Data Storage
This module handles data storage operations for the database. The storage is designed specifically for **_geometry objects_**. Data is communicated as a **_vector of objects_** with other modules.
### Geometry Data types
Presently, 5 data types are supported namely:
  - Point: Represents a point in space defined by an X and a Y coordinate
  - Rectangle: Represents a rectanglular area in space defined by 2 points - a bottom left and a top right point
  - PointPoint: A pair type geometry object containing 2 points
  - RectangleRectangle: A pair type geometry object containing 2 rectangles
  - PointRectangle: A pair type geometry object containing a point and a rectangle
 
### Geometry Collections and operations
This module defines a "Collection" for each of these data types in which objects can be stored, manipulated and retrieved. Following are the properties of each collection:
  - Name: The name of the collection
  - Database Name: The database this collection belongs to
  - Collection Structure: This property defines how the objects in this collection are organized. For e.g. a point collection may be organized by a sorted X value. All operations on this collection will retain this ordering. The collection structure can also be modified after the collection has been defined with a different structure.
Each collection can perform the following operations on the data:
  - Insertions: Insertions can be 1 object at a time or in bulk by passing a vector or another collection of similar objects. If a specific insertion pattern has been set for the collection then the insertions will retain it while new objects are inserted.
  - Retrievals: Data can be retrieved 1 object at a time or in batches. Data can also be retrieved by specifying the unique identifier of the data in the collection.
  - Deletions: Deletions can be performed by specifying the ID of the data or by specifying the geometry values and all objects satisfying that condition will be deleted.
  
## Internals of Geometry and Collection operations
The storage module stores all data in collections in a **Vector**. This allows data storage in contiguious memory locations. 
The basic storage unit for all geometry types is a **_structure_** which contains *floating* point variables for coordinates and an integer for the ID of the element in the collection. A floating point variable is selected since it allows up to 6 digit precision which more than serves the present requirements of geometry coordinates.
Data can be organized presently in different ways within a collection. At present, data can be unordered or ordered by X coordinate or Y coordinate. Sorted X and Y organizations have been defined for Point and Rectangle geometry types. In case of rectangle, the X and Y coordinate are those of the center of the rectangle.
 
## File Organization
### Header Files
- data-storage.h: This file contains the base classes which will be used for storing the collections in the database. All required functions have been declared only in this header files. This is the one and only file that is to be included by any other team that needs to use data storage API.
- ds_datatypes.h: This file contains the definitions representing a record for each of the data types supported by the database. These data types are used by the data storage only at present and is subject to change to enhance data storage performance. However these changes are independent of the Geometry type classes defined by the integration team.

### Implementation Files
- data-storage.cpp: This file contains all concrete implementations for the functions that are declared in data-storage.h

### Unit Tests
- main.cpp: This file contains the unit tests for checking all basic functionalities of the present code
