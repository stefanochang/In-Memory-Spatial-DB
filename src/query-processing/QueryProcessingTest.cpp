
/*
 * Main.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: Supriya
 */

#include <string>
#include <iostream>
#include <vector>
#include "../integration/query-processing.h"

#define TYPE_NULL 0
#define TYPE_POINT 1
#define TYPE_RECTANGLE 2
#define TYPE_POINTPOINT 3
#define TYPE_POINTRECTANGLE 4
#define TYPE_RECTANGLERECTANGLE 5

#define NO_JOIN '1'
#define RANGE_JOIN '2'
#define KNN_JOIN '3'
#define DISTANCE_JOIN '4'

#define FILTER_BY_AREA_LT 'a'
#define FILTER_BY_AREA_LE 'b'
#define FILTER_BY_AREA_EQ 'c'
#define FILTER_BY_AREA_GT 'd'
#define FILTER_BY_AREA_GE 'e'
#define NO_FILTER ''

#define FILTER_BY_DISTANCE_LT 'f'
#define FILTER_BY_DISTANCE_LE 'g'
#define FILTER_BY_DISTANCE_EQ 'h'
#define FILTER_BY_DISTANCE_GT 'i'
#define FILTER_BY_DISTANCE_GE 'j'

#define KNN 11
#define OBJECTS_IN_RANGE 12

using namespace std;


bool queryProcessingTests() {


    vector<Filter> filterNull;

	PointCollection ptcolNull;
	RectangleCollection retcolNull;


	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 1 : FilterBy Distance -\n\t Find the points that are greater than distance 2 from point (0,0)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams;
		inputParams.push_back(2);
		inputParams.push_back(0);
		inputParams.push_back(0);

		char ft=FILTER_BY_DISTANCE_GT;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		PointCollection ptcol;

		cout<<"POINT DATASET\n";
		for(int i=0;i<5;i++){
			cout<<"(0,"<<i<<")\n";
			ptcol.insert(Point(0,i));
		}
		qTree.setLeftPoints(ptcol);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINT){
			PointCollection ppcol = qResult.getPointCollection();
			cout<<"\nRESULT: PointCollection"<<endl;
			for(int i=0;i<ppcol.getSize();i++)
			{
				vector<Point> temp_ptv = ppcol.getNext(1);
				for (Point pt : temp_ptv)
					cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
			}
		}
		else{
			cout << "Fail Test 1"<<endl;
		}
	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 2 : FilterBy Distance -\n\t Find the points that are equal to distance 5 from point (0,1)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams;
		inputParams.push_back(5);
		inputParams.push_back(0);
		inputParams.push_back(1);

		char ft=FILTER_BY_DISTANCE_EQ;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		PointCollection ptcol;

		cout<<"POINT DATASET\n";
		for(int i=4;i<8;i++){
			cout<<"(0,"<<i<<")\n";
			ptcol.insert(Point(0,i));
		}
		qTree.setLeftPoints(ptcol);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINT){
			PointCollection ppcol = qResult.getPointCollection();
			cout<<"\nRESULT: PointCollection"<<endl;
			for(int i=0;i<ppcol.getSize();i++)
			{
				vector<Point> temp_ptv = ppcol.getNext(1);
				for (Point pt : temp_ptv)
					cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
			}
		}
		else{
			cout << "Fail Test 2"<<endl;
		}
	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 3 : FilterBy Distance -\n\t Find the Rectangles that are less than distance 2 from Rectangle (0,0,1,1)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams;
		inputParams.push_back(2);
		inputParams.push_back(0);
		inputParams.push_back(0);
		inputParams.push_back(1);
		inputParams.push_back(1);

		char ft=FILTER_BY_DISTANCE_LT;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		RectangleCollection retcol;

		cout<<"RECTANGLE DATASET\n";
		for(int i=0;i<6;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+2<<","<<i+2<<")\n";
			retcol.insert(Rectangle(i,i,i+2,i+2));
		}
		qTree.setLeftRectangles(retcol);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 3"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 4 : Two FilterBy Distance on same collection -\n\t Find the Rectangles that are greater than distance 2 and\n\t less than distance from Rectangle (0,0,1,1)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams1;
		inputParams1.push_back(2);
		inputParams1.push_back(0);
		inputParams1.push_back(0);
		inputParams1.push_back(1);
		inputParams1.push_back(1);

		char ft1=FILTER_BY_DISTANCE_GT;
		Filter f1 = Filter(ft1,inputParams1);

		vector<float> inputParams2;
		inputParams2.push_back(4);
		inputParams2.push_back(0);
		inputParams2.push_back(0);
		inputParams2.push_back(1);
		inputParams2.push_back(1);

		char ft2=FILTER_BY_DISTANCE_LT;
		Filter f2 = Filter(ft2,inputParams2);

		vector<Filter> filter;
		filter.push_back(f1);
		filter.push_back(f2);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		RectangleCollection retcol;

		cout<<"RECTANGLE DATASET\n";
		for(int i=0;i<5;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+2<<","<<i+2<<")\n";
			retcol.insert(Rectangle(i,i,i+2,i+2));
		}
		qTree.setLeftRectangles(retcol);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 4"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 5 : FilterBy Area\n\t Find all the Rectangles that have area greater than 5";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams;
		inputParams.push_back(5);

		char ft=FILTER_BY_DISTANCE_GT;
		Filter f = Filter(ft,inputParams);

		vector<Filter> filter;
		filter.push_back(f);

		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		RectangleCollection retcol;

		cout<<"RECTANGLE DATASET\n";
		for(int i=1;i<7;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+i<<","<<i+i<<")\n";
			retcol.insert(Rectangle(i,i,i+i,i+i));
		}
		qTree.setLeftRectangles(retcol);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);



		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 5"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 6 : Distance Join\n";
	cout<<"\t Filterby left branch all points whose distance is greater than 3 from point (0,0)\n";
    cout<<"\t Filterby right branch all points whose distance is less than 5 from point (0,3)\n";
	cout<<"\t DistanceJoin all points whose distance is less than 5";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(DISTANCE_JOIN);
		qTree.setRootParam(5);

		vector<float> inputParamsleft;
		inputParamsleft.push_back(3);
		inputParamsleft.push_back(0);
		inputParamsleft.push_back(0);

		char fl=FILTER_BY_DISTANCE_GT;
		Filter f_left = Filter(fl,inputParamsleft);

		vector<Filter> filter_left;
		filter_left.push_back(f_left);

		qTree.setLeftFilter(filter_left);

		vector<float> inputParamsright;
		inputParamsright.push_back(5);
		inputParamsright.push_back(0);
		inputParamsright.push_back(3);

		char fr=FILTER_BY_DISTANCE_LT;
		Filter f_right = Filter(fr,inputParamsright);

		vector<Filter> filter_right;
		filter_right.push_back(f_right);

		qTree.setRightFilter(filter_right);

		cout<<"POINT DATASET LEFT\t\tPOINT DATASET RIGHT";
		PointCollection ptcolleft,ptcollright;

		for(int i=0;i<5;i++){
			ptcolleft.insert(Point(0,i));
			ptcollright.insert(Point(0,i+2));
			cout<<"\n\t("<<0<<","<<i<<")\t\t\t\t("<<0<<","<<i+2<<")";
		}

		qTree.setLeftPoints(ptcolleft);
		qTree.setRightPoints(ptcollright);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTPOINT){
			PointPointCollection ptcoll = qResult.getPointPointCollection();
			cout<<"\nRESULT: PointPointCollection"<<endl;
			cout << "ResultSet Size : " << ptcoll.getSize() << "\n";
			for(int i=0;i<ptcoll.getSize();i++)
			{
				vector<PointPoint> tempt_ppt = ptcoll.getNext(1);
				for ( PointPoint ppt : tempt_ppt){
					cout<< "[(" << ppt.getCoordinates().at(0)<< " ," << ppt.getCoordinates().at(1) <<"),"
						<< "("<< ppt.getCoordinates().at(2)<< " ," << ppt.getCoordinates().at(3) <<") ]"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 6"<<endl;
		}

	}

   //---------------------------------------------------------------
	/*
	//Test 2
	//The return all the points whose distance is less than 5 from Point(0,0)
	qTree2.setRoot(rootnull);
	vector<vector<string> > leftfilter2;
	vector<string> left2;
	left2.push_back("filterBy");
	left2.push_back("distance");
	left2.push_back("le");
	left2.push_back("5");
	left2.push_back("0");
	left2.push_back("0");
	leftfilter2.push_back(left2);

	//copy(left.begin(),left.end(),qTree1.leftFilter.begin());
	qTree2.setLeftFilter(leftfilter2);

	PointCollection ptcol2;

	for(int i=0;i<5;i++)
		ptcol2.insert(Point(i,i));

	qTree2.setLeftPoints(ptcol2);

	qTree2.setLeftRectangles(retcolNull);
	//qTree1.setLeftIndexedObject("");
	qTree2.setRightFilter(rightfilternull);
	qTree2.setRightPoints(ptcolNull);
	qTree2.setRightRectangles(retcolNull);
	//qTree1.setRightIndexedObject("");

	qResult2 = query2.processQuery(qTree2);

	cout<<"\n-----------------Test 2------------------\n";
	if (qResult2.getResultType() == TYPE_POINT){
		PointCollection ppcol2 = qResult2.getPointCollection();
		for(int i=0;i<ppcol2.getSize();i++)
		{
			vector<Point> temp_ptv = ppcol2.getNext(1);
			for (Point pt : temp_ptv)
				cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
		}
	}
	else{
		cout << "Fail Test 2"<<endl;
	}
	//---------------------------------------------------------------
	//Test 3
	//The return all the points whose distance is less than 3 from Rectangle(0,0,2,2)
	cout<<"\n-----------------Test 3------------------\n";
	qTree3.setRoot(rootnull);
	vector<string> left3;
	vector<vector<string> > leftfilter3;
	left3.push_back("filterBy");
	left3.push_back("distance");
	left3.push_back("le");
	left3.push_back("5");
	left3.push_back("0");
	left3.push_back("0");
	left3.push_back("2");
	left3.push_back("2");
	leftfilter3.push_back(left3);

	//copy(left.begin(),left.end(),qTree1.leftFilter.begin());

	qTree3.setLeftFilter(leftfilter3);


	PointCollection ptcol3;

	for(int i=0;i<5;i++)
		ptcol3.insert(Point(i,i));

	qTree3.setLeftPoints(ptcol3);

	qTree3.setLeftRectangles(retcolNull);
	//qTree1.setLeftIndexedObject("");
	qTree3.setRightFilter(rightfilternull);
	qTree3.setRightPoints(ptcolNull);
	qTree3.setRightRectangles(retcolNull);
	//qTree1.setRightIndexedObject("");

	qResult3 = query3.processQuery(qTree3);


	if (qResult3.getResultType() == TYPE_POINT){
		PointCollection ppcol3 = qResult3.getPointCollection();
		for(int i=0;i<ppcol3.getSize();i++)
		{
			vector<Point> temp_ptv = ppcol3.getNext(1);
			for (Point pt : temp_ptv)
				cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
		}
	}
	else{
		cout << "Fail Test 3"<<endl;
	}
	//---------------------------------------------------------------
	//Test 4
	//The return all the rectangles whose distance is less than 3 from Point(0,0)
	cout<<"\n-----------------Test 4------------------\n";
	qTree4.setRoot(rootnull);
	vector<string> left4;
	vector<vector<string> > leftfilter4;
	left4.push_back("filterBy");
	left4.push_back("distance");
	left4.push_back("le");
	left4.push_back("5");
	left4.push_back("0");
	left4.push_back("0");
	leftfilter4.push_back(left4);
	//copy(left.begin(),left.end(),qTree1.leftFilter.begin());
	qTree4.setLeftFilter(leftfilter4);
	qTree4.setLeftPoints(ptcolNull);

	RectangleCollection retcol4;

	for(int i=0;i<5;i++)
		retcol4.insert(Rectangle(i,i,i+1,i+1));

	qTree4.setLeftRectangles(retcol4);
	//qTree1.setLeftIndexedObject("");
	qTree4.setRightFilter(rightfilternull);
	qTree4.setRightPoints(ptcolNull);
	qTree4.setRightRectangles(retcolNull);
	//qTree1.setRightIndexedObject("");

	qResult4 = query4.processQuery(qTree4);

	if (qResult4.getResultType() == TYPE_RECTANGLE){
		RectangleCollection rcoll4 = qResult4.getRectangleCollection();
		for(int i=0;i<rcoll4.getSize();i++)
		{
			vector<Rectangle> temp_ptv = rcoll4.getNext(1);
			for (Rectangle rt : temp_ptv){
				cout<< "[ Box : (" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
					<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<") ]"<<endl;
			}
		}
	}
	else{
		cout << "Fail Test 4"<<endl;
	}

	//---------------------------------------------------------------
	//Test 5
	//The return all the rectangles whose distance is less than 3 from rectangle(0,0,1,1)
	cout<<"\n-----------------Test 5------------------\n";
	qTree5.setRoot(rootnull);
	vector<string> left5;
	vector<vector<string> > leftfilter5;
	left5.push_back("filterBy");
	left5.push_back("distance");
	left5.push_back("le");
	left5.push_back("3");
	left5.push_back("0");
	left5.push_back("0");
	left5.push_back("1");
	left5.push_back("1");
	leftfilter5.push_back(left5);

	//copy(left.begin(),left.end(),qTree1.leftFilter.begin());
	qTree5.setLeftFilter(leftfilter5);
	qTree5.setLeftPoints(ptcolNull);

	RectangleCollection retcol5;

	for(int i=0;i<5;i++)
		retcol5.insert(Rectangle(i,i,i+2,i+2));

	qTree5.setLeftRectangles(retcol5);
	//qTree1.setLeftIndexedObject("");
	qTree5.setRightFilter(rightfilternull);
	qTree5.setRightPoints(ptcolNull);
	qTree5.setRightRectangles(retcolNull);
	//qTree1.setRightIndexedObject("");

	qResult5 = query5.processQuery(qTree5);

	if (qResult5.getResultType() == TYPE_RECTANGLE){
		RectangleCollection rcoll5 = qResult5.getRectangleCollection();
		for(int i=0;i<rcoll5.getSize();i++)
		{
			vector<Rectangle> temp_ptv = rcoll5.getNext(1);
			for (Rectangle rt : temp_ptv){
				cout<< "[ Box : (" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
					<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<") ]"<<endl;
			}
		}
	}
	else{
		cout << "Fail Test 5"<<endl;
	}

	//---------------------------------------------------------------
	//Test 6
	//Filterby left branch all points whose distance is greater than 3 from point (0,3)
	//Filterby right branch all points whose distance is less than 5 from point (0,0)
	//DistanceJoin all points whose distance is less than 5

	cout<<"\n-----------------Test 6------------------\n";
	vector<string> root6;
	root6.push_back("distanceJoin");
	root6.push_back("5");
	qTree6.setRoot(root6);

	vector<string> left6;
	vector<vector<string> > leftfilter6;
	left6.push_back("filterBy");
	left6.push_back("distance");
	left6.push_back("ge");
	left6.push_back("3");
	left6.push_back("0");
	left6.push_back("3");
	leftfilter6.push_back(left6);
	qTree6.setLeftFilter(leftfilter6);

	vector<string> right6;
	vector<vector<string> > rightfilter6;
	right6.push_back("filterBy");
	right6.push_back("distance");
	right6.push_back("lt");
	right6.push_back("0");
	right6.push_back("0");
	right6.push_back("5");
	leftfilter6.push_back(left6);
	qTree6.setRightFilter(leftfilter6);


	PointCollection ptcolleft6,ptcollright6;

	for(int i=0;i<5;i++){
		ptcolleft6.insert(Point(i,i));
		ptcollright6.insert(Point(i+2,i-1));
	}

	qTree6.setLeftPoints(ptcolleft6);
	qTree6.setRightPoints(ptcollright6);


	qTree6.setLeftRectangles(retcolNull);
	qTree6.setRightRectangles(retcolNull);

	qResult6 = query6.processQuery(qTree6);


	if (qResult6.getResultType() == TYPE_POINTPOINT){
		PointPointCollection ptcoll6 = qResult6.getPointPointCollection();
		cout << "PointPointCollection : PPC\n";
		cout << " ResultSet Size : " << ptcoll6.getSize() << "\n";
		for(int i=0;i<ptcoll6.getSize();i++)
		{
			vector<PointPoint> tempt_ppt = ptcoll6.getNext(1);
			for ( PointPoint ppt : tempt_ppt){
				cout<< "[ PPC : (" << ppt.getCoordinates().at(0)<< " ," << ppt.getCoordinates().at(1) <<"),"
					<< "("<< ppt.getCoordinates().at(2)<< " ," << ppt.getCoordinates().at(3) <<") ]"<<endl;
			}
		}
	}
	else{
		cout << "Fail Test 6"<<endl;
	}

	//---------------------------------------------------------------
	//Test 7
	//Filterby left branch all rectangles whose distance is greater than 5 from rectangle (0,1,3,4)
	//Filterby right branch all points whose distance is less than 10 from point (4,4,9,9)
	//DistanceJoin all points whose distance is less than 6

	cout<<"\n-----------------Test 7------------------\n";
	vector<string> root7;
	root7.push_back("distanceJoin");
	root7.push_back("6");
	qTree7.setRoot(root7);

	vector<string> left7;
	vector<vector<string> > leftfilter7;
	left7.push_back("filterBy");
	left7.push_back("distance");
	left7.push_back("ge");
	left7.push_back("5");
	left7.push_back("0");
	left7.push_back("1");
	left7.push_back("3");
	left7.push_back("4");
	leftfilter7.push_back(left7);
	qTree7.setLeftFilter(leftfilter7);

	vector<string> right7;
	vector<vector<string> > rightfilter7;
	right7.push_back("filterBy");
	right7.push_back("distance");
	right7.push_back("lt");
	right7.push_back("10");
	right7.push_back("4");
	right7.push_back("4");
	right7.push_back("9");
	right7.push_back("9");
	leftfilter7.push_back(left7);
	qTree7.setRightFilter(leftfilter7);


	RectangleCollection retcolleft7,retcollright7;

	for(int i=0;i<5;i++){
		retcolleft7.insert(Rectangle(i,i,i+2,i+1));
		retcollright7.insert(Rectangle(i-1,i-2,i+1,i+1));
	}

	qTree7.setLeftRectangles(retcolleft7);
	qTree7.setRightRectangles(retcollright7);

	qTree7.setLeftPoints(ptcolNull);
	qTree7.setLeftPoints(ptcolNull);

	qResult7 = query7.processQuery(qTree7);

	if (qResult7.getResultType() == TYPE_RECTANGLERECTANGLE){
		RectangleRectangleCollection retcoll7 = qResult7.getRectangleRectangleCollection();
		cout << "RectangleRectangleCollection : RRC\n";
		cout << "ResultSet Size : " << retcoll7.getSize() << "\n";
		for(int i=0;i<retcoll7.getSize();i++)
		{
			vector<RectangleRectangle> tempt_rr = retcoll7.getNext(1);
			for ( RectangleRectangle rr : tempt_rr){
				cout<< "[ RRC : Box1 ((" << rr.getCoordinates().at(0)<< " ," << rr.getCoordinates().at(1) <<"),"
					<< "("<< rr.getCoordinates().at(2)<< " ," << rr.getCoordinates().at(3) <<")) Box2 ( "
					<< "("<< rr.getCoordinates().at(4)<< " ," << rr.getCoordinates().at(5) <<"),  "
					<< "("<< rr.getCoordinates().at(6)<< " ," << rr.getCoordinates().at(7) <<")) ]\n";
			}
		}
	}
	else{
		cout << "Fail Test 7"<<endl;
	}
	*/
}

