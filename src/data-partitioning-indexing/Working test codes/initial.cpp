#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>

// to store queries results
#include <vector>

// just for output
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

#include <boost/foreach.hpp>
using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

int main()
{
    typedef bg::model::point<float, 2, bg::cs::cartesian> point;
    typedef bg::model::box<point> box;
    typedef std::pair<box, unsigned> value;

	string line;
	ifstream myfile ("rectangle.csv");

    // create the rtree using default constructor
	// Rectangle tree variables
    bgi::rtree< value, bgi::quadratic<16> > rtree;
	
	

	//point tree variables

	std::vector<point> points;
	bgi::rtree< point, bgi::linear<16> > rtree2(points.begin(), points.end());



	// Query result variables
	std::vector<point> query_result;
	std::vector<value> result_n;
    	
	// Loading Rectangle data

	cout<<"Loading Rectangle data"<<endl;

	float val;
	int i=0;
	if(myfile.is_open()){
		while(getline(myfile,line)){
			stringstream ss(line);
			vector<float> vect;
			while (ss >> val)
   			{
        		vect.push_back(val);

        		if (ss.peek() == ',')
            		ss.ignore();
            	
    		}
    		
    	// create a box
        box b(point(vect.at(0), vect.at(1)), point(vect.at(2),vect.at(3)));

        // insert new value
        rtree.insert(std::make_pair(b, i));
        i++;
		}
	}
	cout<<"Inserted "<<i<<" rectangles in R tree"<<endl;


	

	cout<<"Loading Point dataset "<<endl;
	// Loading point data
	val = 0.0;
	i = 0;
	ifstream myfile2 ("point.csv");
	
	if(myfile2.is_open()){
		while(getline(myfile2,line)){
			stringstream ss(line);
			vector<float> vect;
			while (ss >> val)
   			{
        			vect.push_back(val);

        			if (ss.peek() == ',')
            				ss.ignore();
            	
    			}
    		
	// insert new value
        	rtree2.insert(point(vect.at(0),vect.at(1)));
        	i++;
		}
	}

	cout<<"Inserted "<<i<<" points in R tree 2"<<endl;

	cout<<"Find points intersecting the rectangle (144,10) and (145,15) "<<endl;

	rtree2.query(bgi::intersects(box(point(144,10),point(145,15))), std::back_inserter(query_result));


	for(int x=0;x<query_result.size();x++){

		cout<<query_result.at(x).get<0>()<<" , "<<query_result.at(x).get<1>()<<endl;
		
	}
	

	// find 5 nearest values to a point
	
	cout<<"Find 3 nearest neighbors(rectangles) to a point 0,0 "<<endl; 
	rtree.query(bgi::nearest(point(0, 0), 3), std::back_inserter(result_n));


	std::cout << "knn query point:" << std::endl;
	std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
	std::cout << "knn query result:" << std::endl;
	BOOST_FOREACH(value const& v, result_n)
    		std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;


	cout<<"Deleting R trees " <<endl;
	rtree.clear();
	rtree2.clear();

	cout<<" Size of R tree = "<<rtree.size()<<endl;	
	cout<<" Size of R tree 2= "<<rtree2.size()<<endl;
    	myfile.close();
	myfile2.close();
	
    return 0;
}
