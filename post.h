#include <iostream>
using namespace std;
class commentsNode
{
    public:
    string comment;
    commentsNode* left;
    commentsNode* right;
    commentsNode(string comment,commentsNode* left=nullptr,commentsNode* right=nullptr )
    {
        this->comment=comment;
        this->left=left;
        this->right=right;
    }
};


class postNode
{
    public:

    postNode* left;
    postNode* right;
    postNode(postNode* left=nullptr,postNode* right=nullptr)
    {
        this->left=left;
        this->right=right;
    }
};
class post
{
    private:
    //comments,like ki queue
 
    string message;

    public:
}; 