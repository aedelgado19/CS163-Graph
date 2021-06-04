/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   main.cpp acts as a testing site for the member functions
   of the graph calass. It provides user input to the cpp file,
   maintaining the rules of data abstraction (no nodes or anything
   are passed as arguments).
   
   Last updated: May 29, 2021
 */
#include <iostream>
#include <cstring>
#include "graph.h"
using namespace std;

void print_error_messages(int success, const char function_name[]);

int main(){
  int success = 0;
  graph* new_graph = new graph();
  char input[20];
  char name[150];
  int length = 0;
  int difficulty = 0;
  char connect1[150];
  char connect2[150];
  cout << " " << endl;
  cout << "******************************" << endl;
  cout << "Welcome to Trail Searcher." << endl;

  while(strcmp(input, "q") != 0){
    cout << "----------------------------" << endl;
    cout << "valid commands (so far) are: " << endl;
    cout << "addv - add vertex (trail head) " << endl;
    cout << "adde - add edge (trail)" << endl;
    //    cout << "dlist - display all nodes adjacent to a certain node" << endl;
    //    cout << "dall - display all nodes in the adjacency matrix" << endl;
    cout << "q - quit " << endl;
    cout << "> ";
    cin.get(input, 20);
    cin.get();
    cout << "----------------------------" << endl;

    for(int i = 0; i < (int) strlen(input); i++){
      input[i] = tolower(input[i]);
    }

    if(strcmp(input, "addv") == 0){
      cout << "Enter the name of the trail head." << endl;
      cout << "> ";
      cin.get(name, 150);
      cin.get();
      success = new_graph->add_vertex(name);
      print_error_messages(success, "vertex");
    }

    if(strcmp(input, "adde") == 0){
      cout << "Enter the length of the trail." << endl;
      cout << "> ";
      cin >> length;
      cin.get();
      cout << "Enter the difficulty of the trail (scale of 1-10)" << endl;
      cout << "> ";
      cin >> difficulty;
      cin.get();
      cout << "What is the first trailhead this trail connects to?" << endl;
      cout << "> ";
      cin.get(connect1, 150);
      cin.get();
      cout << "What is the second trailhead this trail connects to?" << endl;
      cout << "> ";
      cin.get(connect2, 150);
      success = new_graph->add_edge(length, difficulty, connect1, connect2);
      print_error_messages(success, "edge");
    }
  }
  delete new_graph;
  return 0;
}

void print_error_messages(int success, const char function_name[]){
  if(success == 1){ //successful
    if(strcmp(function_name, "vertex") == 0){
      cout << "Trail head added successfully." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "edge") == 0){
      cout << "Trail added successfully." << endl;
      cout << " " << endl;
    }
  } else if(success == 0){ //failure
    if(strcmp(function_name, "edge") == 0){
      cout << "Could not add that trail. " << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "vertex") == 0){
      cout << "Could not add that vertex, max amount has already been reached." << endl;
      cout << " " << endl;
    }
  } else { //special case failure
    cout << "That vertex already exists - so you can't add it again." << endl;
    cout << " " << endl;
  }
}
