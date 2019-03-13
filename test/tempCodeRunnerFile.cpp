#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "../src/Graph.hpp"
#include "../src/Graph.cpp"
#include "../src/Fighter.hpp"

/*TEST_CASE("Lets print the fighters"){
    Graph g;
    g.getData("../data/mma_records.txt");
    
    for (std::unordered_map<string,Fighter*>::iterator it = g.fighters.begin(); it!=g.fighters.end(); ++it){//iterate through nodes
        cout << it->first << endl;
    }