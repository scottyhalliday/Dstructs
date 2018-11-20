//
// LINKEDLISTNODE.H
// Scott Hall
//
// Header for linkedListNode.cpp
#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

class LinkedListNode {

// Set the members protected so that they are accessible in the class that
// defines them and the classes that inherit them
protected:
  int m_data;       // Data to be contained in the node
  int *m_nextNode;  // Pointer to the next node
  int *m_prevNode;  // Pointer to the previous node (i.e. doubly linked lists)

public:
  LinkedListNode();
 ~LinkedListNode();
  void setNodeData(int value);
  void printNodeData();
};

#endif
