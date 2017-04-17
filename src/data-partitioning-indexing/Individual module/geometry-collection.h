#include "geometry.h"

class PointCollection{
    vector<Point> points;    
   // string name, databaseName; 
    //int collectionStructure;
  public:
    PointCollection();
    PointCollection(vector<Point> x){
    	points = x;
	}
   // Point getById(int);
    vector<Point> getNext(int n=1, int transaction_id=1){
    	
    	
		return points;
	}
    	
	
	void printcollection(){
        for(int i=0;i<points.size();i++){
            points.at(i).printpoints();
        }

    }
	
    int insert(Point p){
    	
	}
    int insertBulk(PointCollection p){
    	
		//points = collection;
		return 1;
	}
    //bool isEmpty();
    //int remove(Point);
    //int removeById(int);
    int getSize(){
    	
    	return points.size();
	}  // size of PointCollection
	
    //string getDBName();
    //string getTableName();
};

class RectangleCollection{
    vector<Rectangle> rectangles;    
   // string name, databaseName; 
    //int collectionStructure;
  public:
    RectangleCollection();
    RectangleCollection(vector<Rectangle> x){
        rectangles = x;
    }
   // Point getById(int);
    vector<Rectangle> getNext(int n=1, int transaction_id=1){
        
        
        return rectangles;
    }
        
    
    void printcollection(){
        for(int i=0;i<rectangles.size();i++){
            rectangles.at(i).printrectangles();
        }

    }
    
    int insert(Rectangle p){
        
    }
    int insertBulk(RectangleCollection p){
        
        //points = collection;
        return 1;
    }
    //bool isEmpty();
    //int remove(Point);
    //int removeById(int);
    int getSize(){
        
        return rectangles.size();
    }  // size of PointCollection
    
    //string getDBName();
    //string getTableName();
};


