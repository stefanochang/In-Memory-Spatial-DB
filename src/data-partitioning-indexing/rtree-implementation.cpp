#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>

// Header file for SpatialIndexInterface
#include "spatial-index-interface.h"

// to store queries results
#include <vector>
#include "data-storage.h"
// just for output
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

#include <boost/foreach.hpp>
using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef std::pair<box, unsigned> value;
class PointSpatialIndexR{
	private:
		bgi::rtree< point, bgi::linear<16> > rtreeObj;
	
	
	public:
		PointSpatialIndex() {}
    	
    	void createIndex(PointCollection points){
        	
			cout<<"create index point impl"<<endl;
			bgi::rtree< point, bgi::linear<16> > rtree2;
			
			
			Point p;
			while((p=points.getNext(1))!=NULL){
				vector<float> vect;
				
				vect = p.getCoordinates();
				rtree2.insert(point(vect.at(0),vect.at(1)));
			}
			rtreeObj = rtree2;
			
		
		}
		bool deleteIndex(){
			return true;
		}
		PointCollection searchPoint(Rectangle r){
			
			std::vector<point> query_result;
			vect<float> vect = r.getCoordinates();
			
			rtreeObj.query(bgi::intersects(box(point(vect.at(0),vect.at(1)),point(vect.at(2),vect.at(3)))), std::back_inserter(query_result));
			
			for(int x=0;x<query_result.size();x++){

				cout<<query_result.at(x).get<0>()<<" , "<<query_result.at(x).get<1>()<<endl;
		
			}
			PointCollection p ;
			return p;
		}
		
		bool update(PointCollection points){
			bool r = deleteIndex();
			createIndex(points);
			return r;
		}
		
};

/////////////////////////////////////////////////////

class RectangleSpatialIndexR{

	private:
		bgi::rtree< value, bgi::quadratic<16> > rtreeObj;
	
	
	public:
		RectangleSpatialIndexR(){
		}
		
		void createIndex(RectangleCollection rects){
			
			
			cout<<"create index rect impl"<<endl;
			bgi::rtree< value, bgi::quadratic<16> > rtree;
			
			Rectangle r;
			while((r=rects.getNext())!=NULL){
				vector<float> vect;
				
				vect = r.getCoordinates();
				
				box b(point(vect.at(0), vect.at(1)), point(vect.at(2),vect.at(3)));

        		rtree.insert(std::make_pair(b, i));	
				
			}
			
			rtreeObj = rtee;
			
		}
		bool deleteIndex(){
			return true;
		}
		RectangleCollection searchPoint(Rectangle r){
			
			Rectangle Collection rc;
			vect<float> vect = r.getCoordinates();
			
			std::vector<value> result_s;
    		rtreeObj.query(bgi::intersects(box(point(vect.at(0),vect.at(1)),point(vect.at(2),vect.at(3)))), std::back_inserter(result_s));

			std::cout << "spatial query result:" << std::endl;
			
    		BOOST_FOREACH(value const& v, result_s)
        	std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;
			return rc;
		}
		bool update(RectangleCollection rects){
			bool r = deleteIndex();
			createIndex(rects);
			return r;
		}

};


