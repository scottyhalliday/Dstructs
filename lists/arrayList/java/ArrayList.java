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

  // Check if list is is full
  public boolean isFull() {
    if (this.length == this.maxSize) {
      return true;
    }
    return false;
  }

  // Inserts an item at the end of the list if it does not already exist
  // and the list is not full
  public void insertAtEnd(int value) {

    // Is the list already full?
    if (this.isFull()) {
      System.out.println("insertAtEnd Error: List is already full.  Cannot add additional values");
      return;
    }

    // Is this a dublicate item?  No duplicates
    if (this.searchArrayList(value)) {
      System.out.println("insertAtEnd Error: List is already contains value.  Cannot add duplicate values");
      return;
    }

    this.aList[this.length] = value;
    this.length++;
  }

  // Search the ArrayList for a value
  public boolean searchArrayList(int value) {
    for (int i=0; i<this.length; i++) {
      if (this.aList[i] == value) {
        return true;
      }
    }
    return false;
  }

  // Prints the contents
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

    int input[] = {1,2,3,3,5,6,7,8,9,10};

    // Initialize the array list
    intArrayList = new ArrayList(10);

    for (int i=0; i<10; i++) {
      intArrayList.insertAtEnd(input[i]);
    }

    intArrayList.printList();

    intArrayList.insertAtEnd(11);

  }

}
