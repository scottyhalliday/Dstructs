"""
ArrayList
By Scott Hall
"""

import sys

class ArrayList:

    # Initialize the ArrayList
    def __init__(self, size=100):
        self.aList   = []
        self.maxSize = size
        self.length  = 0

    # -------------------------------------------------------------------------

    # Clear the ArrayList
    #
    # Reset the Python list so we can continue to use Python convenience
    # functions.  Also set internal length tracker back to 0.
    def clear(self):
        self.length = 0
        self.aList  = []

    # -------------------------------------------------------------------------

    # Return the maximum size of the list
    #
    # This simply provides information regarding the initialized length of the
    # ArrayList
    def getMaxSize(self):
        return self.maxSize

    # -------------------------------------------------------------------------

    # Return the current location of the ArrayList end
    def getLength(self):
        return self.length

    # -------------------------------------------------------------------------

    # Is the ArrayList empty?
    def isEmpty(self):
        return (self.length == 0)

    # -------------------------------------------------------------------------

    # Is the ArrayList full?
    def isFull(self):
        return (self.length == self.maxSize)

    # -------------------------------------------------------------------------

    # Search the ArrayList for a specified value
    #
    # Simply uses Python's internally implemented list function, index.
    def searchArrayList(self, value):

        try:
            index = self.aList.index(value)
            return True
        except:
            return False

    # -------------------------------------------------------------------------

    # Get an item at a specified index
    #
    # Performs error checking prior to making query.
    def getItemAtIndex(self, index):

        if type(index) is not int:
            print("getItemAtIndex Error: Index argument must be integer")
            return False

        if (index < 0 or index > self.length):
            print("getItemAtIndex Error: Index is not in valid range of ArrayList")
            print("getItemAtIndex Error: Index passed is '%d' ArrayList length is '%d'" % (index, self.length))
            return False

        return self.aList[index]

    # -------------------------------------------------------------------------


    # Insert an item at the end of the ArrayList
    #
    # Ensures there are no duplicates and that the ArrayList is not full
    def insertAtEnd(self, value):

        # Make sure the item does not already exist in the list
        if self.searchArrayList(value):
            print("Item '%s' already exists in the list.  Cannot add" % str(value))
            return False

        # Make sure list is not full
        if self.isFull():
            print("insertAtEnd Error: List is full, cannot add any more")
            return False

        if (self.length >= len(self.aList)):
            self.aList.append(value)
        else:
            self.aList[self.length] = value

        self.length += 1

        return True

    # -------------------------------------------------------------------------

    # Insert an item at a specified index
    #
    # Ensures the item does not already exist.  If inserted, the remaining
    # items are shifted to the right by 1
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

        # Make sure list is not full

        if self.isFull():
            print("getItemAtIndex Error: List is full, cannot add any more")
            return False

        # Make sure the item does not already exist in the list
        if self.searchArrayList(value):
            print("Item '%s' already exists in the list.  Cannot add" % str(value))
            return False

        self.aList.insert(index,value)

        self.length += 1
        return True

    # -------------------------------------------------------------------------

    # Check if item at index is equal to specified value
    #
    # Uses internal Python list built-ins
    def isItemAtEqual(self, index, value):

        try:
            loc = self.aList.index(value)
            if loc == index:
                return True
        except:
            return False

    # -------------------------------------------------------------------------

    # Remove item at index
    #
    # Ensures index is valid prior to removing
    def removeAtIndex(self, index):

        # Make sure index is an integer type
        if type(index) is not int:
            print("removeAtIndex Error: Index argument must be integer")
            return False

        if (index < 0 or index > self.length):
            print("removeAtIndex Error: Index is not in valid range of ArrayList")
            print("removeAtIndex Error: Index passed is '%d' ArrayList length is '%d'" % (index, self.length))
            return False

        value = self.aList[index]

        self.aList.remove(value)
        self.length -= 1

    # -------------------------------------------------------------------------

    # Remove value by name from list
    #
    # Ensures value exists prior to removing it
    def remove(self, value):

        try:
            self.aList.remove(value)
            self.length -= 1
        except:
            return False

        return True

    # -------------------------------------------------------------------------

    # Print the contents of the ArrayList
    def printList(self):

        print("[ ", end="")
        for i in range(0, self.length):
            if (i%10 == 0 and i != 0):
                print("\n")
            print("%s, " % self.aList[i], end="")

        print("]\n")

# -----------------------------------------------------------------------------
if __name__ == "__main__":

    # Create some input for the ArrayList.  Since this is Python we can mix
    # data types.
    inputList = [1,2,3,4,"ab",5,6,"de",3.14156,"pi?"]

    # Create an ArrayList
    arrayList = ArrayList(50)

    # Check the ArrayList actual Python list size and compare against internal
    # data structure tracker -- Should be equal always!
    print("ArrayList actual size=%d, Internal Tracker size=%d"
            % (len(arrayList.aList),arrayList.getLength()))

    for i in inputList:
        arrayList.insertAtEnd(i)

    print("ArrayList actual size=%d, Internal Tracker size=%d"
            % (len(arrayList.aList),arrayList.getLength()))
    arrayList.printList()

    # Insert some good and bad data
    arrayList.insertAtIndex(1,45) # Should work
    arrayList.printList()

    arrayList.insertAtIndex(40,"oops") # Should fail
    arrayList.printList()

    # Let's look for some data in the list
    print("Is '99' in the list at index '0'? ", arrayList.isItemAtEqual(0,99))

    # Remove value at index 2
    rem = arrayList.removeAtIndex(2)
    print("ArrayList actual size=%d, Internal Tracker size=%d"
            % (len(arrayList.aList),arrayList.getLength()))
    arrayList.printList()

    # Remove by value
    rem = arrayList.remove("notInThere") # Should fail
    print("ArrayList actual size=%d, Internal Tracker size=%d"
            % (len(arrayList.aList),arrayList.getLength()))
    arrayList.printList()

    rem = arrayList.remove("ab") # Should work
    print("ArrayList actual size=%d, Internal Tracker size=%d"
            % (len(arrayList.aList),arrayList.getLength()))
    arrayList.printList()

    arrayList.clear()
    print("ArrayList actual size=%d, Internal Tracker size=%d"
            % (len(arrayList.aList),arrayList.getLength()))
    arrayList.printList()

    # Create an ArrayList
    arrayList2 = ArrayList(10)

    for i in inputList:
        arrayList2.insertAtEnd(i)
    print("ArrayList2 actual size=%d, Internal Tracker size=%d"
            % (len(arrayList2.aList),arrayList2.getLength()))
    arrayList2.printList()

    # Try to add one more item, should fail since list is full
    arrayList2.insertAtEnd(999)
    print("ArrayList2 actual size=%d, Internal Tracker size=%d"
            % (len(arrayList2.aList),arrayList2.getLength()))
    arrayList2.printList()
