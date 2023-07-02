#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "Fighter.h"

//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = 
{"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here
void qcommand(std::string fighter, std::string move, 
 std::map<std::string, Fighter>& all_fighters,std::set<std::string>& allmoves,
 std::ostream& out_str);
void fscommand(std::string key, std::string move, std::string limit, 
 std::map<std::string, Fighter>& all_fighters, std::set<std::string>& allmoves,
 std::ostream& out_str);
void dcommand(std::string move, std::string frame, 
 std::map<std::string, Fighter>& all_fighters, std::set<std::string>& allmoves,
 std::ostream& out_str);

int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] 
		<< " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." 
		<< std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}
	///////Fill in the rest of main below:
	std::map<std::string, Fighter> all_fighters;
	Fighter afighter;
	std::set<std::string> allmoves;
	//creates set with moves from array
	for(int i = 0; i<7; i++){
		allmoves.insert(move_names[i]);
	}
	int counter = 0;
	std::string word;
	//parses through header of database file
	while(counter<8){
		dbfile>>word;
		counter++;
	}
	//reads through file, editing aFighter through the dbfile and adding copy to the map
	while(afighter.read(dbfile)){
		all_fighters[afighter.getName()] = afighter;
	}
	std::string key;
	std::string object;
	std::string last;
	//parses query file(infile)
	while(infile>>key){
		infile>>object>>last;
		if(key=="-q"){
			qcommand(object, last, all_fighters, allmoves, outfile);
		}
		else if(key=="-f"||key=="-s"){
			fscommand(key, object, last, all_fighters, allmoves, outfile);
		}
		else if(key == "-d"){
			dcommand(object, last, all_fighters, allmoves, outfile);
		}
		else{
			std::cout<<"Command "<<key<<" not recognized"<<std::endl;
			std::cout<<std::endl;
		}
	}
	return 0;
}
//takes in the name of the fighter and the move and outputs necessary information
//to out_str, which will be the outfile
void qcommand(std::string fighter, std::string move, 
 std::map<std::string, Fighter>& all_fighters,std::set<std::string>& allmoves,
 std::ostream& out_str){
	//sees if fighter is valid by using find which is logf runtime
	if(all_fighters.find(fighter) == all_fighters.end()){
		out_str<<"Invalid character name: "<<fighter<<std::endl;
		out_str<<std::endl;
		return;
	}
	std::map<std::string,Fighter>::iterator itr = all_fighters.find(fighter);
	std::map<std::string,int> moves = (itr->second).getMoves();
	//prints all of the move info for the fighter if the move is all
	if(move == "all"){
		for(std::map<std::string,int>::iterator moveitr = moves.begin();
			moveitr!=moves.end(); moveitr++){
			out_str<<(itr->second).getName()<<" "<<moveitr->first<<": "<<moveitr->second
			<<std::endl;
		}
		out_str<<std::endl;
	}
	else{
		//checks for invalid move using find, so log time
		if(allmoves.find(move) == allmoves.end()){
			out_str<<"Invalid move name: "<<move<<std::endl;
			out_str<<std::endl;
			return;
		}
		//because specific move given, only print this move's info
		std::map<std::string,int>::iterator moveitr = moves.find(move);
		out_str<<itr->first<<" "<<moveitr->first<<": "<<moveitr->second<<std::endl;
		out_str<<std::endl;
	}	
}

//takes in the key, move, and limit and outputs necessary information
//to out_str, which will be the outfile
void fscommand(std::string key, std::string move, std::string limit, 
 std::map<std::string, Fighter>& all_fighters, std::set<std::string>& allmoves,
 std::ostream& out_str){
	//sees if move is valid by using find which is logf runtime	
	if(allmoves.find(move) == allmoves.end()){
		out_str<<"Invalid move name: "<<move<<std::endl;
		out_str<<std::endl;
		return;
	}
	std::map<std::string,Fighter>::iterator itr = all_fighters.begin();
	//framemap will hold the frame speed of the move on left and set of the fighters with
	//that speed on the right, sorted alphabetically through < function
	std::map<int,std::set<Fighter> > framemap;
	int counter = stoi(limit);
	out_str<<key<<" "<<move<<" "<<limit<<std::endl;
	//sets the sortkey of the fighter to the correct move, and inserts them into the
	//framemap at their frame speed
	for( ; itr!= all_fighters.end();itr++){
		(itr->second).setSortkey(move);
		framemap[(itr->second).getSpeed(move)].insert(itr->second);
	}
	//cycles through top of the map until counter, which is the limit is 0 and outputs
	//fighter
	if(key=="-f"){
		std::map<int,std::set<Fighter> >::iterator frameitr = framemap.begin();
		while(counter>0 && frameitr!= framemap.end()){
			std::set<Fighter>::iterator setitr = (frameitr->second).begin();
			while(counter>0 &&setitr!=(frameitr->second).end()){
				out_str<<setitr->getName()<<" "<<setitr->getSpeed(move)<<std::endl;
				counter--;
				setitr++;
			}
			frameitr++;
		}
		out_str<<std::endl;
	}
	//cycles through bottom of the map until counter, which is the limit is 0 and outputs
	//fighter using reverse iterator
	else if(key=="-s"){
		std::map<int,std::set<Fighter> >::reverse_iterator frameitr = framemap.rbegin();
		while(counter>0 && frameitr!= framemap.rend()){
			std::set<Fighter>::iterator setitr = (frameitr->second).begin();
			while(counter>0 &&setitr!=(frameitr->second).end()){
				out_str<<setitr->getName()<<" "<<setitr->getSpeed(move)<<std::endl;
				counter--;
				setitr++;
			}
			frameitr++;
		}
		frameitr++;
		out_str<<std::endl;
	}
}

//takes in the move and frame number and outputs necessary information
//to out_str, which will be the outfile
void dcommand(std::string move, std::string frame, 
 std::map<std::string, Fighter>& all_fighters, std::set<std::string>& allmoves,
 std::ostream& out_str){
	//sees if move is valid by using find which is logf runtime
	if(allmoves.find(move) == allmoves.end()){
			out_str<<"Invalid move name: "<<move<<std::endl;
			out_str<<std::endl;
			return;
	}
	out_str<<"-d "<<move<<" "<<frame<<std::endl;
	std::map<std::string,Fighter>::iterator itr = all_fighters.begin();
	//loops through all the fighters and prints the ones that have the given frame
	for( ; itr!= all_fighters.end();itr++){
		if((itr->second).getSpeed(move) == stoi(frame)){
			out_str<<(itr->second).getName()<<std::endl;
		}
	}
	out_str<<std::endl;
}
