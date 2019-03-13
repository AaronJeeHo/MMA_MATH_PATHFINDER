#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include <string>
#include <vector>

using namespace std;

class Fighter {
public:
    string name;
    string lost_to;
    vector<string> wins;
    vector<int> win_record;
    vector<int> loss_record;


    Fighter(string name): name(name), wins(0), win_record(4,0),loss_record(4,0),lost_to(" "){
        
    }

};

#endif