#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "BlastTable.h"

//This is the implementation of the BlastTable class

//hash function from lecture which is used for strings.
int BlastTable::hash_func(const string& kmer){
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < kmer.length(); i++)
      hash ^= ((hash << 5) + kmer[i] + (hash >> 2));
    return hash;
}

//takes in a size that the table should be resized to and copys/rehashes
//the data for the new size
void BlastTable::resize_table(unsigned int new_size){
    vector<vector<pair<string, int> > > new_table(new_size);
    for(unsigned int i = 0; i<m_table.size(); i++){
        for(unsigned int j = 0; j<m_table[i].size(); j++){
            int index = hash_func(m_table[i][j].first) % new_table.size();
            //if vector already has elements
            while(new_table[index].size() > 0){
                //if over the table size, go back to 0
                if(index>=int(new_table.size())){
                    index = 0;
                    continue;
                }
                //check that the vector has the same kmer as the one
                //we are trying to insert
                if(new_table[index][0].first == m_table[i][j].first)
                    break;
                index++;
            }
            //adds pair whether at empty vector or at vector with same kmers
            new_table[index].push_back(m_table[i][j]);
        } 
    }
    //redefine table
    m_table = new_table;
}

void BlastTable::filltable(){
    //go through each set of kmer letters to create keys
    for(int i = 0; i<(int(genome.size())-m_kmer); i++){
        string line = genome.substr(i,m_kmer);
        insert({line, i});
    }
}

void BlastTable::insert(const pair<string, int>& key){
    //calculate current occupancy and resize of over given max occupancy
    float ratio = float(m_size)/float(m_table.size());
    if(ratio>m_occupancy)
        resize_table(m_table.size() * 2);
    int index = hash_func(key.first) % m_table.size();
    //if vector already has elements
    while(m_table[index].size() > 0){
        //if over the table size, go back to 0
        if(index>=int(m_table.size())){
            index = 0;
            continue;
        }
        //check that the vector has the same kmer as the one
        //we are trying to insert
        if(m_table[index][0].first == key.first)
            break;                                                                                                                          
        index++;
    }
    //add 1 to size if the vector was empty
    if(m_table[index].size()==0)
        m_size++;
    m_table[index].push_back(key);
}

void BlastTable::print() {
    for (unsigned int i=0; i<m_table.size(); ++i) {
      cout << i << ": ";
      for (unsigned int j = 0; j< m_table[i].size(); ++j)
        cout << ' ' << m_table[i][j].first << " "<< m_table[i][j].second;
      cout << std::endl;
    }
}

void BlastTable::find(int mismatch, const string& q_string){
    cout<<"Query: "<<q_string<<endl;
    //define first kmer letters, to search
    string kmer = q_string.substr(0,m_kmer);
    int index = hash_func(kmer) % m_table.size();
    //if vector already has elements
    while(m_table[index].size()>0){
        //if over the table size, go back to 0
        if(index>=int(m_table.size())){
            index = 0;
            continue;
        }
        //if the pairs in the vector have the same kmer as the search key,
        //break because index match found
        if(m_table[index][0].first == kmer)
            break;
        index++;
    }
    //if the vector was empty then there is no match
    if(m_table[index].size() == 0){
        cout<<"No Match"<<endl;
    }
    //if found the search key in the hash table
    else if(m_table[index][0].first == kmer){
        bool found = false;
        //check each index of the matched vector for a match in the genome
        for(unsigned int i = 0; i<m_table[index].size(); i++){
            int genindex = m_table[index][i].second;
            int num_mist = 0;
            int add = 0;
            //go through the genome index while there are not too many mistakes
            //and we have not gone over the size of the query string and not 
            //over the size of the genome
            while(num_mist<=mismatch && (m_kmer + add)<int(q_string.size()) && 
            (genindex + m_kmer + add)<int(genome.size())){
                //if the charectars do not match, add a mistake
                if(genome[genindex + m_kmer + add] != q_string[m_kmer + add]){
                    num_mist++;
                }
                add++;
            }
            //if not too many mistakes, at full query size and not over genome size,
            //print that there is a match
            if(num_mist<=mismatch && (m_kmer + add)==int(q_string.size()) && 
            (genindex + m_kmer + add)<=int(genome.size())){
                cout<<genindex<<" "<<num_mist<<" "<<
                    genome.substr(genindex,(m_kmer + add))<<endl;
                found = true;
            }
        }
        if(!found)
            cout<<"No Match"<<endl;
    }
}
