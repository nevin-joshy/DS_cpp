#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "loc.h"

using namespace std;

/*This this a program that will build an inverse word search program using  
recursion, given dimensions, words to include, and words to exclude. All
extra spaces will be filled in will the letters of the alphabet in every
combination. Successful puzzles are outputted to a file. The outlines for
the puzzles are given through a puzzle input fole, such as puzzle8.txt
(see file)
*/

//prints the grid to file
void printGrid(std::ofstream& puzzout, vector<vector<loc>>& grid){
    puzzout<<"Board:\n";
    for (vector<loc> row : grid) {
        puzzout<<"  ";
        for (loc l : row) {
            puzzout << l.getChar();
        }
        puzzout << endl;
    }
}

//word search that checks whether a given word is in the grid
bool inGrid(const string& word, vector<vector<loc>>& currentGrid){
    for(int i = 0; i<int(currentGrid.size()); i++){
        for(int j = 0; j<int(currentGrid[i].size()); j++){
            //skip if we are not on the first letter of the word
            if(currentGrid[i][j].getChar()!=word[0]) continue;
            //go in all 8 directions
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    // Skip if both di and dj are 0 (i.e., current cell)
                    if (di == 0 && dj == 0) continue;
                    //skip if it is not possible to go in the given direction
                    if (i+di<0 || i+di>=int(currentGrid.size()) || j+dj<0 || 
                    j+dj>=int(currentGrid[i].size())) continue;
                    int k = 1;
                    int tempi = i+di;
                    int tempj = j+dj;
                    //keep going in direction while letter matches
                    while(currentGrid[tempi][tempj].getChar() == word[k]){
                        tempi += di;
                        tempj += dj;
                        k++;
                        //break if out of bounds
                        if (tempi<0 || tempi>=int(currentGrid.size()) ||
                         tempj<0 || tempj>=int(currentGrid[i].size())) break;
                    }
                    //if the counter, k, is the same size as the word, then the word was
                    //found
                    if(k == int(word.size())) return true;
                }    
            }    
        }
    }
    return false;
}

//removes a given word from the grid
void removeWord(const string& word, vector<vector<loc>>& currentGrid){
    for(int i = 0; i<int(currentGrid.size()); i++){
        for(int j = 0; j<int(currentGrid[i].size()); j++){
            //checks that the word is being used(has words in usedwords)
            if(currentGrid[i][j].getUsed().size()!=0){
                //if there is more than 1, then it will just remove the word which will
                //always be last in the vector because we remove after we insert, so it
                //it the most recently inserted, however if the word is the only one
                //using the spot then the spot must become blank
                if(word == currentGrid[i][j].getUsed().back() &&
                 currentGrid[i][j].getUsed().size()>1){
                    currentGrid[i][j].removeWord();
                }
                else if(word == currentGrid[i][j].getUsed().back()){
                    currentGrid[i][j].removeWord();
                    currentGrid[i][j].setChar(' ');
                }
            }
        }
    }
}

//checks if a word can be put in the grid in the given direction, and if so, inserts
//and returns true, if not, the word is not inserted and it returns false
bool insertWord(int x, int y, int dx, int dy, const string& word,
 const vector<string>& excludeList, vector<vector<loc>>& currentGrid){
    int size = word.size();
    int counter = 0;
    int tempx = x;
    int tempy = y;
    //counts how many spots are open in the given direction
    while(tempx>=0 && tempx<int(currentGrid[0].size()) && tempy>=0 && tempy<int(currentGrid.size())
     && counter<size){
        if(currentGrid[tempy][tempx].getChar() == ' ' ||
         currentGrid[tempy][tempx].getChar() == word[counter]){
            counter++;
        }
        else{
            break;
        }
        tempx += dx;
        tempy += dy;
    }
    //if there are enough spots, then the word will be inserted
    if(counter == size){
        //word inserts backwards, starting from last spot and decreasing until back
        //to the beginning
        while(counter>0){
            counter--;
            tempx -=dx;
            tempy -=dy;
            currentGrid[tempy][tempx].setChar(word[counter]);
            currentGrid[tempy][tempx].addWord(word);
        }
        //checks that a - word was not added when the word was added
        bool allExcluded = true;
        for (string tword : excludeList){
            if(inGrid(tword, currentGrid)){
                allExcluded = false;
                break;
            }
        }
        if(!allExcluded){
            removeWord(word, currentGrid);
            return false;
        }
        return true;
    }else{
        return false;
    }
}

//checks whether the given grid is already in the vector of grids
bool usedGrid(vector<vector<loc>>& currentGrid, vector<vector<vector<loc>>>& validGrids){
    for(vector<vector<loc>> grid : validGrids){
        bool isSame = true;
        for(int i = 0; i<int(currentGrid.size()); i++){
            for(int j = 0; j<int(currentGrid[i].size()); j++){
                if(grid[i][j].getChar() != currentGrid[i][j].getChar()){
                    isSame = false;
                }
            }
        }
        if(isSame){
            return true;
        }
    }
    return false;
}

//this function checks whether the given grid has any open spots, and if so recursively
//fills in the spots with every possible letter and once the grid does not have openings,
//it is pushed back to the lsit of valid grids
void completeGrid(vector<vector<loc>>& currentGrid, const vector<string>& excludeList,
 vector<vector<vector<loc>>>& validGrids){
    bool emptySpot = false;
    for(int i = 0; i<int(currentGrid.size()); i++){
        for(int j = 0; j<int(currentGrid[i].size()); j++){
            if(currentGrid[i][j].getChar() == ' '){
                emptySpot = true;
                break;
            }
        }
        if(emptySpot) break;
    }
    //if there are no empty spots and the grid is not already used, add the grid
    //(base case)
    if(!emptySpot){
        if(!usedGrid(currentGrid,validGrids)){
            validGrids.push_back(currentGrid);
        }
    }
    else{
        for(int i = 0; i<int(currentGrid.size()); i++){
            for(int j = 0; j<int(currentGrid[i].size()); j++){
                if(currentGrid[i][j].getChar() == ' '){
                    for(char l = 'a'; l<='z'; l++){
                        currentGrid[i][j].setChar(l);
                        //after filling in letter, checks that a - word was not created
                        bool allExcluded = true;
                        for (string wordl : excludeList){
                            if(inGrid(wordl, currentGrid)){
                                allExcluded = false;
                                break;
                            }
                        }
                        if(!allExcluded) continue;
                        //recursively fills in next letter, with each letter
                        completeGrid(currentGrid, excludeList, validGrids);
                    }
                    //resets spot to be blank
                    currentGrid[i][j].setChar(' ');
                }
            }
        }
    }
}

// This function generates all possible word search grids by adding each word in every 
//possible position
void generateGrids(int index, const vector<string>& includeList,
 const vector<string>& excludeList, vector<vector<loc>>& currentGrid,
  vector<vector<vector<loc>>>& validGrids, bool onlyOne) {
    // if we only want 1 solution, it will return if the size of the valid grid is 1
    // or more
    if (onlyOne && validGrids.size()>=1){
        return;
    }
    //otherwise we want all solutions, so call completegrid to fill in empty spots if any
    else if (index>=int(includeList.size())) {
        completeGrid(currentGrid, excludeList, validGrids);
    }
    //otherwise grid is incomplete, and next word should be inserted and recursively call
    //generateGrids
    else{
        for(int i = 0; i<int(currentGrid.size()); i++){
            for(int j = 0; j<int(currentGrid[i].size()); j++){
                if(currentGrid[i][j].getChar()!=includeList[index][0] &&
                 currentGrid[i][j].getChar()!=' '){
                    continue;
                }
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        //skip if current spot
                        if (di == 0 && dj == 0) continue;
                        //skip if going out of bounds
                        if (i+di<0 || i+di>=int(currentGrid.size()) || j+dj<0 ||
                         j+dj>=int(currentGrid[i].size())) continue;
                        //if word can be inserted it will be, and we call generategrids
                        //for next word
                        if(insertWord( j, i, dj, di, includeList[index], excludeList,
                         currentGrid)){
                            generateGrids(index+1, includeList, excludeList, currentGrid,
                             validGrids, onlyOne);
                            //word is removed because all possibilities with later words 
                            //fulfilled
                            removeWord(includeList[index], currentGrid);
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    ifstream puzzin(argv[1]);//defines input file stream as toolin
    if(argc != 4){
        cerr << "Insufficient arguments\n";
        return 1;
    }
    if (!puzzin)//checks whether input file can be read, if not gives error
    {
        cerr << "Could not open " << argv[1] << " to read\n";
        return 1;
    }
    ofstream puzzout(argv[2]);//defines output file as toolout
    if (!puzzout)//checks whether output file can be written to, if not gives error
    {
        cerr << "Could not open " << argv[2] << " to write\n";
        return 1;
    }
    bool onlyOne;
    if (string(argv[3])=="one_solution"){
        onlyOne = true;
    }
    else if (string(argv[3])=="all_solutions"){
        onlyOne = false;
    }else{
        cerr << "Cant recognize " << argv[3] << endl;
        return 1;
    }
    int n; // grid height
    int m; // grid width
    vector<string> includeList;
    vector<string> excludeList;
    vector<vector<vector<loc>>> validGrids;
    vector<vector<loc>> currentGrid;
    puzzin>>m>>n;
    string word;
    while(puzzin>>word){
        if(word == "+"){
            puzzin>>word;
            includeList.push_back(word);
        }
        else if(word=="-"){
            puzzin>>word;
            excludeList.push_back(word);
        }
    }
    //create grid
    for(int i = 0; i<n;i++){
        currentGrid.push_back(vector<loc>(m, loc()));
    }
    generateGrids(0,includeList, excludeList, currentGrid, validGrids, onlyOne);
    //print grids to file
    if(validGrids.size() == 0) puzzout<<"No solutions found\n";
    else if(!onlyOne && validGrids.size()>0) puzzout<<validGrids.size()
    <<" solution(s)\n";
    for(vector<vector<loc>> grid : validGrids){
        printGrid(puzzout, grid);
    }
    return 0;
}