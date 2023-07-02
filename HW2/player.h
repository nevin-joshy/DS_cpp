#include <iostream>
#include <string>
#include <vector>

class Player{//holds the info of each player as an object, records goals,
//assists, penalties and name
public:
    Player();
    const std::string& get_name() const {return playname;}//gives name
    const std::string& get_team() const { return teamname; }//gives team name
    const int& num_ass() const { return ass; }//gives number of assists
    const int& num_pns() const { return pns; }//gives number of penalties
    const int& num_gls() const { return gls;}//gives number of goals

    void addass();//adds 1 to assists
    void addpn();//adds 1 to penalties
    void addgl();//adds 1 to goals
    void set_plyname(std::string nm);//sets the name of the player
    void set_teamname(std::string tm);// sets the name of the team

private:
    std::string playname;// name of player
    std::string teamname;//name of team
    int ass;//number of assists
    int pns;//number of penalties
    int gls;// number of goals
};
bool isPlyGreaterThan(const Player &player1, const Player &player2);//compares
//two player objects for sorting purposes for the output table, passes 2 objects as
// reference
void player_calculate(std::vector<std::string> &allwords, 
std::vector<Player> &playerlist);//pupolates the playerlist and updates each of the
//players on it by passing words in file and player list as reference
std::ostream& output_players(std::ostream& fileout, 
std::vector<Player> &playerlist);//outputs the player table by passing in the output
//file stream as reference and the player list as reference