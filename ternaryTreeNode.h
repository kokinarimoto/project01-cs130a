#include <string>
#include <utility>

using namespace std;

class ternaryTreeNode{
    public:
        ternaryTreeNode();
        ternaryTreeNode(string key);
        ~ternaryTreeNode();

        //
        void setKey(string key);
        //
        void swapKey();
        
        pair<string, int> leftKey;
        pair<string, int> rightKey;

        ternaryTreeNode *parent;
        
        ternaryTreeNode *left;
        ternaryTreeNode *middle;
        ternaryTreeNode *right;
};