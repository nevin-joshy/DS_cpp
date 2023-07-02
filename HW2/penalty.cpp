#include <iostream>
#include <string>
#include <vector>
#include "penalty.h"
#include <algorithm>
#include <iomanip>

Penalty::Penalty()//Penalty starts with all values empty
{
    penname = "";
    p1_pen = 0;
    p2_pen = 0;
    p3_pen = 0;
    ot_pen = 0;
}

void Penalty::add_pen_p1()
{
    p1_pen++;
}

void Penalty::add_pen_p2()
{
    p2_pen++;
}

void Penalty::add_pen_p3()
{
    p3_pen++;
}

void Penalty::add_pen_ot()
{
    ot_pen++;
}

void Penalty::set_name(std::string s)
{
    penname = s;
}

bool isPenGreaterThan(const Penalty &pen1, const Penalty &pen2)
{
    //calculates all of the penalty percentages(pens in period/total pens) so that
    //it is easier to type in return statement
    double pen1_otpercent = double(pen1.get_pen_ot()) / double(pen1.get_total_pens());
    double pen1_p3percent = double(pen1.get_pen_p3()) / double(pen1.get_total_pens());
    double pen2_otpercent = double(pen2.get_pen_ot()) / double(pen2.get_total_pens());
    double pen2_p3percent = double(pen2.get_pen_p3()) / double(pen2.get_total_pens());

    //orders by highest overtime penalty percentage, then in period 3,
    //then by total penalties
    return ((pen1_otpercent > pen2_otpercent) || ((pen1_otpercent == pen2_otpercent) && 
    (pen1_p3percent > pen2_p3percent)) || ((pen1_otpercent == pen2_otpercent) && 
    (pen1_p3percent == pen2_p3percent) && pen1.get_total_pens() > pen2.get_total_pens()));
}

void penalty_calculate(std::vector<std::string> &allwords, 
std::vector<Penalty> &penaltylist)
{
    Penalty apenalty;
    int i = 0;
    while (i < allwords.size())
    {
        if (allwords[i] == "PERIOD" && allwords[i + 1] == "1")//checks for first period
        {
            int count = 1;//count will increment until next period is reached
            while (allwords[i + count] != "PERIOD")
            {
                if (allwords[i + count] == "penalty")
                {
                    bool inlist = false;
                    for (int j = 0; j < penaltylist.size(); j++)//to check if penalty is
                    //already in the penaltylist
                    {
                        if (penaltylist[j].get_pen() == allwords[i + count + 3])
                        {//increments p1 pens in current object if it is in the list
                            penaltylist[j].add_pen_p1();
                            inlist = true;
                        }
                    }
                    if (!inlist)
                    {
                        //if not in the list, new oject is made and added to the list,
                        //and is given a name and adds a pen in period 1
                        penaltylist.push_back(apenalty);
                        penaltylist[penaltylist.size() - 1]
                        .set_name(allwords[i + count + 3]);
                        penaltylist[penaltylist.size() - 1].add_pen_p1();
                    }
                }
                count++;//count iterates until next period hits
            }
        }

        //same structure as last block, checks for period 2 instead
        if (allwords[i] == "PERIOD" && allwords[i + 1] == "2")
        {
            int count = 1;
            while (allwords[i + count] != "PERIOD")
            {
                if (allwords[i + count] == "penalty")
                {
                    bool inlist = false;
                    for (int j = 0; j < penaltylist.size(); j++)
                    {
                        if (penaltylist[j].get_pen() == allwords[i + count + 3])
                        {
                            penaltylist[j].add_pen_p2();//adds to period 2 pens if
                            // object in list
                            inlist = true;
                        }
                    }
                    if (!inlist)
                    {
                        penaltylist.push_back(apenalty);//creates new object if not
                        // in list
                        penaltylist[penaltylist.size() - 1]
                        .set_name(allwords[i + count + 3]);
                        penaltylist[penaltylist.size() - 1].add_pen_p2();
                    }
                }
                count++;//count iterates until next period hits
            }
        }

        //same structure except checks for period 3, end at final or overtime
        if (allwords[i] == "PERIOD" && allwords[i + 1] == "3")
        {
            int count = 1;
            while ((allwords[i + count] != "FINAL") && 
            (allwords[i + count] != "OVERTIME"))
            {
                if (allwords[i + count] == "penalty")
                {
                    bool inlist = false;
                    for (int j = 0; j < penaltylist.size(); j++)
                    {
                        if (penaltylist[j].get_pen() == allwords[i + count + 3])
                        {
                            penaltylist[j].add_pen_p3();//adds to period 3 pens of object
                            inlist = true;
                        }
                    }
                    if (!inlist)
                    {
                        penaltylist.push_back(apenalty);
                        penaltylist[penaltylist.size() - 1]
                        .set_name(allwords[i + count + 3]);
                        penaltylist[penaltylist.size() - 1].add_pen_p3();
                    }
                }
                count++;//count iterates until FINAL or OVERTIME is hit
            }
        }
        //same structure but for overtime period
        if (allwords[i] == "OVERTIME")
        {
            int count = 1;
            while (allwords[i + count] != "FINAL")
            {
                if (allwords[i + count] == "penalty")
                {
                    bool inlist = false;
                    for (int j = 0; j < penaltylist.size(); j++)
                    {
                        if (penaltylist[j].get_pen() == allwords[i + count + 3])
                        {
                            penaltylist[j].add_pen_ot();//adds to overtime pens of object
                            inlist = true;
                        }
                    }
                    if (!inlist)
                    {
                        penaltylist.push_back(apenalty);
                        penaltylist[penaltylist.size() - 1]
                        .set_name(allwords[i + count + 3]);
                        penaltylist[penaltylist.size() - 1].add_pen_ot();
                    }
                }
                count++;//so count can iterate until keyword FINAL is hit
            }
        }
        i++;//so i can iterate through allwords
    }
}

std::ostream &output_penalties(std::ostream &fileout, std::vector<Penalty> &penaltylist)
{
    unsigned int max_length = 0;//loop iterates through to find the largest
    //length penalty name
    for (int j = 0; j < penaltylist.size(); ++j)
    {
        unsigned int tmp_length = penaltylist[j].get_pen().size();
        max_length = std::max(max_length, tmp_length);
    }
    if (max_length != 0)//if max length is still 0, there were no penalties
    {
        fileout << "Penalty Type" + std::string(max_length - 12, ' ') 
        + "      P1      P2" + "      P3      OT   Total\n";//header for table

        for (int j = 0; j < penaltylist.size(); j++)//follows format for each 
        //penalty in list
        {
            //penalties are formatted by name first, then period 1, 2, 3, and overtime
            //percentages shown as a decimal to 3 decimal places using setprecision.
            //last, the total number or penalties of the type are shown
            fileout << std::setw(max_length) << std::left << penaltylist[j].get_pen()
                    << std::setw(8) << std::right << std::fixed << std::setprecision(3)
                    << double(penaltylist[j].get_pen_p1()) / 
                    double(penaltylist[j].get_total_pens())
                    << std::setw(8) << std::right << std::fixed << std::setprecision(3)
                    << double(penaltylist[j].get_pen_p2()) / 
                    double(penaltylist[j].get_total_pens())
                    << std::setw(8) << std::right << std::fixed << std::setprecision(3)
                    << double(penaltylist[j].get_pen_p3()) / 
                    double(penaltylist[j].get_total_pens())
                    << std::setw(8) << std::right << std::fixed << std::setprecision(3)
                    << double(penaltylist[j].get_pen_ot()) / 
                    double(penaltylist[j].get_total_pens())
                    << std::setw(8) << std::right 
                    << penaltylist[j].get_total_pens() << "\n";
        }
    }
    else//if nothing in penaltylist
    {
        fileout << "No penalties were found in this file";
    }

    return fileout;
}