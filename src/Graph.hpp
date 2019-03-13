#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include "Fighter.hpp"

using namespace std;

class Graph{
    public:
    std::unordered_map<string,Fighter*> fighters;

    Graph(void);//constructor

    ~Graph(void);//destructor

    void getData(const char* in_filename);

    void insertFighter(string name);

    int parseWin(string win);

    void getFighterData(Fighter* name, const char* out_filename);

    void printPath(string a, string b, const char* out_filename);

    vector<string>findPath(string a, string b);
};

#endif