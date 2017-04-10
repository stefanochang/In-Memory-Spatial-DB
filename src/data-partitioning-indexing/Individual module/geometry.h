#include <vector>
// just for output
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;

class Rectangle {
    float x1, y1, x2, y2;
   // int id;
  public:
    Rectangle(float a, float b, float c, float d){
    	x1=a;
    	y1=b;
    	x2=c;
    	y2 = d;
    	
	}

    vector<float> getCoordinates(){
        vector<float> vect;

        vect.push_back(x1);
        vect.push_back(y1);
        vect.push_back(x2);
        vect.push_back(y2);
        return vect;
    }
    void printrectangles(){
        cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    }
    
};

class Point {
    float x, y;
    
  public:
    Point(float a, float b){
    	x=a;
    	y=b;
	}
    //int getId();
    //void setId(int);
    vector<float> getCoordinates(){
    	vector<float> vect;
    	vect.push_back(x);
    	vect.push_back(y);
    	return vect;
	}
    void printpoints(){
        cout<<x<<" "<<y<<endl;
    }
   // Rectangle getEnvelope();
};

