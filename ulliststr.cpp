#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val)
{
  if(empty()){
    //first node
    Item* node = new Item();
    head_ = node;
    tail_ = node;
  }

  //if tail block is full, add new tail block
  if(tail_->last == ARRSIZE){
    Item* node = new Item();
    node->prev = tail_;
    node->next = nullptr;
    tail_->next = node;
    tail_ = node;
  }

  //tail_->last and advance
  tail_->val[tail_->last] = val;
  tail_->last = tail_->last + 1;
  size_ = size_ + 1;
}

void ULListStr::push_front(const std::string& val)
{
  //empty list case
  if(head_ == nullptr){
    Item* node = new Item();
    node->first = ARRSIZE - 1;
    node->last = ARRSIZE;
    node->val[node->first] = val;
    node->prev = nullptr;
    node->next = nullptr;
    head_ = node;
    tail_ = node;
    size_ = size_ + 1;
    return;
  }

  //use space before head_->first if there is any
  if(head_->first > 0){
    head_->first = head_->first - 1;
    head_->val[head_->first] = val;
    size_ = size_ + 1;
    return;
  }

  //no space, add a new head node and place value at ARRSIZE-1
  Item* node = new Item();
  node->prev = nullptr;
  node->next = head_;
  head_->prev = node;
  head_ = node;

  head_->first = ARRSIZE - 1;
  head_->last = ARRSIZE;
  head_->val[head_->first] = val;

  size_ = size_ + 1;
}

void ULListStr::pop_back()
{
  if(size_ == 0){
    return;
  }

  //remove one from back of tail_
  tail_->last = tail_->last - 1;

  //delete block if empty
  if(tail_->first == tail_->last){
    Item* prev = tail_->prev;
    delete tail_;
    tail_ = prev;
    if(tail_ == nullptr){
      head_ = nullptr;
    } else {
      tail_->next = nullptr;
    }
  }
  size_ = size_ - 1;
}

void ULListStr::pop_front()
{
  if(size_ == 0){
    return;
  }

  //remove one from front of head_
  head_->first = head_->first + 1;

  //delete block if empty
  if(head_->first == head_->last){
    Item* next = head_->next;
    delete head_;
    head_ = next;
    if(head_ == nullptr){
      tail_ = nullptr;
    } else {
      head_->prev = nullptr;
    }
  }
  size_ = size_ - 1;
}

std::string const & ULListStr::back() const
{
  if(size_ == 0){
    throw std::invalid_argument("empty list");
  }
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
  if(size_ == 0){
    throw std::invalid_argument("empty list");
  }
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc >= size_){
    return nullptr;
  }

  Item* temp = head_;
  size_t offset = loc;

  while(temp != nullptr){
    size_t count = temp->last - temp->first;
    if(offset < count){
      //target is inside this block
      size_t index = temp->first + offset;
      return &(temp->val[index]);
    } else {
      //skip block
      offset = offset - count;
      temp = temp->next;
    }
  }

  return nullptr;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
