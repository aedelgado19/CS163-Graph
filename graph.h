/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   graph.h is the header file for graph.cpp.
   It contains all the function prototypes necessary
   for the ADT. This data structure is a weighted graph
   used to in the application of a trail organizer 
   where a vertex is a trail head and an edge represents
   the trail.

   Last updated: June 7, 2021 */

struct node {
  int length;
  int difficulty;
  node* next;
  struct vertex* connection;
};

struct vertex {
  char* label;
  node* head;
};

// all int return types return 1 for success
// and 0 for failure
class graph {
 public:
  graph();
  
  //task 3: destructor
  ~graph();

  //task 1: BUILD AN ADJACENCY LIST
  int add_vertex(char* name);

  //task 2: insert an edge
  int add_edge(int length, int difficulty, char* connect1, char* connect2);

  //task 4: traverse the adjacency list, display which
  //are adjacent, and display all
  int display_adjacent(char* name);
  int display_all();

 private:
  vertex** array;
  int list_size;
  
  //the recursive version of each function:
  int add_vertex(vertex* current, char* name, int i);
  int add_edge(int index, node*& to_add, node* current);
  int display_adjacent(node* current);
  int display_all(node* current);
};

