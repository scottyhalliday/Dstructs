public class ArrayList<T> {

  // Instance variables
  private int maxSize;
  private int length;
  private T   aList[];

  // Constructor
  public ArrayList(int size) {
    this.maxSize = size;
    this.length  = 0;
    this.aList = (T[]) new Object[size];
  }

  // --------------------------------------------------------------------------

  // Get the class instance for the maximum ArrayList size
  public int getMaxSize() {
    return this.maxSize;
  }

  // --------------------------------------------------------------------------

  // Get current length of the ArrayList
  public int getLength() {
    return this.length;
  }

  // --------------------------------------------------------------------------

  // Check if list is is full
  public boolean isFull() {
    if (this.length == this.maxSize) {
      return true;
    }
    return false;
  }

  // --------------------------------------------------------------------------

  // Check if the list is is empty
  public boolean isEmpty() {
    if (this.length == 0) {
      return true;
    }
    return false;
  }

  // --------------------------------------------------------------------------

  // Clear the list.  Simply return the length index back to zero
  public void clear() {
    this.length = 0;
  }

  // --------------------------------------------------------------------------

  // Is index valid?
  public boolean isIndexValid(int index) {
    if (index < 0 || index > this.length) {
      return false;
    }
    return true;
  }

  // --------------------------------------------------------------------------

  // Search the ArrayList for a value
  public int searchArrayList(T value) {

    // Use String class to compare so that we are comparing values
    // rather than comparing objects
    String sValue = new String();

    sValue = sValue.valueOf(value);

    for (int i=0; i<this.length; i++) {
      if (sValue.equals(String.valueOf(this.aList[i]))) {
        return i;
      }
    }
    return -1;

  }

  // --------------------------------------------------------------------------

  // Inserts an item at the end of the list if it does not already exist
  // and the list is not full
  public void insertAtEnd(T value) {

    // Is the list already full?
    if (this.isFull()) {
      System.out.println("insertAtEnd Error: List is already full.  Cannot add additional values");
      return;
    }

    // Is this a dublicate item?  No duplicates
    if (this.searchArrayList(value) != -1) {
      System.out.println("insertAtEnd Error: List is already contains value.  Cannot add duplicate values");
      return;
    }

    this.aList[this.length] = value;
    this.length++;
  }

  // --------------------------------------------------------------------------

  // Insert at a specified index.  Array cannot be full, value cannot exist
  public void insertAtIndex(int index, T value) {

    // Is the list already full?
    if (this.isFull()) {
      System.out.println("insertAtIndex Error: List is already full.  Cannot add additional values");
      return;
    }

    // Is this a dublicate item?  No duplicates
    if (this.searchArrayList(value) != -1) {
      System.out.println("insertAtIndex Error: List is already contains value.  Cannot add duplicate values");
      return;
    }

    // Make sure index range is valid
    if (this.isIndexValid(index) == false) {
      System.out.println("insertAtIndex Error: Index is out of range.  Cannot add");
    }

    // Move all items over to make room for new value
    for (int i=this.length; i>index; i--) {
      this.aList[i] = this.aList[i-1];
    }

    // Add new item
    this.aList[index] = value;
    this.length++;

  }

  // --------------------------------------------------------------------------

  // Remove an item from the list.  Item needs to be in the list to remove
  public void remove(T value) {

      int index;

      // See if value is in the ArrayList
      index = this.searchArrayList(value);

      if (index == -1) {
        System.out.println("remove Error: Value is not in list.  Cannot remove");
        return;
      }

      // Move all items to the right of removed item over
      for (int i=index; i<this.length-1; i++) {
        this.aList[i] = this.aList[i+1];
      }

      this.length--;
  }

  // --------------------------------------------------------------------------

  // Remove an item from the list for a given index.  Of course make sure the
  // index range is valid
  public void removeAtIndex(int index) {

      if (this.isIndexValid(index) == false) {
        System.out.println("removeAtIndex Error: Index range is not valid.  Cannot remove");
        return;
      }

      // Move all items to the right of removed item over
      for (int i=index; i<this.length-1; i++) {
        this.aList[i] = this.aList[i+1];
      }

      this.length--;
  }

  // --------------------------------------------------------------------------

  // Return the value at the specified index in the ArrayList.  Checks for
  // index in range of current list size.  To keep this somewhat generic
  // this returns an object and it is the responsibility of the programmer
  // to cast it approprietly
  public Object getItemAtIndex(int index) {

    Object obj = new Object();

    // Checks index is valid.  This should really be done prior to calling this
    // method since it is possible a return type of -1 could be in the list
    if (this.isIndexValid(index) == false) {
      System.out.println("getItemAtIndex Error: Index range is not valid.  Cannot remove");
      return null;
    }
    obj = this.aList[index];
    return obj;

  }

  // --------------------------------------------------------------------------

  // Prints the contents of the list
  public void printList() {

    System.out.println(" Array List Content:");
    for (int i=0; i<this.length; i++) {
      if (i%10 == 0 && i != 0) {
        System.out.println("");
      }
      if (this.aList[i] instanceof Integer) {
        System.out.printf("%d, ", this.aList[i]);
      } else if (this.aList[i] instanceof Double) {
        System.out.printf("%f, ", this.aList[i]);
      } else {
        System.out.printf("%s, ", this.aList[i]);
      }
    }
    System.out.println("");

  }

  public static void main(String[] args) {

    ArrayList<Integer> intArrayList;
    ArrayList<Double> doubleArrayList;
    ArrayList<String> strArrayList;

    // Let's test the Generic class for Integers
    int input[] = {1,2,3,4,5,6,7,8,9,10};
    double inputDouble[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10};
    String inputStr[] = {"Hello", "There", "this", "is", "a", "String", "List"};
    int value;
    double dValue;
    String strValue;

    // Initialize the array list
    System.out.println(" TESTING INTEGER ARRAYLIST \n\n");
    intArrayList = new ArrayList<Integer>(10);

    for (int i=0; i<10; i++) {
      intArrayList.insertAtEnd(input[i]);
    }
    intArrayList.printList();

    System.out.println("\nLet's try to add '11' to the list.  Should fail, list is already full");
    intArrayList.insertAtEnd(11);
    intArrayList.printList();

    System.out.println("\nLet's remove the value '5' from the list");
    intArrayList.remove(5);
    intArrayList.printList();

    System.out.println("\nNow that we made space in the list let's add '11' to the end of the list");
    intArrayList.insertAtEnd(11);
    intArrayList.printList();

    System.out.println("\nLet's remove the value at index '0' from the list");
    intArrayList.removeAtIndex(0);
    intArrayList.printList();

    System.out.println("\nLet's remove the value at index '100' from the list.  Should fail since index is out of range");
    intArrayList.removeAtIndex(100);
    intArrayList.printList();

    System.out.println("\nLet's remove the value at the last index from the list.");
    intArrayList.removeAtIndex(8);
    intArrayList.printList();


    System.out.println("\nLet's get a value from the list at a specified index");
    System.out.println("Try to get a value from index '20' which doesn't exist so it should fail");
    if (intArrayList.isIndexValid(20)) {
      value = (Integer) intArrayList.getItemAtIndex(20);
      System.out.printf("Value got %d\n", value);
    } else {
      System.out.println("INVALID INDEX");
    }

    System.out.println("Try to get a value from index '4' which does exist so it should work");
    if (intArrayList.isIndexValid(4)) {
      value = (Integer) intArrayList.getItemAtIndex(4);
      System.out.printf("Value got %d\n", value);
    } else {
      System.out.println("INVALID INDEX");
    }

    // Initialize the array list
    System.out.println("\n\n TESTING DOUBLE ARRAYLIST \n\n");
    doubleArrayList = new ArrayList<Double>(10);

    for (int i=0; i<10; i++) {
      doubleArrayList.insertAtEnd(inputDouble[i]);
    }
    doubleArrayList.printList();

    System.out.println("\nLet's try to add '11.0' to the list.  Should fail, list is already full");
    doubleArrayList.insertAtEnd(11.0);
    doubleArrayList.printList();

    System.out.println("\nLet's remove the value '5.5' from the list");
    doubleArrayList.remove(5.5);
    doubleArrayList.printList();

    System.out.println("\nNow that we made space in the list let's add '11.0' to the end of the list");
    doubleArrayList.insertAtEnd(11.0);
    doubleArrayList.printList();

    System.out.println("\nLet's remove the value at index '0' from the list");
    doubleArrayList.removeAtIndex(0);
    doubleArrayList.printList();

    System.out.println("\nLet's remove the value at index '100' from the list.  Should fail since index is out of range");
    doubleArrayList.removeAtIndex(100);
    doubleArrayList.printList();

    System.out.println("\nLet's remove the value at the last index from the list.");
    doubleArrayList.removeAtIndex(8);
    doubleArrayList.printList();


    System.out.println("\nLet's get a value from the list at a specified index");
    System.out.println("Try to get a value from index '20' which doesn't exist so it should fail");
    if (doubleArrayList.isIndexValid(20)) {
      dValue = (Double) doubleArrayList.getItemAtIndex(20);
      System.out.printf("Value got %f\n", dValue);
    } else {
      System.out.println("INVALID INDEX");
    }

    System.out.println("Try to get a value from index '4' which does exist so it should work");
    if (doubleArrayList.isIndexValid(4)) {
      dValue = (Double) doubleArrayList.getItemAtIndex(4);
      System.out.printf("Value got %f\n", dValue);
    } else {
      System.out.println("INVALID INDEX");
    }

    // Initialize the array list
    System.out.println("\n\n TESTING STRING ARRAYLIST \n\n");
    strArrayList = new ArrayList<String>(7);

    for (int i=0; i<7; i++) {
      strArrayList.insertAtEnd(inputStr[i]);
    }
    strArrayList.printList();

    System.out.println("\nLet's try to add another item to the list.  Should fail since list is full");
    strArrayList.insertAtEnd("Super");
    strArrayList.printList();

    System.out.println("\nLet's remove 'There' so we can free some space");
    strArrayList.remove("There");
    strArrayList.printList();

    System.out.println("\nNow let's try to again to add 'Super' now that the list has space");
    strArrayList.insertAtEnd("Super");
    strArrayList.printList();

    System.out.println("\nLet's try to remove a specific index, '2'");
    strArrayList.removeAtIndex(2);
    strArrayList.printList();

    System.out.println("\nLet's try to put 'work?' into index 2");
    strArrayList.insertAtIndex(2, "work?");
    strArrayList.printList();

    System.out.println("\nLet's try to get the value at index 5");
    if (strArrayList.isIndexValid(4)) {
      strValue = (String) strArrayList.getItemAtIndex(5);
      System.out.printf("Value got '%s'\n", strValue);
    } else {
      System.out.println("INVALID INDEX");
    }

  }
}
