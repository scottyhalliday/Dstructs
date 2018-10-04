import sys

class ArrayList:

    def __init__(self, size=100):
        self.aList   = []
        self.maxSize = size
        self.length  = 0

    # Clear the ArrayList
    #
    # Could simply use the Python list properties to clear but this will
    # attempt to keep the data structure behavior in line with other
    # implementations
    def clear(self):
        self.length = 0

    def getMaxSize(self):
        return self.maxSize

    def getLength(self):
        return self.length

    def isEmpty(self):
        return (self.length == 0)

    def isFull(self):
        return (self.length == self.maxSize-1)

    def searchArrayList(self, value):
        for i in range(0, self.length):
            if (self.aList[i] == value):
                return True
        return False

    def insertAtEnd(self, value):

        # Make sure the item does not already exist in the list
        if self.searchArrayList(value):
            print("Item '%s' already exists in the list.  Cannot add" % str(value))
            return False

        if (self.length >= len(self.aList)):
            self.aList.append(value)
        else:
            self.aList[self.length] = value

        self.length += 1
        return True

    def insertAtIndex(self, index, value):

        # Make sure index is an integer type
        if type(index) is not int:
            print("insertAtIndex Error: Index argument must be integer")
            return False

        # Check the index range
        if (index < 0 || index > self.length):
            print("insertAtIndex Error: Index is not in valid range of ArrayList")
            print("insertAtIndex Error: Index passed is '%d' ArrayList length is '%d'" % (index, self.length))
            return False

    def printList(self):

        print("[ ", end="")
        for i in range(0, self.length):
            if (i%10 == 0 and i != 0):
                print("\n")
            print("%s, " % self.aList[i], end="")

        print("]\n")

#  void insertAtIndex(const int index, const arrayType& value);
#  void print() const;
#  bool isItemAtEqual(const int index, const arrayType& value) const;
#  void removeAtIndex(const int index);
#  void remove(const arrayType& value);
#  int searchArrayList(const arrayType& value) const;
#  int getItemAtIndex(const int index, arrayType& value);


# -----------------------------------------------------------------------------
if __name__ == "__main__":

    # Create an ArrayList (don't care about type since python lets you mix)
    arrayList = ArrayList(50)

    print("aList is what size? %d" % len(arrayList.aList))
    print(arrayList.isFull())

    inputList = [1,2,3,4,"hello"]

    for i in inputList:
        arrayList.insertAtEnd(i)

    print("aList is what size? %d" % len(arrayList.aList))
    arrayList.printList()
    arrayList.insertAtIndex(1,2)
