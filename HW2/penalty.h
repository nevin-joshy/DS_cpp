#include <iostream>
#include <string>
#include <vector>

class Penalty//will hold each type of penalty as an object and record how many times
//it occurs in each period
{
public:
    Penalty();
    const std::string &get_pen() const { return penname; }//gives penalty name
    const int& get_pen_p1() const { return p1_pen; }//gives the total penalties in p1
    const int& get_pen_p2() const { return p2_pen; }//gives the total penalties in p2
    const int& get_pen_p3() const { return p3_pen; }//gives the total penalties in p3
    const int& get_pen_ot() const { return ot_pen; }//gives the total penalties in overtime
    int get_total_pens() const {return p1_pen+p2_pen+p3_pen+ot_pen;}//adds all of the
    //penalties together 
    void add_pen_p1();//increments penalties in period 1 by 1
    void add_pen_p2();//increments penalties in period 2 by 1
    void add_pen_p3();//increments penalties in period 3 by 1
    void add_pen_ot();//increments penalties in overtime by 1
    void set_name(std::string nm);//sets the name attribute of the penalty object

private:
    std::string penname;//name of the penalty
    int p1_pen;//number of occurrences in period 1
    int p2_pen;//number of occurences in period 2
    int p3_pen;//number of occurences in period 3
    int ot_pen;//number of occurences in overtime
};
bool isPenGreaterThan(const Penalty& pen1, const Penalty& pen2);//compares 2 penalty objects
//so that the penalty list can be sorted for output
void penalty_calculate(std::vector<std::string> &allwords, 
std::vector<Penalty> &penaltylist);//takes in a vector of words(all file words) and
//a list of penalty objects by reference to populate and edit the number of penalties
std::ostream& output_penalties(std::ostream& fileout, std::vector<Penalty> &penaltylist);
//organizes the output table by taking in the file stream name and a list of penalty
//objects by reference, and iterate through each object