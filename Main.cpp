//Main file to create a red black tree in c++
//Date: March 23, 2018
//Created by: Ethan Reese

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Node{
     int data;
     Node* left;
     Node* right;
     bool Black;
}

struct Node* newNode(int element);
void printTree(Node* head, int indentation);

int main(){




}
//Shortcut to initialize new nodes as they are created
struct Node* newNode(int data){
     struct Node* node = new struct Node();
     node->data = data;
     node->right = NULL;
     node->left = NULL;
     return node;
}
//Print out the tree in nice tree form
void printTree(Node* node, int indentation){
     char color = 'b';
     if(node != NULL){
          //Get the indentation in the right place
          if(indentation)
               cout << std::setw(indentation) << ' ';
          if(node->black){
               color = 'b';
          }
          else{
               color = 'r';
          }
          cout << node->data << color << '\n';
          //Recursively call on the left
          if(node->left){
               printTree(node->left, indentation-6);
          }
          //Recursively call on the right
          if(node->right){
               printTree(node->right, indentation+4);
          }
     }
}
