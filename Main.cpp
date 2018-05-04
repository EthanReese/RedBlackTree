//Main file to create a red black tree in c++
//Date: March 23, 2018
//Created by: Ethan Reese

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <deque>
#include <list>
#include <queue>

using namespace std;

struct Node{
     int data;
     Node* left;
     Node* right;
     Node* parent;
     bool is_black;
};

struct Node* newRedNode(int data);
struct Node* newBlackNode(int data);
void rotateRight(Node* node);
void printTree(Node* head);
void rotateLeft(Node* node);
void fixTree(Node* node);
void findLeaf(struct Node* current, struct Node* n);
struct Node* addNode(int element, Node* &root);

int main(){
     bool going = true;
     //Keep getting inputs until the user asks to stop
     char* input;
     Node* head = NULL;
     cout << "Enter the character I for input prompts and enter the character F for file entry:  " << endl;
     char* input_1;
     input_1 = new char[80];
     cin >> input_1;
     if(strcmp(input_1, "I") == 0){
          cout << "Enter the numbers separated by returns and enter the character N when done or P to print." << endl;
          while(going){
               cout << "Number: ";
               input =  new char[80];
               cin >> input;
               //If the user inputs the N then the program needs to stop
               if(strcmp(input, "N") == 0){
                    going = false;
                    printTree(head);
               }
               //If they put in P then it prints it
               if(strcmp(input, "P") == 0){
                    printTree(head);
               }
               //The directions say to ignore 0
               else if(strcmp(input, "0") == 0){ 
               } 
               else{
                       //Turn the input into an integer
                       stringstream convert;
                       convert << input;
                       int element = 0;
                       convert >> element;
                       delete input;
                       if(head != NULL){
                         head = addNode(element, head);
                       }
                       else{
                         head = newBlackNode(element);
                       }
               }
          }
     }
     else if(strcmp("F", input_1) == 0){
          cout << "Please enter the filename of the file you would like to read in: ";
          input = new char[1000];
          cin >> input;
          //Open up the file with a stream
          ifstream inFile;
          inFile.open(input);
          if(!inFile){
               return 1;
          }
          int x;
          while(inFile){
               //The adding function gets slightly screwed up if the head is null
               char* input_1 = new char[1000];
               inFile.getline(input_1, 1000, ',');
               stringstream convert;
               convert << input_1;
               int element = 0;
               convert >> element;
               if(head == NULL){
                    head = newBlackNode(element);
               }
               else{   
                         head = addNode(element, head);
               }
               if(inFile.eof()){
                    break;
               }
          }
          printTree(head);
          delete input;
          delete[] input_1;
     }
}
//Shortcut to initialize new nodes as they are created
struct Node* newRedNode(int data){
     struct Node* node = new struct Node();
     node->data = data;
     node->right = NULL;
     node->left = NULL;
     node->parent = NULL;
     node->is_black = false;
     return node;
}
struct Node* newBlackNode(int data){
     struct Node* node = new struct Node();
     node->data = data;
     node->right = NULL;
     node->left = NULL;
     node->parent = NULL;
     node->is_black = true;
     return node;
}
//Print out the tree in nice tree form
void printTree(Node* node){
     queue<Node*> q;
     q.push(node);
     cout << "Tree: " << endl;
     bool moreonlevel = true;
     //Keep going while there are still nodes on the level.
     while(moreonlevel){
          int levelCount = q.size();
          moreonlevel = false;
          while(levelCount > 0){
                  Node* n = q.front();
                  q.pop();
                  if(n == NULL){
                         cout << "_ ";
                         q.push(NULL);
                         q.push(NULL);
                  }
                  else{
                          //Say that there are more nodes that can be checked and add the proper nodes to the tree.
                          moreonlevel = true;
                          char color = 'R';
                          if(n->is_black){
                              color = 'B';
                          }
                          cout << n->data << color << " ";
                          q.push(n->left);
                          q.push(n->right);
                  }
                  //It went through one of the levels so take the counter down.
                  levelCount--;
          }
          //End of a tree level
          cout << endl;

     }
}
struct Node* addNode(int element, Node* &root){
     struct Node* n = newRedNode(element);

     //Place the node in the tree just like a binary tree
     findLeaf(root, n);
     
     //Fix up the whole tree so that the properties are preserved
     fixTree(n);

     //Find the new root of the tree since sometimes it gets screwed up
     while(n->parent != NULL){
          n = n->parent;
     }
     n->is_black = true;
     return n;
     
}
//Get the grandparent of a node and make sure its not NULL
struct Node* grandParent(Node* node){
     if(node->parent != NULL){
          Node* parent = node->parent;
          if(parent->parent != NULL){
               return parent->parent;
          }
          return NULL;
     }
     return NULL;
}
//Find the sibling given a node. This is just for convenience in rotations
struct Node* sibling(Node* node){
     //If its the root it cannot have a sibling
     if(node->parent == NULL){
          return NULL;
     }
     if(node->parent->left == node){
          return node->parent->right;
     }
     else{
             return node->parent->left;
     }
}
//Find the uncle of a given node. This is for convenience
struct Node* uncle(Node* node){
     //The uncle is the parent's sibling
     return sibling(node->parent);
}
//Recursively go through the tree until it finds a leaf where the node can go.
void findLeaf(struct Node* current, struct Node* n){
     //Descend the tree looking for a slot
     if(n->data < current->data){
          //check if there is a slot for the node immediately
          if(current->left != NULL){
               //Continue looping through but with using the left node as the root
               findLeaf(current->left, n);
               return;
          }
          else{
               current->left = n;
          }
     }
     //Go the other way for a greater value
     else{
          //Check if there is an immediate slot to the right
          if(current->right != NULL){
               findLeaf(current->right, n);
                  return;
          }
          else{
               current->right = n;
          }
     }
     
     //Give the new node the right properties
     n->parent = current;
     n->is_black = false;
}
void fixTree(Node* node){   
     if(node->parent == NULL){
          node->is_black = true;
     }
     else if(node->parent->is_black){
          return;
     }
     //Case 2: The Node's parent is red and the uncle is also red
     else if(uncle(node) != NULL && (uncle(node)->is_black) == false){
          //Make the parent and uncle black
          node->parent->is_black = true;
          uncle(node)->is_black = true;
          //But make the grandparent red to preserve the red black tree property
          grandParent(node)->is_black = false;
          //Then recurse
          fixTree(grandParent(node));
     }
     //Case 4: Something else is going on
     else{
          if(grandParent(node) != NULL && grandParent(node)->left != NULL &&(node == (grandParent(node)->left->right))){
               rotateLeft(node->parent);
               node = node->left;
          }
          else if(grandParent(node) != NULL && grandParent(node)->right != NULL && (node == grandParent(node)->right->left)){
               rotateRight(node->parent);
               node = node->right;
          }
          if(node->parent->left == node){
               rotateRight(grandParent(node));
          }
          else{
               rotateLeft(grandParent(node));
          }
          if(node->parent != NULL){
                  node->parent->is_black = true;
          }
          if(grandParent(node) != NULL){
               grandParent(node)->is_black = false;
          }
     }
}
//Rotate the tree left around a node
void rotateLeft(Node* node){
     //This happened a surprising amount
     if(node == NULL){
             return;
     }
     struct Node* temp = node->right;
     //Make sure the new node isn't a leaf
     if(temp == NULL){
          return;
     }
     node->right = temp->left;
     if(node->right != NULL){
             node->right->parent = node;
     }
     temp->left = node;
     temp->parent = node->parent;
     if(temp->parent != NULL){
          if(temp->parent->right == node){
               temp->parent->right = temp;
          }
          else{
               temp->parent->left = temp;
          }
     }
     node->parent = temp;
     node->is_black = false;
}
//Rotate the tree right around a node
void rotateRight(Node* node){
     struct Node* temp = node->left;
     //Make sure the new node isn't a leaf
     if(temp == NULL){
          return;
     }
     node->left = temp->right;
     if(node->left != NULL){
             node->left->parent = node;
     }
     temp->right = node;
     temp->parent = node->parent;
     if(node->parent != NULL){
          if(temp->parent->left == node){
             temp->parent->left = temp;
          }
          else{
             temp->parent->right = temp;
          }
     }
     node->parent = temp;
     node->is_black = false;
}
