#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "BlastTable.h"

using namespace std;

int main(){
    string input;
    string genome;
    int table_size = 100;
    float occupancy = 0.5;
    int kmer = 0;
    while(cin>>input){
        if(input == "genome"){
            cin>>genome;
            //read in genome file
            std::ifstream genomefile(genome);
	        if(!genomefile){
		        std::cerr << "Failed to open database " << genome << " for reading." 
		        << std::endl;
	        }
            string line;
            genome = "";
            //make 1 long string with genome file
            while(genomefile>>line){
                genome+=line;
            }
        }  
        else if(input == "table_size")
            cin>>table_size;
        else if(input=="occupancy")
            cin>>occupancy;
        else if(input=="kmer"){
            cin>>kmer;
            break;
        }
    }
    //create and fill table
    BlastTable blasthash = BlastTable(genome, kmer, table_size, occupancy);
    blasthash.filltable();
    int mismatch;
    string query;
    while(cin>>input){
        if(input=="query"){
            cin>>mismatch>>query;
            blasthash.find(mismatch, query);
        }
        else if(input == "quit")
            break;
    }
}