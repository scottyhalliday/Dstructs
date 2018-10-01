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
  int getMaxSize();
  bool const isEmpty();
  bool isFull() const;      // Recall: const after function declaration indicates that the function cannot change class access specifiers
};

#endif
