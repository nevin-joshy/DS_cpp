#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "team.h"
#include "player.h"
#include "penalty.h"

int main(int argc, char *argv[])
{
    if (argc != 4)//checks whether 4 arguments are given, if not gives error
    {
        std::cerr << "Error, " << argv[0] << " args given rather than 4";
        return 1;
    }
    std::ifstream filein(argv[1]);//defines input file stream as filein
    if (!filein)//checks whether input file can be read, if not gives error
    {
        std::cerr << "Could not open " << argv[1] << " to read\n";
        return 1;
    }
    std::ofstream fileout(argv[2]);//defines output file as fileout
    if (!fileout)//checks whether output file can be written to, if not gives error
    {
        std::cerr << "Could not open " << argv[2] << " to write\n";
        return 1;
    }

    std::string word;                  // string that will be each word
    std::vector<std::string> allwords; // vector that will carry all words
    while (filein >> word)
    { // adds each word from file and packs them into allwords vector
        allwords.push_back(word);
    }

    if (std::string(argv[3]) == "--team_stats")
    {
        std::vector<Team> teamlist;
        team_calculate(allwords,teamlist);//populates and edits all teams into teamlist
        std::sort(teamlist.begin(), teamlist.end(), isGreaterThan);//sorts according to
        //isGreaterThan function
        output_teams(fileout,teamlist);//team info goes to output file
    }

    if (std::string(argv[3]) == "--player_stats")
    {   
        std::vector<Player> playerlist;
        player_calculate(allwords,playerlist);//populates and edits all players into 
        //playerlist
        std::sort(playerlist.begin(), playerlist.end(), isPlyGreaterThan);//sorts
        //according to isPlyGreaterThan function
        output_players(fileout,playerlist);//player info to output file
    }

    if (std::string(argv[3]) == "--custom_stats")
    {   
        std::vector<Penalty> penaltylist;
        penalty_calculate(allwords,penaltylist);//populates and edits penalties to
        //penaltylist
        std::sort(penaltylist.begin(), penaltylist.end(), isPenGreaterThan);//sorts according
        //to isPenGreaterThan function
        output_penalties(fileout,penaltylist);//penalty info to output file
    }

    return 0;
}
