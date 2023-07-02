#include <iostream>
#include <string>
#include <vector>

class Team{//holds the information on each team as an object,
//such as wins, losses, ties, penalties, goals, and name
public:
    Team();
    const std::string& get_name() const {return name;}
    const int& num_wins() const { return wins; }
    const int& num_loss() const { return loss; }
    const int& num_tie() const { return ties; }
    const int& num_pens() const { return pens; }
    const int& num_goals() const { return goals;}

    void addwin();//adds 1 win to team
    void addloss();// adds 1 loss to team
    void addtie();//adds 1 tie to team
    void addpen();//adds 1 penalty to team
    void addgoal();//adds 1 goal to team
    void setname(std::string nm);//sets the name of the team

private:
    std::string name;//name of team
    int wins;//number of wins
    int loss;//number of losses
    int ties;//number of ties
    int pens;//number of penalties
    int goals;//number of goals
};
bool isGreaterThan(const Team &team1, const Team &team2);//
void team_calculate(std::vector<std::string> &allwords, std::vector<Team> &teamlist);
std::ostream& output_teams(std::ostream& fileout, std::vector<Team> &teamlist);