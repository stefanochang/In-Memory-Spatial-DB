# Data Storage
## File Organization
### Header Files
- data-storage.h: This file contains the base classes which will be used for storing the collections in the database. All required functions have been declared only in this header files. This is the one and only file that is to be included by any other team that needs to use data storage API.
- ds_datatypes.h: This file contains the definitions representing a record for each of the data types supported by the database. These data types are used by the data storage only at present and is subject to change to enhance data storage performance. However these changes are independent of the Geometry type classes defined by the integration team.

### Implementation Files
- data-storage.cpp: This file contains all concrete implementations for the functions that are declared in data-storage.h

### Unit Tests
- main.cpp: This file contains the unit tests for checking all basic functionalities of the present code

## Working
The present implementation is a naive working implementation for the collections which can store the data as a serial list. Work is in progress to add support for data storage using different methods and also study on how features like concurrency can be added here is being done.
