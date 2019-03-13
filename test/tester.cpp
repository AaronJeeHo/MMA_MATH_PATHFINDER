//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"

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
}*/

/*TEST_CASE("Lets print some fight records"){
    Graph g;
    g.getData("../data/mma_records.txt");
    
    Fighter* name = g.fighters.at("nate diazs");

    for(int i = 0; i < name->wins.size(); i++){
        cout << name->wins.at(i) << endl;
    }
}*/

/*TEST_CASE("Lets print some fighter stats"){
    cout << "Getting fighter database..." << endl;
    Graph g;
    g.getData("../data/mma_records.txt");
    cout << "Database Complete" << endl;
    
    string b ("jose aldo");
    string a ("nate diaz");

    g.printPath(a,b,"./out.txt");
}*/

int main(void){
    Graph g;
    g.getData("../data/mma_records.txt");
    
    string a ("khabib nurmagomedov");
    string b ("conor mcgregor");

    g.printPath(a,b,"./out.txt");
}
