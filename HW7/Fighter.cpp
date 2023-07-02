#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

#include "Fighter.h"

//This is the implementation of the Fighter class

//This will go through the row of the dbfile and assign the name,
//as well as creating the moves map by assigned the corresponding
//values
bool Fighter::read(std::istream& in_str){
    int jab, f_t, u_t, d_t, f_s, u_s, d_s;
    if(!(in_str>>name)) return false;
    in_str>>jab>>f_t>>u_t>>d_t>>f_s>>u_s>>d_s;
    moves.clear();
    moves["jab"] = jab;
    moves["forward-tilt"] = f_t;
    moves["up-tilt"] = u_t;
    moves["down-tilt"] = d_t;
    moves["forward-smash"] = f_s;
    moves["up-smash"] = u_s;
    moves["down-smash"] = d_s;
    return true;
}

//checks what the sortkey is, then depending on the key it will compare the
//frame value of the key's move to determine whether it is less than. If it
//is the same, then it will compare the names(compares alphabetically)
bool Fighter::operator<(const Fighter& f)const{
    if(getSpeed(sortkey)< f.getSpeed(sortkey)){
        return true;
    }
    else if(getSpeed(sortkey) == f.getSpeed(sortkey)){
        if(name<f.getName()){
            return true;
        }
    }
    return false;
}
