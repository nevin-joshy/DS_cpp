#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "player.h"

Player::Player()//Initializes Player object as empty when created
{
    gls = 0;
    ass = 0;
    pns = 0;
    playname = "";
    teamname = "";
}

void Player::addass()
{
    ass++;
}

void Player::addpn()
{
    pns++;
}

void Player::addgl()
{
    gls++;
}

void Player::set_plyname(std::string nm)
{
    playname = nm;
}

void Player::set_teamname(std::string tm)
{
    teamname = tm;
}

bool isPlyGreaterThan(const Player &player1, const Player &player2)//for sort function
{
    //orders players by their goals and assists first, and then from there the player
    //with less penalties is on top, and finally alphabetically
    return ((player1.num_gls() + player1.num_ass() > player2.num_gls() + 
    player2.num_ass()) || (player1.num_gls() + player1.num_ass() 
    == player2.num_gls() + player2.num_ass() && player1.num_pns() < player2.num_pns()) ||
    (player1.num_gls() + player1.num_ass() == player2.num_gls() + player2.num_ass() && 
    player1.num_pns() == player2.num_pns() && player1.get_name() < player2.get_name()));
}

void player_calculate(std::vector<std::string> &allwords, std::vector<Player> &playerlist)
//populates playerlist and objects within
{
    Player aplayer;
    int i = 0;
    while (i < allwords.size())//iterates through all words in file
    {
        if (allwords[i] == "goal")
        //code for when goal is found in file
        {
            bool isin = false;
            for (int j = 0; j < playerlist.size(); j++)
            {
                if ((playerlist[j].get_name()==allwords[i+1])
                && playerlist[j].get_team() == allwords[i - 1])
                {//checks if in Player is in list by name and team, and if so adds a goal
                    playerlist[j].addgl();
                    isin = true;
                }
            }

            if (!isin)
            {
                playerlist.push_back(aplayer);//if not in the list,
                //an empty player is added and updated for the goal
                playerlist[playerlist.size() - 1].addgl();
                playerlist[playerlist.size() - 1].set_plyname(allwords[i + 1]);
                playerlist[playerlist.size() - 1].set_teamname(allwords[i - 1]);
            }
        }

        if (allwords[i] == "penalty")//checks for penalty in vector
        {
            bool isin = false;
            for (int j = 0; j < playerlist.size(); j++)
            {
                if (playerlist[j].get_name() == allwords[i + 1] && 
                playerlist[j].get_team() == allwords[i - 1])
                {//checks if player is in list by name and team, if so adds pen
                    playerlist[j].addpn();
                    isin = true;
                }
            }
            if (!isin)
            {
                playerlist.push_back(aplayer);//if not in list, adds empty player and
                //adds penalty, name, and team
                playerlist[playerlist.size() - 1].addpn();
                playerlist[playerlist.size() - 1].set_plyname(allwords[i + 1]);
                playerlist[playerlist.size() - 1].set_teamname(allwords[i - 1]);
            }
        }

        if (allwords[i] == "(")//checks for opening parentheses for assists
        {
            int counter = 1;
            while (allwords[i + counter] != ")")//counter iterates through next
            //few elements until closing parenthesis is found
            {
                bool isin = false;
                for (int j = 0; j < playerlist.size(); j++)
                {
                    if (playerlist[j].get_name() == allwords[i + counter] && 
                    playerlist[j].get_team() == allwords[i - 3])
                    {//checks whther player is alreadt in the list by name and team
                        playerlist[j].addass();
                        isin = true;
                    }
                }

                if (!isin)
                {
                    playerlist.push_back(aplayer);//if not in the list, empty player is
                    //added and assist, name, and team are added
                    playerlist[playerlist.size() - 1].addass();
                    playerlist[playerlist.size() - 1].
                    set_plyname(allwords[i + counter]);
                    playerlist[playerlist.size() - 1].set_teamname(allwords[i - 3]);
                }
                counter++;
            }
        }
        i++;//iterates through allwords, file vector
    }
}

std::ostream &output_players(std::ostream &fileout, std::vector<Player> &playerlist)
//for output to output file
{
    //finds longest string of player name so that header and player can be formatted
    //correctly
    unsigned int max_length = 0;
    for (int j = 0; j < playerlist.size(); ++j)
    {
        unsigned int tmp_length = playerlist[j].get_name().size();
        max_length = std::max(max_length, tmp_length);
    }
    max_length += 2;//adds 2 for gap in between in header

    //finds longest team name so that header can be formatted correctly
    unsigned int max_teamlength = 0;
    for (int j = 0; j < playerlist.size(); ++j)
    {
        unsigned int tmp_teamlength = playerlist[j].get_team().size();
        max_teamlength = std::max(max_teamlength, tmp_teamlength);
    }
    max_teamlength += 3;//adds 3 for gap in header

    if(max_length==0 || max_teamlength ==0){//returns no players or teams if the lengths
    //remains 0
        fileout<<"Players or teams missing from file";
        return fileout;
    }

    fileout << "Player Name" + std::string(max_length - 11, ' ') + "Team" + 
    std::string(max_teamlength - 4, ' ') + "Goals  Assists  Penalties\n";//header for
    //table
    
    for (int j = 0; j < playerlist.size(); ++j)
    {
        if (!(playerlist[j].get_name() == "BENCH"))//iterates through all the players
        //but leaves out BENCH, formats with name first, then team, goals, assists,
        //penalties.
        {
            fileout << std::setw(max_length) << std::left << playerlist[j].get_name() 
            << std::setw(max_teamlength)<< std::left << playerlist[j].get_team() 
            << std::setw(5) << std::right << playerlist[j].num_gls()<< std::setw(9) 
            << std::right << playerlist[j].num_ass() << std::setw(11) << std::right
            << playerlist[j].num_pns() << "\n";
        }
    }

    return fileout;
}