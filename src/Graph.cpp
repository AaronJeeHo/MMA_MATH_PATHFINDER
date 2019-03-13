/*
*Aaron Ho
*MMAMATH
*3-12-19
*Ver 1.0
*/

#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

Graph::Graph(void):fighters(0) {}

Graph::~Graph(void) {
  for (auto itr : fighters) {
    delete itr.second;
  }
}

void Graph::insertFighter(string name){

  std::unordered_map<string,Fighter*>::const_iterator got = fighters.find(name);

  if(got == fighters.end()){//if node does not exists in graph
  
    Fighter* insert = new Fighter(name);//make node
    std::pair<string,Fighter*> keyPair(name,insert);//create its key value pair
    fighters.insert(keyPair);
  }
  else{
    return;
  }

}

int Graph::parseWin(string win){

  string ko ("KO"); //return 0
  string sub ("Submission");//return 1
  string dec ("Decision");//return 2

  if(win.find(ko) != std::string::npos){
    return 0;  
  }
  else if(win.find(sub) != std::string::npos){
    return 1;  
  }
  else if(win.find(dec) != std::string::npos){
    return 2;  
  }
  else{
    return 3;
  }

}

void Graph::getFighterData(Fighter* name,const char* out_filename){
  int win_num = name->win_record.at(0) + name->win_record.at(1) +
  name->win_record.at(2) + name->win_record.at(3);

  int loss_num = name->loss_record.at(0) + name->loss_record.at(1) +
  name->loss_record.at(2) + name->loss_record.at(3);
  int ko_num = name->win_record.at(0);
  int sub_num = name->win_record.at(1);
  int dec_num = name->win_record.at(2);
  int other_num = name->win_record.at(3);

  ofstream writeFile;//open output file
  writeFile.open(out_filename,std::ios::app);

  writeFile << "Fighter: " << name->name << endl; 
  writeFile << win_num << " Wins / " << loss_num << " Losses" << endl;

  if(ko_num != 0){
    writeFile << "KO Wins: " << ko_num << endl;
  }

  if(sub_num != 0){
    writeFile << "Submission Wins: " << sub_num << endl;
  }

  if(dec_num != 0){
    writeFile << "Decision Wins: " << dec_num << endl;
  }

  if(other_num != 0){
    writeFile << "Other wins" << other_num << endl;
  }

  writeFile.close();
}

void Graph::getData(const char* in_filename){
    ifstream infile(in_filename);

    while (infile){
        string s;

        if(!getline(infile, s)){
            break;
        }
        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string s;
            if (!getline(ss, s, '\t')) break;
            record.push_back(s);
        }

        if (record.size() != 4) {
            continue;
        }

        string name = record.at(0);
        string opponent = record.at(1);
        int win_method = parseWin(record.at(2));
        //int round_won = stoi(record.at(3));
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::transform(opponent.begin(), opponent.end(), opponent.begin(), ::tolower);

        insertFighter(name);
        insertFighter(opponent);

        Fighter* & currFighter = fighters.at(name);
        Fighter* & oppFighter = fighters.at(opponent);
        currFighter->wins.push_back(opponent);//insert opponent name
        currFighter->win_record.at(win_method) +=1;//set fighter wins
        oppFighter->loss_record.at(win_method) +=1;//set opponent losses


    }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return;
  }

  infile.close();
}

vector<string> Graph::findPath(string a, string b){

  vector<string> returnVec;
  Fighter* &opponent = fighters.at(b);

  for (std::unordered_map<string,Fighter*>::iterator it = fighters.begin(); it!=fighters.end(); ++it){//iterate through nodes
    it->second->lost_to = " ";//did not lose to anyone yet
  }

  if(opponent->loss_record.at(0) + opponent->loss_record.at(1) +
  opponent->loss_record.at(2) + opponent->loss_record.at(3) == 0){
    vector<string> undefeated;//should be a 0 vector
    return undefeated;
  }

  queue<string> toExplore;
  toExplore.push(a);
  string curr_name;

  while(!toExplore.empty()){

    curr_name = toExplore.front();
    cout << curr_name << endl;
    Fighter* &curr = fighters.at(curr_name);

    if(!curr_name.compare(b)){

      stack<string> fightPath;

      while((curr->lost_to).compare(" ")){
        fightPath.push(curr->lost_to);
        curr = fighters.at(curr->lost_to);
      }
      while(!fightPath.empty()){
        returnVec.push_back(fightPath.top());
        fightPath.pop();
      }
      return returnVec;
    } 

    for(int i = 0; i < curr->wins.size(); i++ ){
      (fighters.at(curr->wins.at(i)))->lost_to = curr_name;
      toExplore.push(curr->wins.at(i));
    }
    toExplore.pop();
  } 
}



void Graph::printPath(string a, string b, const char* out_filename){

  ofstream writeFile;//open output file
  writeFile.open(out_filename);
  writeFile.close();

  Fighter* &fighter_a = fighters.at(a);
  Fighter* &fighter_b = fighters.at(b);

  getFighterData(fighter_a,out_filename);
  writeFile.open(out_filename,std::ios::app);
  writeFile << endl;
  writeFile << "==============VS==============" << endl;
  writeFile << endl;
  writeFile.close();
  getFighterData(fighter_b,out_filename);

  writeFile.open(out_filename,std::ios::app);
  writeFile << endl;
  vector<string> a_path = findPath(a,b);

  for(int i = 0; i < a_path.size(); i++){
    writeFile << a_path.at(i) << " ";
  }

  writeFile.close();




  //writeFile.close(); 
}



