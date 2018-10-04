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

        try:
            index = self.aList.index(value)
            return True
        except:
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
        if (index < 0 or index > self.length):
            print("insertAtIndex Error: Index is not in valid range of ArrayList")
            print("insertAtIndex Error: Index passed is '%d' ArrayList length is '%d'" % (index, self.length))
            return False

        # Make sure the item does not already exist in the list
        if self.searchArrayList(value):
            print("Item '%s' already exists in the list.  Cannot add" % str(value))
            return False        

        self.aList.insert(index,value)

        self.length += 1
        return True

    def isItemAtEqual(self, index, value):

        try:
            loc = self.aList.index(value)
            if loc == index:
                return True
        except:
            return False

    def removeAtIndex(self, index):

        if (index < 0 or index > self.length):
            print("removeAtIndex Error: Index is not in valid range of ArrayList")
            print("removeAtIndex Error: Index passed is '%d' ArrayList length is '%d'" % (index, self.length))
            return False

        value = self.aList[index]

        self.aList.remove(value)
        self.length -= 1

    def printList(self):

        print("[ ", end="")
        for i in range(0, self.length):
            if (i%10 == 0 and i != 0):
                print("\n")
            print("%s, " % self.aList[i], end="")

        print("]\n")

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
    arrayList.insertAtIndex(1,45)
    arrayList.printList()

    print(arrayList.isItemAtEqual(0,99))

    rem = arrayList.removeAtIndex(2)
    arrayList.printList()
