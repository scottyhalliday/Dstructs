//
// LINKEDLIST.H
// Scott Hall
//
// Header for linkedList.cpp
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class LinkedList {

// Set the members protected so that they are accessible in the class that
// defines them and the classes that inherit them
protected:
  int m_count;  // Number of nodes in the linked list
  int *m_head;  // Pointer to the head of the
  int *m_tail;

public:
  LinkedList();
 ~LinkedList();
  int  insertAtEnd(int value);
  bool isEmpty();

};

#endif
