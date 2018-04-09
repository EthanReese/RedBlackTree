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
     bool is_black;
}

struct Node* newNode(int element);
void printTree(Node* head, int indentation);

int main(){
     bool going = true;
     //Keep getting inputs until the user asks to stop
     char* input;
     Node* head = NULL;
     cout << "Enter the character I if you would prefer to be prompted for input: " << endl;
     char* input_1;
     input_1 = new char[80];
     cin >> input_1;
     if(strcmp(input_1, "I") == 0){
          cout << "Enter the numbers and enter the character N when done." << endl;
          while(going){
               cout << "Number: ";
               input =  new char[80];
               cin >> input;
               //If the user inputs the N then the program needs to stop
               if(strcmp(input, "N") == 0){
                    going = false;
                    delete input;
                    printTree(head, 20);
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
     else{
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
          while(inFile >> x){
               head = addNode(x, head);
          }
          printTree(head, 20);
          delete input;
     }
}
//Shortcut to initialize new nodes as they are created
struct Node* newRedNode(int data){
     struct Node* node = new struct Node();
     node->data = data;
     node->right = NULL;
     node->left = NULL;
     node->isBlack = false;
     return node;
}
struct Node* newBlackNode(int data){
     struct Node* node = new struct Node();
     node->data = data;
     node->right = NULL;
     node->left = NULL;
     node->isBlack = true;
     return node;
}
//Print out the tree in nice tree form
void printTree(Node* node, int indentation){
     char color = 'b';
     if(node != NULL){
          //Get the indentation in the right place
          if(indentation)
               cout << std::setw(indentation) << ' ';
          if(node->is_black){
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
struct Node* addNode(int element, Node* &current){
     struct Node* n = newRedNode(int element);
     
     insert(
}
