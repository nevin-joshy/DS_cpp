#ifndef __BlastTable_h_
#define __BlastTable_h_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*
BlastTable is a class that hold all of the information of the hash table including the
table itself. It has a member fuction hash_func that takes in a kmer and helps find the 
index in the hash table that it should be placed in. The has table is a vector or vector 
of pairs. Linear probing is used in the insert function so that there are no collisions,
except for with repeats of a kmer which will be in the same sub-vector for easy access
in the find function
*/

class BlastTable{
public:
    BlastTable(string gen, int kmer_size, unsigned int init_size, float occupancy) : 
        m_kmer(kmer_size), genome(gen), m_table(init_size), m_occupancy(occupancy) {}
    void filltable();
    void insert(const pair<string, int>& key);
    void print();
    void find(int mismatch, const string& q_string);
private:
    int m_kmer;
    string genome;
    vector<vector<pair<string, int> > > m_table;
    float m_occupancy;
    int m_size = 0;
    void resize_table(unsigned int new_size);
    int hash_func(const string& kmer);
};


#endif

