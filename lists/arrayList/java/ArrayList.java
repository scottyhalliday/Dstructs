public class ArrayList {

  // Instance variables
  private int maxSize;
  private int length;
  private int aList[];

  // Constructor
  public ArrayList(int size) {
    this.maxSize = size;
    this.length  = 0;
    this.aList   = new int[size];
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
  public int searchArrayList(int value) {
    for (int i=0; i<this.length; i++) {
      if (this.aList[i] == value) {
        return i;
      }
    }
    return -1;
  }

  // --------------------------------------------------------------------------

  // Inserts an item at the end of the list if it does not already exist
  // and the list is not full
  public void insertAtEnd(int value) {

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
  public void insertAtIndex(int index, int value) {

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
    for (int i=this.length+1; i>index; i--) {
      this.aList[i] = this.aList[i-1];
    }

    // Add new item
    this.aList[index] = value;
    this.length++;

  }

  // --------------------------------------------------------------------------

  // Remove an item from the list.  Item needs to be in the list to remove
  public void remove(int value) {

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
  // index in range of current list size.
  public int getItemAtIndex(int index) {

    // Checks index is valid.  This should really be done prior to calling this
    // method since it is possible a return type of -1 could be in the list
    if (this.isIndexValid(index) == false) {
      System.out.println("getItemAtIndex Error: Index range is not valid.  Cannot remove");
      return -1;
    }

    return this.aList[index];
  }

  // --------------------------------------------------------------------------

  // Prints the contents of the list
  public void printList() {

    System.out.println(" Array List Content:");
    for (int i=0; i<this.length; i++) {
      if (i%10 == 0 && i != 0) {
        System.out.println("");
      }
      System.out.printf("%d, ", this.aList[i]);
    }
    System.out.println("");

  }

  public static void main(String[] args) {

    ArrayList intArrayList;

    int input[] = {1,2,3,4,5,6,7,8,9,10};
    int value;

    // Initialize the array list
    intArrayList = new ArrayList(10);

    for (int i=0; i<10; i++) {
      intArrayList.insertAtEnd(input[i]);
    }
    intArrayList.printList();

    System.out.println("\nLet's try to add 11 to the list.  Should fail, list is already full");
    intArrayList.insertAtEnd(11);
    intArrayList.printList();

    System.out.println("\nLet's remove the value 5 from the list");
    intArrayList.remove(5);
    intArrayList.printList();

    System.out.println("\nNow that we made space let's add 11 to the end of the list");
    intArrayList.insertAtEnd(11);
    intArrayList.printList();

    System.out.println("\nLet's remove the value at index 0 from the list");
    intArrayList.removeAtIndex(0);
    intArrayList.printList();

    System.out.println("\nLet's remove the value at index 100 from the list.  Should fail since index is out of range");
    intArrayList.removeAtIndex(100);
    intArrayList.printList();

    System.out.println("\nLet's remove the value at the last index from the list.");
    intArrayList.removeAtIndex(8);
    intArrayList.printList();

    System.out.println("\nLet's get a value from the list at a specified index");
    if (intArrayList.isIndexValid(20)) {
      value = intArrayList.getItemAtIndex(20);
      System.out.printf("Value got %d\n", value);
    } else {
      System.out.println("INVALID INDEX");
    }

    if (intArrayList.isIndexValid(4)) {
      value = intArrayList.getItemAtIndex(4);
      System.out.printf("Value got %d\n", value);
    } else {
      System.out.println("INVALID INDEX");
    }


  }

}
