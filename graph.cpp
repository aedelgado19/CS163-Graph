/* Author: Allison Delgado
   Class: CS 163 Spring 2021

   graph.cpp contains all member functions for the graph
   class. This data structure is a weighted graph used to
   in the application of a trail organizer where a vertex
   is a trail head and an edge represents the trail.

   Last updated: June 3, 2021
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
  deallocate_all();
}

/* a function to deallocate all
   dynamic memory from the graph. It first stops 
   at every array index then deletes each node in the 
   vertex's edge chain */
void graph::deallocate_all(){
  node* current = NULL;
  
  for(int i = 0; i < list_size; i++){
    current = array[i]->head;
    while(current->next){
      node* temp = current->next;
      delete current;
      current = temp;
    }
    delete [] array[i]->label;
  }
}

/* a wrapper function to add a vertex to the graph. 
   It is supplied the name, and checks if the vertex
   is existing. */
   
int graph::add_vertex(char* name){
  //first check if that vertex already exists

  if(array[0] != NULL){
    for(int i = 0; i < list_size; i++){
      if(strcmp(name, array[i]->label) == 0){
	return -1;
      }
    }
  }
  return add_vertex(array[0], name);
}

/* this function finds the next available slot
   and adds in the vertex. If the table is full, it returns 0. */
int graph::add_vertex(vertex* current, char* name){
  bool flag = false; // a flag to see if the array is completely full
  //walk through the table
  for(int i = 0; i < list_size; i++){
    if(array[i] != NULL){ //found an open slot
      flag = true;
      vertex* new_vertex = new vertex;
      new_vertex->label = new char[150];
      strcpy(new_vertex->label, name);
      new_vertex->head = NULL;
    }
  }
  if(flag == false) return 0;
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
  
  //find the vertex that it connects to
  for(int i = 0; i < list_size; i++){
    if(strcmp(array[i]->label, connect1) == 0){
      flag1 = true;
      index1 = i;
    }
    if(strcmp(array[i]->label, connect2) == 0){
      flag2 = true;
      index2 = i;
    }
  }
  if(flag1 == false || flag2 == false) return 0;
  
  node* new_node = new node;
  new_node->length = length;
  new_node->difficulty = difficulty;
  new_node->connection = array[index2];
  new_node->next = NULL;
  add_edge(array[index1], new_node);
  return 1;
}

/* this function finds the vertex node in the
   array and chains itself onto its LLL.
   If it cannot find the vertex given, it will return 0. */
int graph::add_edge(vertex* connect, node*& to_add){
  bool flag = false;
  node* current = NULL;
  
  for(int i = 0; i < list_size; i++){
    if(strcmp(array[i]->label, connect->label) == 0){
      flag = true;
      current = array[i]->head;
      while(current->next){
	current = current->next;
      }
      current->next = to_add;
    }
  }
  return 1;
}

int graph::display_adjacent(char* name){

  return 0;
}

int graph::display_adjacent(vertex* current, char* name){

  return 0;
}

int graph::display_all(){

  return 0;
}

int graph::display_all(vertex* current){

  return 0;
}
