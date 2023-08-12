#include <iostream>
using namespace std;
//declaration of a binary tree
struct Node{
    int data;
    Node* left;
    Node* right;
};
class Node
{
public:
    Node()
    {
        left = NULL;
        right = NULL;
    }
    Node(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
    
};
//insert a new node into tree
Node* root;

bool isEmpty(){
    if(root == NULL)
    {
        return 1;
    }else{
        return 0;
    }
}
void insertNode(Node* root, int data){
    if(root == NULL){
        Node* root = new Node();
        root->data = data;
        root->left = root->right = NULL;
    }
    else {
        while (root != NULL){
            if

        }
    }
}


