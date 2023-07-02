#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

/*
The fighter class will store all of the information of a Fighter, such as its name
and all of its moves and corresponding frame numbers in a map called moves. Last,
it will hold a sortkey whoch will tell the operator< which move to sort the Fighter by.
*/

class Fighter{
public:
    bool read(std::istream& in_str);
    int getSpeed(const std::string& move) const{return (moves.find(move))->second;}
    const std::string& getName()const {return name;}
    bool operator<(const Fighter& f) const;
    void changeKey(const std::string& key){sortkey = key;}
    const std::map<std::string, int>& getMoves()const {return moves;};
    void setSortkey(std::string s){sortkey = s;}
    bool operator==(const Fighter& f) const;
private:
    std::string name;
    std::map<std::string, int> moves;
    std::string sortkey;
};
