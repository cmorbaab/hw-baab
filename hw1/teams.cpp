#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

string getTeam2(string data, string team1, int team_size){
  string * team1_d = (string*) calloc (team_size, sizeof(string)) ;
  string* copy = team1_d ;
  istringstream iss (team1) ;
  for (int i = 0 ; i < team_size; i++){
    string c ;
    iss >> c;
    *copy = c ;
    copy++ ;
  }

  string team2 ;
  istringstream all (data) ;
  string curr1 ;
  string curr2 ;
  bool both = false;
  while(1){
    all >> curr1 ;
    if(all.fail()) break ;
    for (int i = 0; i < team_size; i++){
      curr2 = team1_d[i];
      if(curr1 == curr2){
        both = true ;
      }
    }
    if(!both){
      team2 = team2 + " " + curr1 ;
    }
    both = false ;
  }

  free(team1_d) ;
  return team2 ;
}
// You may add additional functions here
int generateComb(string* data, string team1, int curr_size, int depth, int team_size, string all){
  string element ;
  if (depth != team_size*2){
    element = *data ;
    data++ ;
    depth++ ;
  }

  //first element in team 1:
  if (curr_size == team_size){
    string temp =  getTeam2(all,team1, team_size) ;
    string* _team1 = (string*) calloc (team_size, sizeof(string)) ;
    string* _team2 = (string*) calloc (team_size, sizeof(string)) ;
    istringstream one (team1) ;
    istringstream two (temp) ;
    string c ;
    for (int i = 0; i < team_size; i++){
      one >> c ;
      *_team1 = c ;
      _team1++ ;
    }
    for (int i = 0; i < team_size; i++){
      two >> c ;
      *_team2 = c;
      _team2++ ;
    }
    for (int i = 0; i < team_size; i++){
      _team1-- ;
      _team2-- ;
    }
    const string* _t1 = _team1 ;
    const string* _t2 = _team2 ;
    
    printSolution(_t1,_t2,team_size) ;
    free(_team1) ;
    free(_team2) ;
    one.clear() ;
    two.clear() ;

  }
  else{
    string temp = team1 + " " + element ;
    //Actually a real element has been added
    if (element != ""){
      generateComb(data, temp, curr_size + 1, depth, team_size, all) ;
    }

    if (depth != team_size*2){
      generateComb(data, team1, curr_size, depth, team_size, all) ;
    }

  }
  return 0;

}


int main(int argc, char* argv[])
{
  if(argc < 2){
    //cerr << "Please provide a file of names" << endl;
    return 1;
  }
  ifstream ifile(argv[1]);
  if(ifile.fail()){
    //cerr << "Error" << endl;
    return 1;
  }
  int num ;
  string name ;
  ifile >> num ;
  if(ifile.fail()){
    //cout << "Error" << endl ;
    return 1 ;
  } 
  //Dynamically allocate data
  string * data ;
  data = (string*) calloc (num, sizeof(string)) ;
  string all ;
  //Read in names and assign them into the data
  for (int i = 0 ; i < num ; i++){
    ifile >> name ;
    //If one of the inputs is not a string, fail
    if(ifile.fail()){
      //cout << "Error" << endl ;
      return 1;
    }
    all = all + " " + name ;
    *data = name ;
    data++;
  }
  //reset to the start
  data = data - num;
  string team1 = "" ;
  generateComb(data, team1, 0, 0,  num/2, all) ;

  free(data) ;





  return 0;
}
