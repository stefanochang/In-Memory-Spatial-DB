
/* ************************************************************************************* *\
    CSE 591 - Advances in Databases - Spring 2017 - Project - Data Storage Module
    -------------------------------------------------------------------------------

	File: ds_datatypes.h

    All internal representations for the objects in the data store are defined here.

    Each geometry type has got corresponding structure representation which contains
    individual coordinate values and provision for storing the ID of the element within
    the collection.

    This representation is separate from the Object representation of the geometry types
    as defined in the integration folder. This is done simply to isolate the data storage
    optimizations from the global data communication object formats. Methods to marshall
    and unmarshall between the object and structure representation are provided in the 
    individual collections.

    -- Ajay Kulkarni, Anuran Duttaroy, Dhanashree Adhikari, Nilam Bari, Omkar Kaptan --

\* ************************************************************************************* */

struct ds_point{
	int id;
	float x;
	float y;
};
typedef struct ds_point ds_point;

struct ds_rectangle{
	int id;
	float top_x;
	float top_y;
	float bottom_x;
	float bottom_y;
};
typedef struct ds_rectangle ds_rectangle;

struct ds_pointpoint{
	int id;
	ds_point point1;
	ds_point point2;
};
typedef struct ds_pointpoint ds_pointpoint;

struct ds_pointrectangle{
	int id;
	ds_point point;
	ds_rectangle rec;
};
typedef struct ds_pointrectangle ds_pointrectangle;

struct ds_rectanglerectangle{
	int id;
	ds_rectangle rec1;
	ds_rectangle rec2;
};
typedef struct ds_rectanglerectangle ds_rectanglerectangle;
