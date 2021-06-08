/* Author: Allison Delgado
   Class: CS 163 Spring 2021

   graph.cpp contains all member functions for the graph
   class. This data structure is a weighted graph used to
   in the application of a trail organizer where a vertex
   is a trail head and an edge represents the trail.

   Last updated: June 7, 2021
 */
#include <iostream>
#include <cstring>
#include "graph.h"
#define SIZE 10

/* the constructor for the graph class. Initializes
   the each index in the vertex array to null and sets list size. */
graph::graph(){
  list_size = SIZE;
  array = new vertex*[SIZE];
  for(int i = 0; i < list_size; i++){
    array[i] = NULL;
  }
}

/* the destructor for the graph class.
   It calls a function to deallocate all 
   dynamic memory. */
graph::~graph(){
  node* current = NULL;

  if(!array[0]){ //if there's nothing in the array
    return;
  } else {
    for(int i = 0; i < list_size; i++){
      if(array[i]){
	current = array[i]->head;
      }
      if(current){
	while(current->next){
	  node* temp = current->next;
	  delete current;
	  current = temp;
	}
      }
      if(array[i]){
	delete [] array[i]->label;
      }
    }
  }
}

/* a wrapper function to add a vertex to the graph. 
   It is supplied the name, and checks if the vertex
   is existing. */
int graph::add_vertex(char* name){
  bool full = true; //a flag to see if the entire array is already full
  
  //first check if that vertex already exists or if the array is completely full

  for(int i = 0; i < list_size; i++){
    if(array[i] && strcmp(name, array[i]->label) == 0){
      return -1;
    }
    if(!array[i]){ //found a null spot so the array isn't completely full
      full = false;
      break;
    }
  }

  if(full == false){
    return add_vertex(array[0], name, 0);
  } else {
    return -2;
  }
}

/* this function finds the next available slot
   and adds in the vertex. the iterator is an
   integer that is incremented to walk through the array*/
int graph::add_vertex(vertex* current, char* name, int i){
  //recur if the current spot is taken
  if(array[i]){
    i++;
    add_vertex(array[i+1], name, i);
  }
  else { //found an open slot (it's null so there's nothing there)
    vertex* new_vertex = new vertex;
    new_vertex->label = new char[150];
    strcpy(new_vertex->label, name);
    new_vertex->head = NULL;
    array[i] = new_vertex;
  }
  return 1;
}

/* a wrapper function to add an edge node to the graph.
   The wrapper creates a new node, then sends the node to
   the recursive version of the function. */
int graph::add_edge(int length, int difficulty, char* connect1, char* connect2){
  bool flag1 = false; //flag to see if the first connection point exists
  bool flag2 = false; //flag to see if the second connection point exists
  int index1 = 0; //the index of the first connection point
  int index2 = 0; //the index of the second connection point

  if(!array[0]) return 0;
  //find the vertex that it connects to
  for(int i = 0; i < list_size; i++){
    if(array[i] && strcmp(array[i]->label, connect1) == 0){ //first connection point
      flag1 = true;
      index1 = i;
    }
    if(array[i] && strcmp(array[i]->label, connect2) == 0){ //second connection point
      flag2 = true;
      index2 = i;
    }
  }
  if(flag1 == false || flag2 == false) return 0; //couldn't find one or both of them
  node* new_node = new node;
  new_node->length = length;
  new_node->difficulty = difficulty;
  new_node->connection = array[index2];
  new_node->next = NULL;
  add_edge(index1, new_node, array[index1]->head);
  return 1;
}

/* this function finds the vertex node in the
   array and chains itself onto its LLL.
   If it cannot find the vertex given, it will return 0.
   the integer is the index at which the node should be connected to. */
int graph::add_edge(int index, node*& to_add, node* current){
  std::cout << "here " << std::endl;
  if(!array[index]) return 0;
  if(!current) return 0;
  if(current->next){
    std::cout << "recurring" << std::endl;
    add_edge(index, to_add, current->next);
  } else {
    std::cout << "woo" << std::endl;
    current->next = to_add;
  }
  return 1;
}

/* This function is a wrapper function to call the recursive print
   function. It displays all connecting trails for a given trailhead.
 */
int graph::display_adjacent(char* name){
  int index = 0;
  bool found = false;
  
  //find the index that the name is at
  for(int i = 0; i < list_size; i++){
    if(array[i] && strcmp(array[i]->label, name) == 0){
      index = i;
      found = true;
    }
  }

  //if you couldn't find that index, return 0
  if(found == false){
    return 0;
  }
  
  return display_adjacent(array[index]->head);
}

/* the recursive version of the above function. It
   recurs to display each of the nodes in the vertex's edge list */
int graph::display_adjacent(node* current){
  if(!current) return 0;
  if(current->next){
    std::cout << current->connection->label << std::endl;
    display_adjacent(current->next);
  } else {
    std::cout << current->connection->label << std::endl;
    return 1;
  }
  return 0;
}

/* a wrapper function to display all the nodes
   in the adjacency matrix. If the array is null,
   it returns 0. */
int graph::display_all(){
  if(!array[0]) return 0;
  for(int i = 0; i < list_size; i++){
    if(!array[i]){
      break;
      return 1;
    }
    std::cout << "Trailhead name: " << array[i]->label << std::endl;
    if(array[i]->head){
      std::cout << "Trails connecting to " << array[i]->label << ": " << std::endl;
      display_all(array[i]->head);
    }
  }
  return 1;
}

/* a recursive version of the function above used
   to print out the entire adjacency matrix */
int graph::display_all(node* current){
  if(current->next){
    std::cout << "Name: " << current->connection->label << std::endl;
    std::cout << "   length: " << current->length << std::endl;
    std::cout << "   difficulty: " << current->difficulty << std::endl;
    display_all(current->next);
  } else {
    std::cout << "Name: " << current->connection->label << std::endl;
    std::cout << "   length: " << current->length << std::endl;
    std::cout << "   difficulty: " << current->difficulty << std::endl;
  }  
  return 1;
}
