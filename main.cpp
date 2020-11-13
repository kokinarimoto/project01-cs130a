#include "ternarySearchTree.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
	ternarySearchTree tmp;
	string input = argv[1];
	stringstream changed(input);
	vector <string> arguments;
	string tmpString;
	bool stop = false;

	while(getline(changed, tmpString, ' '))
    {
        arguments.push_back(tmpString);
    }

    int count = 0;
	while(count < arguments.size()){
		string word = arguments[count];
		string nextWord = arguments[count+1];
		if(nextWord.substr(nextWord.length()-1).compare(",") == 0){
			nextWord.pop_back();
		}
		if(word.compare("lookup") == 0){
			// value not found
			tmp.searchWord(nextWord);
		} else if(word.compare("insert") == 0){
			tmp.insertWord(nextWord);
		} else if(word.compare("delete") == 0){
			tmp.deleteWord(nextWord);
		} else if(word.compare("range_search") == 0){
			string nextWord2 = arguments[count+3];
			if(nextWord2.substr(nextWord2.length()-1).compare(",") == 0){
				nextWord2.pop_back();
			}
			tmp.range_search(nextWord, nextWord2);
			count+=2;
		}
		count+=2;
	}
	return 0;
}
