//----------------------------------------------------------------------
// FILE: linked_list.h
// NAME: Maria Elena Aviles-Baquero
// DATE: December 06, 2020
// DESC: Implements a linked list version of the list class. Elements
//       are added by default to the end of the list via a tail pointer.
//----------------------------------------------------------------------


#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "list.h"

template<typename T>
class LinkedList : public List<T>
{
public:
  LinkedList();
  LinkedList(const LinkedList<T>& rhs);
  ~LinkedList();
  LinkedList& operator=(const LinkedList<T>& rhs);

  void add(const T& item);
  bool add(size_t index, const T& item);
  bool get(size_t index, T& return_item) const;
  bool set(size_t index, const T& new_item);
  bool remove(size_t index);
  size_t size() const;
  void selection_sort();
  void insertion_sort();

private:
  struct Node {
    T value;
    Node* next;
  };
  Node* head;
  Node* tail;
  size_t length;

  // helper to delete linked list
  void make_empty();
  
};


// Constructor for Linked List
template<typename T>
LinkedList<T>::LinkedList()
  : head(nullptr), tail(nullptr), length(0)
{
}

// Copy Constructor for Linked List
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
  : head(nullptr), tail(nullptr), length(0)
{
  // defer to assignment operator
  *this = rhs;
}

// Destructor for Linked List
template<typename T>
LinkedList<T>::~LinkedList()
{
  make_empty();
}

// Assignment Operator Overloading for Linked List
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
  if(this != &rhs)  
  {
    make_empty();

    Node* temp = rhs.head;

    // Creates a copy of the list
    while(temp)
    {
      add(temp->value);
      temp = temp->next;
    }
  }
  return *this;
}
  
// Adds an item to the end of the linked list
template<typename T>
void LinkedList<T>::add(const T& item) 
{ 
  
  Node* new_node = new Node;
  new_node->value = item;
  new_node->next = nullptr;

  if(length > 0) {
    tail->next = new_node;
    tail = new_node;
  }
  else {
    head = new_node;
    tail = new_node;
  }
  length++;
}

// Adds an item to index of the linked list
template<typename T>
bool LinkedList<T>::add(size_t index, const T& item)
{ 
  // Checks if the index is valid
  if(index >= 0 && index <= length-1)
  {
    Node* temp = new Node;
    temp->value = item;
    temp->next = nullptr;

    // Checks if the index is the head of the list
    if(index == 0)
    {
      temp->next = head;
      head = temp;
      // If there is one item in the list
      if(temp->next == nullptr) 
        tail = temp;
      return 1;
    }
    else
    {
      Node* curr = head;
      // Iterates through the list until index -1 is reached
      for(int i = 1; i < index; i++)
      {
        curr = curr->next;
      }
      temp->next = curr->next;
      curr->next = temp;
    }
    // Reassigns the tail pointer
    if(temp->next == nullptr)
      tail = temp;

    length++;
    return 1;
  }
  return 0;
}

// Returns the item at specified index
template<typename T>
bool LinkedList<T>::get(size_t index, T& return_item) const 
{ 
  // Checks if the index is valid
  if(index >= 0 && index <= length - 1)
  {
    Node* curr = head;
    int num = 0;

    // Increments through curr list until index is found
    while(curr != nullptr)
    {
      if(num == index)
        return_item = curr->value;
      num++;
      curr = curr->next;
    }
    return 1;
  }
  return 0;
}

// Sets an item at index to a new item
template<typename T>
bool LinkedList<T>::set(size_t index, const T& new_item) 
{ 
  // Checks if the index is valid
  if(index >= 0 && index <= length - 1)
  {
    Node* curr = head;
    int num = 0;
    // Increments through curr list until index is found
    while(curr != nullptr)
    {
      if(num == index)
        curr->value = new_item;
      num++;
      curr = curr->next;
    }
    return 1;
  }
  return 0;
}

// Removes an item at specified index
template<typename T>
bool LinkedList<T>::remove(size_t index)
{ 
  // Checks if the index is valid
  if((index >= 0) && (index <= length - 1) && (head != nullptr))  
  { 
    // Checks if index is head of list
    if(index == 0)
    {
      // Check if list has one item
      if(head->next == nullptr)
      {
        Node* temp1 = head;
        head = head->next;
        delete temp1;
        temp1 = nullptr;
        tail = head;
      }
      // Checks if list is empty
      else if(length == 0)
      {
        tail = nullptr;
      }
      // Runs if the list is not empty and there is more than one item is list
      else {
        Node* temp_1a = head;
        head = head->next;
        delete temp_1a;
        temp_1a = nullptr;
      }   
    }
    // Checks if the index is at the end of the list
    else if(index == (length-1))
    {
      Node* temp2 = head;
      Node* prev_1 = head;

      // Traverses through to the end of the list
      while(temp2->next != nullptr)
      {
        prev_1 = temp2;
        temp2 = temp2->next;
      }

      tail = prev_1;
      prev_1->next = nullptr;
      delete temp2;
      temp2 = nullptr;
    }
    // Runs if the index is neither the head or the tail of the list
    else {
      Node* curr = head;
      Node* prev_2;

      // Traverses through the list until index - 1
      for(int i = 0; i < index; ++i)
      {
        prev_2 = curr;
        curr = curr->next;
      }
      prev_2->next = curr->next;
      delete curr;
      curr = nullptr;
    }

    length--; 
    return 1;
  }
  return 0;
}

// Returns the length of the linked list
template<typename T>
size_t LinkedList<T>::size() const 
{ 
  return length;
}

// Empties the linked list
template<typename T>
void LinkedList<T>::make_empty() 
{  
  Node* temp = head;
  while(head) 
  {
    temp = temp->next;
    delete head;
    head = temp;
  }
  length = 0;
}

// Sorts the linked list using this the selection sort algorithm
template<typename T>
void LinkedList<T>::selection_sort()
{
  int count = length - 1;
  int idx;

  // iterates through the linked list 
  for(int i = 1; i < length; ++i)
  {
    Node* min = head;
    Node* ptr = head;
    idx = 0;
    for(int j = 1; j < count; ++j)
    {
      // if a previous pointer is less than the ptr ahead, the idx is noted and min value is set
      ptr = ptr->next;
      if(ptr->value < min->value)
      {
        min = ptr;
        idx = j;
      }
    }

    // the min value is added as a new node and the node at idx is removed
    add(min->value);
    remove(idx);
    count--;
  }
}

  

// Sorts the linked list using this the insertion sort algorithm
template<typename T>
void LinkedList<T>::insertion_sort()
{
  Node* sorted = head;
  Node* ptr = head->next;

  // while head->next is not null, while the ptr is not equal to the tail of the list
  while(ptr != nullptr)
  {
    Node* curr = ptr;
    ptr = ptr->next;
    sorted->next = ptr;
    curr->next = nullptr;

    // if the value at curr is less than the head's value, then curr is made to be the new head
    if(curr->value < head->value)
    {
      curr->next = head;
      head = curr;
    }
    // otherwise, we go through the rest of the list to compare values
    else {
      Node* tmp = head->next;
      Node* prev = head;

      while((curr->value > tmp->value) && (tmp != ptr))
      {
        prev = tmp;
        tmp = tmp->next;
      }

      if(tmp == sorted)
      {
        sorted->next = curr;
        curr->next = ptr;
        sorted = sorted->next;
      }
      else {
        prev->next = curr;
        curr->next = tmp;
      }
    }
  }
  tail = sorted;
}


#endif