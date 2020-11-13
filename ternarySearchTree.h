#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>

#include "ternaryTreeNode.h"

using namespace std;

class ternarySearchTree{
    public:
        void test(char* argv[]);
        
        ternarySearchTree();
        ternarySearchTree(string);

        // function for searching the word in the TST
        // if found, returns "[word] found, count = ..."
        // if not, returns "[word] not found"
        // this output string should end with a new line "\n"
        void searchWord(string word);

        ternaryTreeNode* searchHelper(ternaryTreeNode* node, string word);

        // function for adding a word to the TST
        // if the word already exists within the TST, then
        // increment the count by 1
        // if not, add the word into the TST at the correct
        // location 
        // the returned string after the function ends should
        // follow this format
        // "[word] inserted, new count = [count]"
        // this output string should end with a new line "\n"
        void insertWord(string word);

        int insertHelper(ternaryTreeNode* node, string word);

        // function for deleting a word from the TST 
        // if the current count is 1, then delete the node
        // and shift the other nodes accordingly
        // if not, decrememnt the count by 1
        // the returned string after the function ends should
        // follow this format
        // if the word still exists within TST
        // "[word] deleted, new count = [count]"
        // if word does not exist anymore
        // "[word] deleted"
        // this output string should end with a new line "\n"
        // if word did not exist from start
        // don't print anything ""
        void deleteWord(string word);

        int deleteHelper(ternaryTreeNode* node, string word);

        ternaryTreeNode* findPredecessor(ternaryTreeNode* node, string key);

        ternaryTreeNode* findSuccessor(ternaryTreeNode* node, string key);


        // function for printing out all words in between the two words
        // provided for the range search in alphabetical order
        // if the word passed as parameter doesn't exist,
        // can print elements that would fall between the elements or if
        // there exist none, then don't print anything
        // this output string should have each element end with a new line "\n"
        void range_search(string word1, string word2);

        void inOrder(ternaryTreeNode* node, string word1, string word2);


    private:
        ternaryTreeNode *root;
};


