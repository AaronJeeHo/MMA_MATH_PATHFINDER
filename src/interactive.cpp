/*
*Aaron Ho
*A12673241
*CSE100 Alvarado PA3
*3-6-19
*/


#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "Graph.hpp"

using namespace std;

/*void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " fighter_A fighter_B output_file"
       << endl;
  exit(-1);
}*/

int main(int argc, char* argv[]) {

    Graph g;
    g.getData("./data/mma_records.txt");
    char* output_filename = "./output.txt";

    string fighter_a;
    string fighter_b;

    cout << "Please enter the name of fighter A" << endl;
    std::getline(std::cin, fighter_a);

    while(g.fighters.find(fighter_a) == g.fighters.end()){
        cout << "Fighter not found, please enter another name" << endl;
        std::getline(std::cin, fighter_a);
    }

    cout << "Please enter the name of fighter B" << endl;
    std::getline(std::cin, fighter_b);

    while(g.fighters.find(fighter_b) == g.fighters.end()){
        cout << "Fighter not found, please enter another name" << endl;
       std::getline(std::cin, fighter_b);
    }

    g.printPath(fighter_a,fighter_b,output_filename);

    cout << "Open output.txt" << endl;
}