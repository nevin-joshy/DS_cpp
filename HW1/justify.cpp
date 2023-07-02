#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>

/*This is the text justification code. It cosists of three functions and main code. The three functions are leftjustify,
rightjustify, and fulljustify. Depending on which the user inputs, the corresponding function is called in the main.
*/


/*This is the leftjustify code. It takes a reference to a vector of stings, words, which will be a complete vector of 
all the words in the input file. It also takes a reference to an empty string line, which the function edits which ends
up being the complete box that is written into the output file. Finally, it takes an int len, whcih is the length specified
for the box by the user.
*/
void leftjustify(std::vector<std::string> &words, std::string &line, int len){
    
    line = std::string(len+4,'-') + "\n";//line starts off as a string of dashes, 4 longer than the length(top of box)

    int i = 0;
    /*This loop goes through as long as i is less than the size of the list. in this loop, a string
    temp is made which adds words to itself as a string as long as its length is less than or
    equal to the specified length by the user
    */
    while (i<(int)(words.size())){
        std::string temp = words[i];//temp starts as the current position in words held by i
        while ((i+1)<int(words.size()) && int((temp+" "+words[i+1]).size())<=len){//the loop runs if the next word exists
            //and it temp would be less than the specified length with it added on
            i++;
            temp+= " " + words[i];//the next word is added to temp with a space in between
        }
    i++;
    int rem = len-temp.size();//calculates the remaining number of spaces by subtracting the length
    // of tmp from the specified length by user
    line += "| " + temp + std::string(rem, ' ')+ " |\n";//the next line is added onto the line string, first with
    //the edge, and then temp, and then the remaining number of spaces fill in on the right, then the right edge
    }
    line+=std::string(len+4,'-') + "\n";//when the loop ends, the bottom of the box is added(same as top)
}


/*This is the rightjustify code. It takes a reference to a vector of stings, words, which will be a complete vector of 
all the words in the input file. It also takes a reference to an empty string line, which the function edits which ends
up being the complete box that is written into the output file. Finally, it takes an int len, whcih is the length specified
for the box by the user.
*/
void rightjustify(std::vector<std::string> &words, std::string &line, int len){
    
    line = std::string(len+4,'-') + "\n";//line starts off as a string of dashes, 4 longer than the length(top of box)

    int i = 0;
    /*This loop goes through as long as i is less than the size of the list. in this loop, a string
    temp is made which adds words to itself as a string as long as its length is less than or
    equal to the specified length by the user
    */
    while (i<int(words.size())){
        std::string temp = words[i];//temp starts as the current position in words held by i
        while ((i+1)<int(words.size()) && int((temp+" "+words[i+1]).size())<=len){//the loop runs if the next word exists
            //and it temp would be less than the specified length with it added on
            i++;
            temp+= " " + words[i];//the next word is added to temp with a space in between
        }
    i++;
    int rem = len-temp.size();//calculates the remaining number of spaces by subtracting the length
    // of tmp from the specified length by user
    line += "| " + std::string(rem, ' ')+ temp +" |\n";//the next line is added onto the line string, first with
    //the edge, and then remaining number of spaces fill in on the left, and then temp, then the right edge
    }
    line+=std::string(len+4,'-') + "\n";//when the loop ends, the bottom of the box is added(same as top)
}


/*This is the fulljustify code. It takes a reference to a vector of stings, words, which will be a complete vector of 
all the words in the input file. It also takes a reference to an empty string line, which the function edits which ends
up being the complete box that is written into the output file. Finally, it takes an int len, whcih is the length specified
for the box by the user.
*/
void fulljustify(std::vector<std::string> &words, std::string &line, int len){

 line = std::string(len+4,'-') + "\n";//line starts off as a string of dashes, 4 longer than the length(top of box)

    int i = 0;
    std::vector<std::string> lnwds;//this vector will contain the words that will be on the current line, and is cleared
    //after each line

    /*This loop goes through as long as i is less than the size of the list. in this loop, a string
    temp is made which adds words to itself as a string as long as its length is less than or
    equal to the specified length by the user. Also, an int total calculates the total number of charectars in the
    words, and the vector lnwds adds a word to itself if the next word will fit.
    */
    while (i<int(words.size())){
        std::string temp = words[i];//temp begins as the current word
        lnwds.push_back(words[i]);//lnwds starts as only containing the current word
        int total = int(words[i].size());//total begins as the size of the first word
        while ((i+1)<int(words.size()) && int((temp+" "+words[i+1]).size())<=len){//the loop runs if the next word exists
            //and it temp would be less than the specified length with it added on
            i++;
            temp+= " " + words[i];//the next word is added to temp with a space in between
            total+=int(words[i].size());//the size of the next word is added to total
            lnwds.push_back(words[i]);//the next word is added to the linewords vector
        }
        i++;
        if (int(lnwds.size())>1){//executes if there is more than 1 word in the current line
            int gaps = int(lnwds.size())-1;//calculates the number of gaps between words by subtracting 1
            // from the number of words in the line
            int rem = len-(total);// calculates the remaining spaces by subtracting the size of the words
            //from the specified length by the user
            int extra = rem%gaps;//finds the remainder of spaces left over after the remaining spaces are divided
            //evenly across the gaps

            if(i>=int(words.size())){//checks whether i is out of range of the words list, indicating we
            //have reached the lst word, thus this line should be left justified
                int rem = len-temp.size();//rem becomes the number of spaces after temp(string with spaces in between)
                //is subtracted from the specified length
                line += "| " + temp + std::string(rem, ' ')+ " |\n";// line is added, edge first, then temp, then
                //remaining spaces, then edge
            } else{//if it is not the last word, then lines are full justified by adding to line with the
            //number of spaces when the remaining are divided are split among the gaps, and if there is a remainder.
            // it is added one by one while extra is decremented
                line += "| " + lnwds[0];//line starts as the first element in the vector of word in line
                for(unsigned int j = 1; j<int(lnwds.size());j++){//adds each word to line one at a time, adding
                    //estra spaces if needed
                    if (extra>0){//if there is extra, adds a space and decrements extra
                        line+=" ";
                        extra--;
                    }
                    line+= std::string(int(rem/gaps),' ') + lnwds[j];//next word is added to line with the divided
                    //number of spaces
                }
                line+=" |\n";// end of line with right edge
            }
        } else if(int(lnwds.size())==1 && int(temp.size())<=len){//if there is only 1 word in line and the word is less
            //than the size of the line(len), it is left justified
            int rem = len-total;//remaining char is found by subtracting total size of word from specified length
            line += "| " + lnwds[0] + std::string(rem, ' ')+ " |\n";//word is added alone to line, left justified
        } else{//else, which runs if there is 1 word in the line and it is greater than the size of the line(len)
            //hyphen needs to be added and word is split
            std::string newstr = temp.substr(len-1);//newstr becomes the rest of the word that cannot fit
            words.insert(words.begin()+i,newstr);//newstr is added to words at i to be added to line when loop restarts
            temp = temp.substr(0,len-1)+"-";//temp redefined as a new string that fits, with a hyphen
            line+= "| " + temp + " |\n";// line is filled with temp
        }
    lnwds.clear();// the vector with the words from the line is cleared out
    }
    line+=std::string(len+4,'-') + "\n";//loop ends, so bottom of box is added(same as top)
}


int main(int argc, char* argv[]){

    std::ifstream filein(argv[1]);//takes the first argument from command line as input file
    if (!filein.good()) {//check if file can open
        std::cerr << "Can't open " << argv[1] << " to read.\n";//if not, error message is given
        exit(1);
    }
    std::ofstream fileout(argv[2]);//takes second argument from command line as output file
    if (!fileout.good()) {//check if file can open
        std::cerr << "Can't open " << argv[2] << " to write.\n";// if not, error message is given
        exit(1);
    }

    if (argc!= 5){// checks whether 5 arguments are given, if not error fiven displaying how many args were
        //given, and that 5 are needed
        std::cerr << "Only " << argc << " arguments given, need 5.\n";
        exit(1);
    }
    
    int size = atoi(argv[3]);//3rd argument, the size, needs to be made an into to be used in functions
    std::string word;//string that will be each word
    std::vector<std::string> allwords;//vector that will carry all words
    while (filein>>word){//adds each word from file and packs them into allwords vector
        allwords.push_back(word);
    }

    std::string box;// empty string box is ade, which will be passed in fucntion to become the output string
    if (std::string(argv[4]) == std::string("flush_left")) {// if the 4th argument calls for left justify, function
        //is called
        leftjustify(allwords, box, size);
    } else if(std::string(argv[4]) == std::string("flush_right")){// if the 4th argument calls for right justify, function
        //is called
        rightjustify(allwords, box, size);
    } else if(std::string(argv[4]) == std::string("full_justify")){// if the 4th argument calls for full justify, function
        //is called
        fulljustify(allwords, box, size);
    }

    
    fileout<<box;//outputs the string into the output file

    return 0;
}