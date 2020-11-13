#include "ternarySearchTree.h"

void ternarySearchTree::test(char* argv[]){
	string input = argv[1];
	stringstream changed(input);
	vector <string> token;
	string intermediate;
	bool stop = false;
	while(getline(changed, intermediate, ' '))
    {
        token.push_back(intermediate);
    }

    int count = 0;
	while(count < token.size()){
		string word = token[count];
		string nextWord = token[count+1];
		if(nextWord.substr(nextWord.length()-1).compare(",") == 0){
			nextWord.pop_back();
		}

		if(word.compare("lookup") == 0){
			// value not found
			searchWord(nextWord);
		} else if(word.compare("insert") == 0){
			insertWord(nextWord);
		} else if(word.compare("delete") == 0){
			deleteWord(nextWord);
		} else if(word.compare("range_search") == 0){
			string nextWord2 = token[count+3];
			if(nextWord2.substr(nextWord2.length()-1).compare(",") == 0){
				nextWord2.pop_back();
			}
			range_search(nextWord, nextWord2);
			count+=2;
		}
		count+=2;
	}
}

ternarySearchTree::ternarySearchTree(){
    root = NULL;
}

void ternarySearchTree::searchWord(string word){
    ternaryTreeNode* tmp = searchHelper(root, word);
    if(tmp == NULL){
        cout << word << " not found";
    }
    if((tmp->leftKey).first.compare(word) == 0){
        cout << word << " found, count = " << tmp->leftKey.second << endl;
    }
    else if(tmp->rightKey.first.compare(word) == 0){
        cout << word << " found, count = " << tmp->rightKey.second << endl;
    }
}

ternaryTreeNode* ternarySearchTree::searchHelper(ternaryTreeNode* node, string word){
    if(node == NULL){
        return NULL;
    }
    if(node->leftKey.first.compare(word) == 0 || node->rightKey.first.compare(word) == 0){
        cout << "key found" << endl;
        return node;
    }
    if(node->leftKey.first.compare(word) > 0 && !(node->leftKey.first.compare("") == 0)){
        cout << "entering left"<< endl;
        return searchHelper(node->left, word);
    }
    else if((node->rightKey).first.compare(word) > 0 && !(node->rightKey.first.compare("") == 0)){
        cout << "entering middle"<< endl;
        return searchHelper(node->middle, word);
    }
    else if(node->rightKey.first.compare(word) < 0 && !(node->rightKey.first.compare("") == 0)){
        cout << "entering right"<< endl;
        return searchHelper(node->right, word);
    }
    return node;
}

void ternarySearchTree::insertWord(string word){
    if(root == NULL){
        root = new ternaryTreeNode(word);
        cout << word << " inserted, new count = " << 1 << endl;
        return;
    }
    int tmp = insertHelper(root, word);
    cout << word << " inserted, new count = " << tmp << endl;
}

int ternarySearchTree::insertHelper(ternaryTreeNode* node, string word){
    if((node->leftKey.first.compare(word)) == 0){
        (node->leftKey.second)++;
        return node->leftKey.second;
    }
    if((node->rightKey.first.compare(word)) == 0){
        (node->rightKey.second)++;
        return node->leftKey.second;
    }

    // adds the key to the left/right key if no values exist
    if(node->left == NULL && node->middle == NULL && node->right == NULL){
        if(node->leftKey.first.compare("") == 0){
            node->leftKey.first = word;
            node->leftKey.second = 1;
            return 1;
        }
        else if(node->rightKey.first.compare("") == 0){
            node->rightKey.first = word;
            node->rightKey.second = 1;
            if((node->rightKey).first.compare((node->leftKey).first) < 0){
                node->swapKey();
            }
            return node->rightKey.second;
            
        }
    }

    // adds new Node if none exist
    int tmp = 0;
    if((node->leftKey).first.compare(word) > 0){
        if(node->left == NULL){
            node->left = new ternaryTreeNode(word);
            node->left->parent = node;
            return 1;
        }
        else{
            tmp = insertHelper(node->left, word);
        }
    }
    else if((node->rightKey).first.compare(word) > 0){
        if(node->middle == NULL){
            node->middle = new ternaryTreeNode(word);
            node->middle->parent = node;
            return 1;
        }
        else{
            tmp = insertHelper(node->middle, word);
        }
    }
    else if((node->rightKey).first.compare(word) < 0){
        //cout << "entered rightKey comparison" <<endl;
        if(node->right == NULL){
            node->right = new ternaryTreeNode(word);
            node->right->parent = node;
            return 1;
        }
        else{
            tmp = insertHelper(node->right, word);
        }
    }
    return tmp;
}

void ternarySearchTree::deleteWord(string word){
    int tmp = deleteHelper(root, word);
    if(tmp == -1){
        return;
    }
    if(tmp > 0){
        cout << word << " deleted, new count = " << tmp << endl;
    }
    else {
        cout << word << " deleted" << endl;
    }
}

int ternarySearchTree::deleteHelper(ternaryTreeNode* node, string word){
    if(node == NULL){
        return -1;
    }
    bool inLeft = node->leftKey.first.compare(word) == 0;
    bool inRight = node->rightKey.first.compare(word) == 0;

    if(inLeft && node->leftKey.second > 1){
        node->leftKey.second--;
        return node->leftKey.second;
    }
    if(inRight && node->rightKey.second > 1){
        node->rightKey.second--;
        return node->rightKey.second;
    }

    // if the word that is being deleted has no children
    if(node->left == NULL && node->middle == NULL && node->right == NULL){
        if(inLeft){
            if(node->rightKey.first.compare("") == 0){
                if(node == root){
                    root =  NULL;
                }
                if(node->parent->left == node){
                    node->parent->left = NULL;
                }
                else if(node->parent->middle == node){
                    node->parent->middle = NULL;
                }
                else if(node->parent->right == node){
                    node->parent->right = NULL;
                }
                delete node;
                return 0;
            }
            else{
                node->swapKey();
                node->rightKey.first = "";
                node->rightKey.second = 0;
                return 0;
            }
        }
        else if(inRight){
            node->rightKey.first = "";
            node->rightKey.second = 0;
            return 0;
        }
        return 0;
    }
    int tmp = -1;
    // if the word that is being deleted has 1 child
    if(node->left != NULL){
        ternaryTreeNode* preNode = findPredecessor(node, "left");
        pair<string, int> tmpPair;
        if(preNode->rightKey.second > 0){
            tmpPair = preNode->rightKey;
            while(preNode->rightKey.second > 1){
                preNode->rightKey.second--;
            }
            tmp = deleteHelper(preNode, preNode->rightKey.first);
        }
        else{
            tmpPair = preNode->leftKey;
            while(preNode->leftKey.second > 1){
                preNode->leftKey.second--;
            }
            tmp = deleteHelper(preNode, preNode->leftKey.first);
        }
        int count = -1;
        if(inLeft){
            node->leftKey = tmpPair;
            node->leftKey.second--;
            count = node->leftKey.second;
        }
        else if(inRight){
            node->swapKey();
            node->rightKey = tmpPair;
            node->rightKey.second--;
            count = node->rightKey.second;
        }
        return count;
    }
    if(node->middle != NULL){
        int count = -1;
        if(inLeft){
            ternaryTreeNode* sucNode = findSuccessor(node, "left");
            pair<string, int> tmpSucPair;
            if(sucNode->leftKey.second > 0){
                tmpSucPair = sucNode->leftKey;
                while(sucNode->leftKey.second > 1){
                    sucNode->leftKey.second--;
                }
                tmp = deleteHelper(sucNode, sucNode->leftKey.first);
            }
            /*
            else{
                tmpSucPair = sucNode->rightKey;
                while(sucNode->rightKey.second > 1){
                    sucNode->rightKey.second--;
                }
                tmp = deleteHelper(sucNode, sucNode->rightKey.first);
            }
            */

            node->leftKey = tmpSucPair;
            node->leftKey.second--;
            count = node->leftKey.second;
        }
        else if(inRight){
            ternaryTreeNode* preNode = findPredecessor(node, "right");
            pair<string, int> tmpPrePair;
            if(preNode->rightKey.second > 0){
                tmpPrePair = preNode->rightKey;
                while(preNode->rightKey.second > 1){
                    preNode->rightKey.second--;
                }
                tmp = deleteHelper(preNode, preNode->rightKey.first);
            }
            else{
                tmpPrePair = preNode->leftKey;
                while(preNode->leftKey.second > 1){
                    preNode->leftKey.second--;
                }
                tmp = deleteHelper(preNode, preNode->leftKey.first);
            }
            node->rightKey = tmpPrePair;
            node->rightKey.second--;
            count = node->rightKey.second;
        }
        return count;
    }
    if(node->right != NULL){
        ternaryTreeNode* sucNode = findSuccessor(node, "right");
        pair<string, int> tmpPair;
        if(sucNode->leftKey.second > 0){
            tmpPair = sucNode->leftKey;
            while(sucNode->leftKey.second > 1){
                sucNode->leftKey.second--;
            }
            tmp = deleteHelper(sucNode, sucNode->leftKey.first);
        }
        /*
        else{
            tmpPair = sucNode->rightKey;
            while(sucNode->rightKey.second > 1){
                sucNode->rightKey.second--;
            }
            tmp = deleteHelper(sucNode, sucNode->rightKey.first);
        }
        */
        int count = -1;
        if(inLeft){
            node->leftKey = tmpPair;
            node->leftKey.second--;
            node->swapKey();
            count = node->leftKey.second;
        }
        else if(inRight){
            node->rightKey = tmpPair;
            node->rightKey.second--;
            count = node->rightKey.second;
        }
        return count;
    }
    return -1;
}

ternaryTreeNode* ternarySearchTree::findPredecessor(ternaryTreeNode* node, string key){
    if(key == "left"){
        node = node->left;
        while(node->right != NULL){
            node = node->right;
        }
    }
    else if(key == "right"){
        node = node->middle;
        while(node->right != NULL){
            node = node->right;
        }
    }
    return node;
}

ternaryTreeNode* ternarySearchTree::findSuccessor(ternaryTreeNode* node, string key){
    if(key == "left"){
        node = node->middle;
        while(node->left != NULL){
            node = node->left;
        }
    }
    else if(key == "right"){
        node = node->right;
        while(node->left != NULL){
            node = node->left;
        }
    }
    return node;
}

void ternarySearchTree::range_search(string word1, string word2){
    inOrder(root, word1, word2);
}

void ternarySearchTree::inOrder(ternaryTreeNode* node, string word1, string word2){
    if(node == NULL){
        return;
    }
    if(node != NULL){
        if(node->rightKey.first.compare("") != 0){
            if(word1.compare(node->leftKey.first) == 0 || word1.compare(node->rightKey.first) == 0){
                cout << word1 << endl;
            }
            inOrder(node->left, word1, word2);
            if(word1.compare(node->leftKey.first) < 0 && node->leftKey.first.compare(word2) < 0){
                cout << node->leftKey.first << endl;
            }
            inOrder(node->middle, word1, word2);
            if(word1.compare(node->rightKey.first) < 0 && node->rightKey.first.compare(word2) < 0){
                cout << node->rightKey.first << endl;
            }
            inOrder(node->right, word1, word2);
            if(word2.compare(node->rightKey.first) == 0 || word2.compare(node->leftKey.first) == 0){
                cout << word2 << endl;
                return;
            }
        }
        else if(node->rightKey.first.compare("") == 0){
            if(word1.compare(node->leftKey.first) == 0){
                cout << word1 << endl;
            }
            if(word1.compare(node->leftKey.first) < 0){
                cout << node->leftKey.first << endl;
            }
        }
    }
}