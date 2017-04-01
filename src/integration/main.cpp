#include "data-storage.h"
#include <iostream>

using namespace std;
int get_geom_type_from_string(string geom) {
    if(geom.compare("POINT") == 0) return 1;
    if(geom.compare("RECTANGLE") == 0) return 2;
    cout << "Invalid Parameter for geometry type.\n"; 
    return -1;
}

bool is_param_sufficient(vector<string> tokens, int required_params) {
    if(tokens.size() < required_params) {
        cout << "Insufficient Parameters\n";   
        return false;
    }
    return true;
}

vector<string> split(string str,string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

int main() {
    while(1) {
        string query, cmd;
        cout << "\nPlease, enter your query: ";
        getline (cin, query);
        vector<string> query_tokens = split(query, " ");            
        if(query_tokens[0].compare("LOAD") == 0) {            
            if(is_param_sufficient(query_tokens, 6)) { 
                int collection_structure = 1;
                //loadData(query_tokens[1], query_tokens[2], query_tokens[3], query_tokens[4], collection_structure);                 
                cout << "Loaded " << query_tokens[3] << " data collection into " << query_tokens[1] << "." << query_tokens[2] <<
                 " from " << query_tokens[4]; 
            }
        }  else  if(query_tokens[0].compare("CREATE") == 0) {
            if(is_param_sufficient(query_tokens, 3)) {
                if(query_tokens[1].compare("SPATIAL-INDEX")) {
                    //Class name unknown.
                } else if(query_tokens[1].compare("DATA-INDEX")) {
                    //Class name unknown.
                } else {
                    cout << "Invalid index type.\n";                             
                }

            }      
        } else if(query_tokens[0].compare("SELECT") == 0) {    
            string query_param = query.substr(7);
            int left_param_end = query.substr(7).find("]");     
            string left_param = query_param.substr(1, left_param_end-1);

            int root_param_end = query_param.substr(left_param_end + 1).find("]");     
            string root_param = query_param.substr(
                left_param_end + query_param.substr(left_param_end).find("[") + 1, 
                root_param_end-2);

            int right_param_end = query_param.substr(left_param_end + root_param_end + 2).find("]");     
            string right_param = query_param.substr(
                left_param_end + root_param_end + 
                query_param.substr(left_param_end + root_param_end).find("[") + 1, 
                right_param_end-2);

            //QueryTree query_param_tree = new QueryTree();
            /*Root Parameter */
            vector<string> root_param_vector = split(root_param, "|");
            vector<string> root;
            if(root_param_vector.size() > 1 ){
                root.push_back(root_param_vector[0]);
                root_param_vector = split(root_param_vector[1], ":");
                root.insert(root.end(), root_param_vector.begin(), root_param_vector.end());                
                //query_param_tree.set_root(root);
            }            

            //PointCollection leftPoints, rightPoints;
            //RectangleCollection leftRectangle, rightRectangle;
            //SpatialIndexInterface leftData, rightData;

            /*Left Parameter */
            vector<string> left_param_vector = split(left_param, "|");
            bool isLeftPoint = false; 
            vector<string> left_collection_meta_data = split(left_param_vector[0], " ");
            if(left_collection_meta_data[0].compare("RECTANGLE") == 0) {
                //leftRectangles = Catalog.getRectanlgesByName(left_collection_meta_data[1])
            } else{
                isLeftPoint = true;
                //leftPoints = Catalog.getPointsByName(left_collection_meta_data[1])
            }

            bool isLeftIndexed = false;
            if(left_param.find("WITH-SPATIAL-INDEX") != string::npos) {
                isLeftIndexed = true;
                if(isLeftPoint) {
                    //leftData.createIndex(leftPoints)
                } else {
                    //leftData.createIndex(leftRectangles)
                }                
                //query_param_tree.set_left_indexed_object(leftData);

            } else if(left_param.find("WITH-DATA-INDEX") != string::npos) {
                isLeftIndexed = true;                
                if(isLeftPoint) {
                    //leftData.createIndex(leftPoints)
                } else {
                    //leftData.createIndex(leftRectangles)
                }                
                //query_param_tree.set_left_indexed_object(leftData);
            } else {
                if(isLeftPoint) {
                    //query_param_tree.set_left_points(leftPoints);
                } else {
                    //query_param_tree.set_left_rectangles(leftRectangles);
                }
            }

            left_param_vector = split(left_param_vector[1], ":");
            //query_param_tree.set_left_filter(left_param_vector);

             /*Right Parameter */
            vector<string> right_param_vector = split(right_param, "|");
            bool isRightPoint = false; 
            vector<string> right_collection_meta_data = split(right_param_vector[0], " ");
            if(right_collection_meta_data[0].compare("RECTANGLE") == 0) {
                //rightRectangles = Catalog.getRectanlgesByName(right_collection_meta_data[1])
            } else{
                isRightPoint = true;
                //rightPoints = Catalog.getPointsByName(right_collection_meta_data[1])
            }

            bool isRightIndexed = false;
            if(right_param.find("WITH-SPATIAL-INDEX") != string::npos) {
                isRightIndexed = true;
                if(isRightPoint) {
                    //rightData.createIndex(rightPoints)
                } else {
                    //rightData.createIndex(rightRectangles)
                }                
                //query_param_tree.set_right_indexed_object(rightData);

            } else if(right_param.find("WITH-DATA-INDEX") != string::npos) {
                isRightIndexed = true;                
                if(isRightPoint) {
                    //rightData.createIndex(rightPoints)
                } else {
                    //rightData.createIndex(rightRectangles)
                }                
                //query_param_tree.set_right_indexed_object(rightData);
            } else {
                if(isRightPoint) {
                    //query_param_tree.set_right_points(rightPoints);
                } else {
                    //query_param_tree.set_right_rectangles(rightRectangles);
                }
            }

            right_param_vector = split(right_param_vector[1], ":");
            //query_param_tree.set_right_filter(right_param_vector);
            cout << "Processing Query.."
            //QueryResults results = processQuery(query_param_tree);

        } else {
            cout << "Invalid command\n";        
        }
    }
    return 0;
}