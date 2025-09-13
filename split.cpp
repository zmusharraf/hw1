/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  //base case - empty input
  if(in == nullptr){
    odds = nullptr;
    evens = nullptr;
    return;
  }

  //recursive case
  Node *current = in; //current node
  Node* remainder = in->next; //remainder
  current->next = nullptr; // detach

  Node* subOdds = nullptr;
  Node* subEvens = nullptr;
  split(remainder, subOdds, subEvens); //recursive
  
  if(current->value % 2 != 0){ //odd node
    current->next = subOdds;
    odds = current;
    evens = subEvens;
  } else { //even node
    current->next = subEvens;
    evens = current;
    odds = subOdds;
  }

  in = nullptr; //clear original list
}

/* If you needed a helper function, write it here */
