//
// ARRAYLIST.H
// Scott Hall
//
// Header for arrayList.cpp
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

class ArrayList {
private:
  int maxSize;
  int length;
  int *list;

public:
  ArrayList(int size=100);
  int getMaxSize() const;	// Recall: const after function declaration means we can call it on any const object while restricting change on class access specifiers
  int getLength() const;
  bool isEmpty() const;
  bool isFull() const;
  void clear();      
  void insertEnd(int value);
  void insertAt(int index, int value);
  void print() const;

};

#endif
