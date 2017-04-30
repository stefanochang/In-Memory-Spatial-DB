#ifndef INTEGRATION_HELPER_H
#include "integration-helper.h"
#endif

#include <iostream>

using namespace std;



int main() {
    while(1) {
        string query;
        cout << endl << "Enter your query: ";
        getline (cin, query);
        parseQuery(query);
    }
    return 0;
}
