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
  /*int win_num = name->win_record.at(0) + name->win_record.at(1) +
  name->win_record.at(2) + name->win_record.at(3);*/

  int win_num = name->wins.size();
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

void Graph::victoryResult(Fighter* a, string &result){
  int num_wins = a->wins.size();

  double ko_rate = (a->win_record.at(0));
  double sub_rate = (a->win_record.at(1));
  double dec_rate = (a->win_record.at(2));
  double avg_round = (a->rounds)/num_wins;

  if(avg_round > 4.5){
    avg_round = 5;
  }
  else{
    avg_round = (int)avg_round;
  }

  vector<double> rates;
  rates.push_back(ko_rate);
  rates.push_back(sub_rate);
  rates.push_back(dec_rate);

  double max = *max_element(rates.begin(), rates.end());

  if(max == ko_rate){
    result = "wins by KO in round ";
    result = result + to_string(avg_round);
  }
  else if(max == sub_rate){
    result =  "wins by submission in round ";
    result = result + to_string(avg_round);
  }
  else{
    result = "wins by decision";
  }

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

        //currFighter->rounds += round_won;
    }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return;
  }

  infile.close();
}


void Graph::findPath(string a, string b, vector<string> &vec){

  Fighter* opponent = fighters.at(b);

  for (std::unordered_map<string,Fighter*>::iterator it = fighters.begin(); it!=fighters.end(); ++it){//iterate through nodes
    it->second->lost_to = " ";//did not lose to anyone yet
    it->second->visited = false;
  }

  if(opponent->loss_record.at(0) + opponent->loss_record.at(1) +
  opponent->loss_record.at(2) + opponent->loss_record.at(3) == 0){
    //vector<string> undefeated();//should be a 0 vector
    return;
  }

  queue<string> toExplore;
  toExplore.push(a);
  string curr_name;
  //cout << a << " loop reached this far" << endl;

  while(!toExplore.empty()){
    

    curr_name = toExplore.front();
    Fighter* curr = fighters.at(curr_name);
      //cout << a << " loop curr: " << curr_name << endl;
    if(!curr_name.compare(b)){

      stack<string> fightPath;

      while((curr->name).compare(a)){
        fightPath.push(curr->name);
        curr = fighters.at(curr->lost_to);
      }
      fightPath.push(curr->name); 

      while(!fightPath.empty()){
        vec.push_back(fightPath.top());
        fightPath.pop();
      }
      return;
    } 

    //cout << fighters.at("conor mcgregor")->visited << endl;
    for(int i = 0; i < curr->wins.size(); i++ ){
     /* if(!(fighters.at(curr->wins.at(i)))->name.compare("conor mcgregor")){
        //cout << "found conor" << endl;
      }*/

      if((fighters.at(curr->wins.at(i)))->visited == false){
        //cout << a << " loop reached this far" << endl;

          (fighters.at(curr->wins.at(i)))->lost_to = curr_name;
          (fighters.at(curr->wins.at(i)))->visited = true;
          toExplore.push(curr->wins.at(i));
      }
    }
    toExplore.pop();
  } 
}



void Graph::printPath(string a, string b, const char* out_filename){

  ofstream writeFile;//open output file
  writeFile.open(out_filename);
  writeFile.close();

  Fighter* fighter_a = fighters.at(a);
  Fighter* fighter_b = fighters.at(b);

  writeFile.open(out_filename,std::ios::app);
  writeFile << "=========FIGHTER STATS=========" << endl;
  writeFile << endl;

  writeFile.close();

  getFighterData(fighter_a,out_filename);
  writeFile.open(out_filename,std::ios::app);
  writeFile << endl;
  writeFile << "--------------VS--------------" << endl;
  writeFile << endl;
  writeFile.close();
  getFighterData(fighter_b,out_filename);

  writeFile.open(out_filename,std::ios::app);
  writeFile << endl;
  writeFile << endl;
  writeFile << "=======PATHS TO VICTORY=======" << endl;
  writeFile << endl;
  vector<string> a_path;
  findPath(a,b,a_path);


  writeFile << a << ":" << endl;
  writeFile << "------------------------------" << endl;

  if(a_path.size() == 0){
    writeFile << "no path to victory";
  }

  for(int i = 0; i < a_path.size(); i++){
    writeFile << a_path.at(i);
    if(i != a_path.size()-1){
      writeFile << "->";
    }
  }
  writeFile << endl;
  writeFile << endl;
  //writeFile << "------------------------------" << endl;


  writeFile << endl;
  vector<string> b_path;
  findPath(b,a,b_path);


  writeFile << b << ":" << endl;
  writeFile << "------------------------------" << endl;

  if(b_path.size() == 0){
    writeFile << "no path to victory";
  }

  for(int i = 0; i < b_path.size(); i++){
    writeFile << b_path.at(i);
    if(i != b_path.size()-1){
      writeFile << "->";
    }
  }
  writeFile << endl;
  writeFile << endl;
  //writeFile << "------------------------------" << endl;
  writeFile.close();

  string winner;
  string result;
  if(a_path.size() == 0){
    winner = b;
    victoryResult(fighter_b,result);
  }
  else if(b_path.size() == 0){
    winner = a;
    victoryResult(fighter_a,result);
  }
  else if(a_path.size() <= b_path.size()){
    winner = a;
    victoryResult(fighter_a,result);
  }
  else{
    winner = b;
    victoryResult(fighter_b,result);
  }

  writeFile.open(out_filename,std::ios::app);
  writeFile <<endl;
  writeFile << "============RESULT============" << endl;
  writeFile << endl;
  writeFile << winner << " " << result;
  writeFile.close();

  cout << "Analysis finished for: " << a << " vs " << b << endl;

}



