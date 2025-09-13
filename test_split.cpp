/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include <vector>
#include <iostream>
#include "split.h"

//build a list from a vector
Node* buildList(const std::vector<int>& vals){
  Node* head = nullptr;
  Node* tail = nullptr;

  for(size_t i = 0; i < vals.size(); i++){
    Node* n = new Node(vals[i], nullptr);
    //n->value = vals[i];
    //n->next = nullptr;

    if(head == nullptr){
      head = n;
      tail = n;
    } else {
      tail->next = n;
      tail = n;
    }
  }
  return head;
}

//free all nodes in list
void freeList(Node* head){
  while(head != nullptr){
    Node* nextNode = head->next;
    delete head;
    head = nextNode;
  }
}

//convert list to vector (for comparison)
std::vector<int> toVector(Node* head){
  std::vector<int> out;
  Node* p = head;
  while(p != nullptr){
    out.push_back(p->value);
    p = p->next;
  }
  return out;
}

//compare list with expected values
bool equals(Node* head, const std::vector<int>& expect){
  std::vector<int> exists = toVector(head);
  if(exists.size() != expect.size()){
    return false;
  }
  for(size_t i = 0; i < exists.size(); i++){
    if(exists[i] != expect[i]){
      return false;
    }
  }
  return true;
}

//print linked list
void printList(Node* head){
  std::cout << "[";
  Node* p = head;
  bool first = true;
  while(p != nullptr){
    if(!first){
      std::cout << " ";
    }
    std::cout << p->value;
    first = false;
    p = p->next;
  }
  std::cout << "]";
}

bool runTestCase(const char* name, const std::vector<int>& input,
                                   const std::vector<int>& expectOdds,
                                   const std::vector<int>& expectEvens)
{
  Node* in = buildList(input);
  Node* odds = nullptr;
  Node* evens = nullptr;

  split(in, odds, evens);

  bool inCleared = (in == nullptr);
  bool okOdds = equals(odds, expectOdds);
  bool okEvens = equals(evens, expectEvens);

  bool pass = inCleared && okOdds && okEvens;

  if(pass){
    std::cout << "[PASS] " << name << "\n";
  } else {
    std::cout << "[FAIL] " << name << "\n";

    std::cout << "in cleared ";
    if(inCleared){
      std::cout << "yes\n";
    } else {
      std::cout << "no\n";
    }

    std::cout << "expected odds ";
    Node* tmp1 = buildList(expectOdds);
    printList(tmp1);
    std::cout << "\n";

    std::cout << "got odds ";
    printList(odds);
    std::cout << "\n";
    freeList(tmp1);

    std::cout << "expected evens ";
    Node* tmp2 = buildList(expectEvens);
    printList(tmp2);
    std::cout << "\n";

    std::cout << "got evens ";
    printList(evens);
    std::cout << "\n";
    freeList(tmp2);
  }

  freeList(odds);
  freeList(evens);

  return pass;
}

int main(int argc, char* argv[])
{
  int passed = 0;
  int total = 0;

  //case 1
  total = total + 1;
  if(runTestCase("mixed", std::vector<int>{-2, 0, 1, 2, 3, 4, 7, 8},
                          std::vector<int>{1, 3, 7},
                          std::vector<int>{-2, 0, 2, 4, 8}))
  {
    passed = passed+1;
  }

  //case 2
  total = total + 1;
  if(runTestCase("all odds", std::vector<int>{1, 3, 5, 9},
                             std::vector<int>{1, 3, 5, 9},
                             std::vector<int>{}))
  {
    passed = passed + 1;
  }

  //case 3
  total = total + 1;
  if(runTestCase("all evens", std::vector<int>{-4, -2, 0, 2, 8},
                              std::vector<int>{},
                              std::vector<int>{-4, -2, 0, 2, 8}))
  {
    passed = passed + 1;
  }

  std::cout << "Passed " << passed << " of " << total << "\n";
  if(passed == total){
    return 0;
  } else {
    return 1;
  }
}
