#include "ternaryTreeNode.h"

ternaryTreeNode::ternaryTreeNode(){



    parent = NULL;
    left = NULL;
    middle = NULL;
    right = NULL;
}

ternaryTreeNode::ternaryTreeNode(string key){
    leftKey = make_pair(key, 1);

    parent = NULL;
    left = NULL;
    middle = NULL;
    right = NULL;
}
ternaryTreeNode::~ternaryTreeNode(){
    delete parent;
    delete left;
    delete middle;
    delete right;
}

void ternaryTreeNode::setKey(string key){
    if((leftKey.first).compare("") == 0){
        leftKey = make_pair(key, 1);
    }
    else if((rightKey.first).compare("") == 0){
        rightKey = make_pair(key, 1);
        if(leftKey.first > rightKey.first){
            swapKey();
        }
    }
}

void ternaryTreeNode::swapKey(){
    pair<string, int> tmp = leftKey;
    leftKey = rightKey;
    rightKey = tmp;
}