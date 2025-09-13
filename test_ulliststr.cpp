#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite
void print_list(ULListStr& L, const std::string& tag)
{
  std::cout << tag << " size=" << L.size() << " -> ";
  for(size_t i=0; i < L.size(); i++){
    std::cout << L.get(i);
    if(i + 1 < L.size()){
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}

//check if two strings match
void expect_eq_str(const std::string& a, const std::string& b, const std::string& label)
{
  if(a == b){
    std::cout << "[PASS] " << label << std::endl;
  } else {
    std::cout << "[FAIL] " << label << " expected=\"" << b << "\" got=\"" << a << "\"" << std::endl;
  }
}

//check if two size match
void expect_eq_size(size_t a, size_t b, const std::string& label)
{
  if(a == b){
    std::cout << "[PASS] " << label << std::endl;
  } else {
    std::cout << "[FAIL] " << label << " expected=" << b << " got=" << a << std::endl;
  }
}

//confirm front() throws on empty list
void expect_throw_front_on_empty(ULListStr& L, const std::string& label)
{
  bool ok = false;
  std::string temp;

  try{
    temp = L.front();
  } catch(std::invalid_argument const&){
    ok = true;
  }

  if(ok){
    std::cout << "[PASS] " << label << std::endl;
  } else {
    std::cout << "[FAIL] " << label << " expected exception" << std::endl;
  }
}

//confirm back() throws on empty list
void expect_throw_back_on_empty(ULListStr& L, const std::string& label){
  bool ok = false;
  std::string temp;

  try{
    temp = L.back();
  } catch(std::invalid_argument const&){
    ok = true;
  }

  if(ok){
    std::cout << "[PASS] " << label << std::endl;
  } else {
    std::cout << "[FAIL] " << label << " expected exception" << std::endl;
  }
}

int main(int argc, char* argv[])
{
  ULListStr L;

  //check behavior of empty list
  expect_eq_size(L.size(), 0, "empty size is 0");
  expect_throw_front_on_empty(L, "front throws on empty");
  expect_throw_back_on_empty(L, "back throws on empty");
  L.pop_front(); //does nothing
  L.pop_back(); //does nothing

  //push_backk on empty, then push_front
  L.push_back("7");
  expect_eq_size(L.size(), 1, "size after push_back 7");
  expect_eq_str(L.front(), "7", "front after push_back 7");
  expect_eq_str(L.back(), "7", "back after push_back 7");

  L.push_front("8");
  expect_eq_size(L.size(), 2, "size after push_front 8");
  expect_eq_str(L.front(), "8", "front after push_front 8");
  expect_eq_str(L.back(), "7", "back after push_front 8");
  print_list(L, "state");

  //fill list to force new tail node
  for(int i=0; i<9; i++){
    L.push_back("x");
  }
  L.push_back("9"); //start a new tail node
  expect_eq_str(L.back(), "9", "back after new tail node");
  print_list(L, "after filling and adding 9");

  //get values from front, middle, and back
  expect_eq_str(L.get(0), "8", "get(0) is 8");
  expect_eq_str(L.get(1), "7", "get(1) is 7");
  expect_eq_str(L.get(L.size()-1), "9", "get(last) is 9");

  //set values and check they were stored
  if(L.size() >= 3){
    L.set(0, "A");
    L.set(2, "B");
    expect_eq_str(L.get(0), "A", "set 0 -> A");
    expect_eq_str(L.get(1), "B", "set 1 -> B");
  }
  print_list(L, "after set calls");

  //multiple pop_back, maybe removing a node
  size_t start_size = L.size();
  for(int i=0; i<5; i=i+1){
    L.pop_back();
  }
  expect_eq_size(L.size(), start_size - 5, "size after 5 pop_back");
  print_list(L, "after 5 pop_back");

  //multiple pop_front, maybe removing a node
  for(int i=0; i<3; i++){
    L.pop_front();
  }
  expect_eq_size(L.size(), start_size - 3, "size after 3 pop_front");
  if(!L.empty()){
    std::cout << "now front=" << L.front() << " back=" << L.back() << std::endl;
  }
  print_list(L, "after 3 pop_front");

  //push_front new value "HEAD"
  L.push_front("HEAD");
  expect_eq_str(L.front(), "HEAD", "front after push_front HEAD");
  print_list(L, "after push_front HEAD");

  //push_back a new value "TAIL"
  L.push_back("TAIL");
  expect_eq_str(L.back(), "TAIL", "back after push_back TAIL");
  print_list(L, "after push_back TAIL");

  //clear list to empty and check behavior again
  while(!L.empty()){
    L.pop_front();
  }
  expect_eq_size(L.size(), 0, "size after clearing to empty");
  expect_throw_front_on_empty(L, "front throws after clear");
  expect_throw_back_on_empty(L, "back throws after clear");

  //rebuild list to check it works again
  L.push_back("x1");
  L.push_back("x2");
  L.push_front("x0");
  expect_eq_size(L.size(), 3, "rebuild size is 3");
  expect_eq_str(L.get(0), "x0", "rebuild get(0) x0");
  expect_eq_str(L.get(1), "x1", "rebuild get(1) x1");
  expect_eq_str(L.get(2), "x2", "rebuild get(2) x2");
  print_list(L, "final state");

  return 0;
}
