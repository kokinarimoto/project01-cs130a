#include <string>
#include <set>
#include "ternarySearchTree.h"

using namespace std;


int main(int argc, char* argv[]){
    ternarySearchTree tree;
    int commaIndex = 0;
    string commaDelimitter = ", ";
    int spaceIndex = 0;
    string spaceDelimitter = " ";

    int toIndex = 0;

    string input(argv[1]);
    int length = input.length();
    string tmp;

    bool storedAction = false;
    string action;
    set<string> actions;
    actions.insert("lookup");
    actions.insert("insert");
    actions.insert("delete");
    actions.insert("range_search");

    while((commaIndex = input.find(commaDelimitter) != length) || 
            (spaceIndex = input.find(spaceDelimitter) != length)){
        if(spaceIndex < commaIndex){
            tmp = input.substr(0, spaceIndex);
            
        }
        else if(commaIndex < spaceIndex){
            tmp = input.substr(0, commaIndex);
        }

        if(actions.find(tmp) != actions.end()){
            storedAction = true;
            action = tmp;
        }
        else{
            if(action == "lookup"){
                tree.searchWord(tmp);
            }
            else if(action == "insert"){
                tree.insertWord(tmp);
            }
            else if(action == "delete"){
                tree.deleteWord(tmp);
            }
            else if(action == "range_search"){
                tree.range_search(tmp);
            }
        }


    }
}