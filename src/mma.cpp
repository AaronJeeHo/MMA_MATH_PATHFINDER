/*
*Aaron Ho
*CSE100 Alvarado PA3
*3-6-19
*/


#include <cstdlib>
#include <cstring>
#include <string>
#include "Graph.hpp"

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " fighter_A fighter_B output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {

    if (argc != 4) {
    usage(argv[0]);
    }

    Graph g;
    g.getData("./data/mma_records.txt");
    //g.getData("./data/lightweight.txt"); //USE THIS TO MAKE A GRAPH OF LIGHTWEIGHTS ONLY

    string fighter_a = argv[1];
    string fighter_b = argv[2];
    char* output_filename = argv[3];

    g.printPath(fighter_a,fighter_b,output_filename);
}