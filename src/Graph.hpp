#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
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

    void victoryResult(Fighter* a,string &result);

    void getFighterData(Fighter* name, const char* out_filename);

    void printPath(string a, string b, const char* out_filename);

    void findPath(string a, string b, vector<string> &vec);
};

#endif