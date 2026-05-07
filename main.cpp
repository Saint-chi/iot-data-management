#include <iostream>
#include "Header.h"
#include <fstream>
#include <sstream>

using namespace std;


int main() {
    management m;
    m.load("iot-shard.txt");
    cout << "DATA LOADED" << endl;
    cout << m << endl;
    cout << "TESTING PARTITIONING" << endl;
    m.partition();

    cout << "PAIR CONTAINER" << endl;
    PairContainer<int, double> container = m.extractColValues("id.orig_p", "flow_duration");
    cout << container << endl;
    cout << "ANALYZING FLOWS" << endl;
    m.analyzeflows(container);




}