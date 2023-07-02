#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "team.h"

Team::Team()
{ // Team object initializes as empty, all values empty
    wins = 0;
    loss = 0;
    ties = 0;
    pens = 0;
    goals = 0;
    name = "";
}
void Team::addgoal()
{
    goals += 1;
}

void Team::addwin()
{
    wins += 1;
}

void Team::addloss()
{
    loss += 1;
}

void Team::addtie()
{
    ties += 1;
}

void Team::addpen()
{
    pens += 1;
}

void Team::setname(std::string nm)
{
    name = nm;
}

bool isGreaterThan(const Team &team1, const Team &team2)//compares 2 team objects
//for sorting purposes for the output
{
    //calculates the winpercentage by adding the number of wins to 
    //0.5 times the ties all divided by the total games(wins plus loss plus ties)
    double team1_winperc = (team1.num_wins() + 0.5 * (team1.num_tie())) / 
    (team1.num_wins() + team1.num_loss() + team1.num_tie());
    double team2_winperc = (team2.num_wins() + 0.5 * (team2.num_tie())) / 
    (team2.num_wins() + team2.num_loss() + team2.num_tie());
    //higher win percentage comes first, then the higher number of goals
    return ((team1_winperc > team2_winperc) || ((team1_winperc == team2_winperc) 
    && (team1.num_goals() > team2.num_goals()))||((team1_winperc == team2_winperc) 
    && (team1.num_goals() == team2.num_goals())&&(team1.get_name()<team2.get_name())));
}

void team_calculate(std::vector<std::string> &allwords, std::vector<Team> &teamlist)
{
    Team ateam;
    int i = 0;
    while (i < allwords.size())
    {
        if ((allwords[i] == "at") || (allwords[i] == "vs."))//finds where both teams
        //are listed at beginning of game
        {
            bool inList1 = false;
            bool inList2 = false;
            for (int j = 0; j < teamlist.size(); j++)
            {
                if (teamlist[j].get_name() == allwords[i - 1])//index before is 1stteam
                {
                    inList1 = true;//checks if first team is already in the list
                }
                if (teamlist[j].get_name() == allwords[i + 1])//index after is 2ndteam
                {
                    inList2 = true;//cheacks if secodn team is already in the list
                }
            }

            if (!inList1)
            {
                teamlist.push_back(ateam);//if first team is not in thelist, added
                teamlist[teamlist.size() - 1].setname(allwords[i - 1]);
            }

            if (!inList2)
            {
                teamlist.push_back(ateam);// if second team not in list, added
                teamlist[teamlist.size() - 1].setname(allwords[i + 1]);
            }
        }

        if (allwords[i] == "goal")
        {
            for (int j = 0; j < teamlist.size(); j++)
            {
                if (teamlist[j].get_name() == allwords[i - 1])
                {
                    teamlist[j].addgoal();//adds goal to corect team in list
                    //no need to check if in list because added at beginning of game
                }
            }
        }

        if (allwords[i] == "penalty")
        {
            for (int j = 0; j < teamlist.size(); j++)
            {
                if (teamlist[j].get_name() == allwords[i - 1])
                {
                    teamlist[j].addpen();//adds penalty to correct team in list
                }
            }
        }

        if (allwords[i] == "FINAL")
        {
            std::string winteam;
            std::string loseteam;
            bool istie = false;
            if (int(std::stoi(allwords[i + 2])) > 
            int(std::stoi(allwords[i + 4])))//compares the scores after keyword FINAL
            {
                winteam = allwords[i + 1];//if the first score bigger,
                //first team is the winning team and second losing
                loseteam = allwords[i + 3];
            }
            else if (int(std::stoi(allwords[i + 2])) < 
            int(std::stoi(allwords[i + 4])))
            {
                winteam = allwords[i + 3];//second team bigger so second team
                //is winner anf first is loser
                loseteam = allwords[i + 1];
            }
            else
            {
                istie = true;// if neither score is bigger, is a tie
            }

            for (int j = 0; j < teamlist.size(); j++)
            {
                if (istie)
                {
                    if (teamlist[j].get_name() == allwords[i + 1] || 
                    teamlist[j].get_name() == allwords[i + 3])
                    {//adds tie to both of the teams
                        teamlist[j].addtie();
                    }
                }
                else
                {
                    if (teamlist[j].get_name() == winteam)
                    {//adds win to winning team
                        teamlist[j].addwin();
                    }
                    if (teamlist[j].get_name() == loseteam)
                    {//adds loss to losing team
                        teamlist[j].addloss();
                    }
                }
            }
        }
        i++;//iterates through file vector
    }
}

std::ostream &output_teams(std::ostream &fileout, std::vector<Team> &teamlist)//outputs
//the information in the teamlist into table format
{
    //finds the longest name of team for formatting purposes
    unsigned int max_length = 0;
    for (int j = 0; j < teamlist.size(); ++j)
    {
        unsigned int tmp_length = teamlist[j].get_name().size();
        max_length = std::max(max_length, tmp_length);
    }
    max_length += 1;//adds 1 for gap in formatting

    if(max_length ==0){//if the max length is 0 then outputs that there
    //are no teams
        fileout<<"No teams in file";
        return fileout;
    }

    fileout << "Team Name" + std::string(max_length - 9, ' ') 
    + "   W   L   T   Win%   Goals   Penalties\n";//header for table
    for (int j = 0; j < teamlist.size(); ++j)
    {
        //iterates through team list and outputs the team info first the name,
        //then the wins, then losses, then ties, win percentage to 2 decimals,
        //then goals, the penalties
        fileout << std::setw(max_length) << std::left << teamlist[j].get_name() 
        << std::setw(4)<< std::right << teamlist[j].num_wins() << std::setw(4) 
        << std::right << teamlist[j].num_loss()<< std::setw(4) << std::right 
        << teamlist[j].num_tie() << std::setw(7) << std::right << std::fixed
        << std::setprecision(2) << (teamlist[j].num_wins() + 
        0.5 * (teamlist[j].num_tie())) / (teamlist[j].num_wins() + teamlist[j].num_loss()
         + teamlist[j].num_tie())<< std::setw(8) << std::right << teamlist[j].num_goals()
         << std::setw(12) << std::right << teamlist[j].num_pens() << "\n";
    }
    return fileout;
}