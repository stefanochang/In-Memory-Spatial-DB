#ifndef INTEGRATION_HELPER_H
#include "integration-helper.h"
#endif

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc,char *argv[]) {

    string fileName = "sampleQueries.txt";
    bool pauseAfterQueryExec = false;
    if(argc > 1) {
        fileName = argv[1];
    }
    if(argc > 2) {
        pauseAfterQueryExec = strcmp(argv[2], "pause") == 0;
    }
    ifstream testFileReader;
    testFileReader.open(fileName);
    string query;
    if (testFileReader.is_open()) {
        while (!testFileReader.eof()) {
            getline(testFileReader, query);
            cout << "\n\nEXECUTING: " << query << endl;
            if(pauseAfterQueryExec) {
                cin.get();
            }
            parseQuery(query);
        }
    }
    testFileReader.close();
    return 0;
}
