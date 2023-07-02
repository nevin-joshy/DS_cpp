#include <vector>
#include <string>

using namespace std;

//loc class will hold the row, column, charectar, and a vector of all the words using the
//location in the spot. The grid will be a vector of vector of loc
class loc {
public:
  loc(char s = ' ') : c(s) {}

  const char& getChar(){return c;}
  void setChar(char l){c = l;}
  const vector<string>& getUsed(){return usedWords;}
  void addWord(const string& word){usedWords.push_back(word);}
  void removeWord(){usedWords.pop_back();}
private:
  char c;
  vector<string> usedWords;
};