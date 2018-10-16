//
// ArrayList.js
// By Scott Hall
//
class ArrayList {

  // Initialize the object.  If isStrict is true then the list only allows
  // data types consistent with the first item added
  constructor(size, isStrict) {
    if (isStrict == undefined) {
      this.isStrict = false;
    } else {
      this.isStrict = true;
    }
    this.maxSize = size;
    this.length  = 0;
    this.aList   = [];
  }

  // --------------------------------------------------------------------------

  // Get the max size of the list
  get getMaxSize() {
    return this.maxSize;
  }

  // --------------------------------------------------------------------------

  // Return whether the list is full or not
  get isFull() {
    if (this.length == this.maxSize) {
      return true;
    }
    return false;
  }

  // --------------------------------------------------------------------------

  // Return whether the list is empty or not
  get isEmpty() {
    if (this.length == 0) {
      return true;
    }
    return false;
  }

  // --------------------------------------------------------------------------

  // Clear the list. This simply sets the length indexer to zero.  No actual
  // list deletion is performed.  New values will simply overwrite old values.
  clear() {
    this.length = 0;
  }

  // --------------------------------------------------------------------------

  // Check if an item is in the list
  searchArrayList(value) {
    return this.aList.indexOf(value);
  }

  // --------------------------------------------------------------------------

  // Insert an item at the end of the list, providing it does not exist
  insertAtEnd(value) {

    // Is the list already full?
    if (this.isFull) {
      console.log("insertAtEnd Error:  List is full. Cannot add new item");
      return false;
    }

    // Is item already in the list?
    if (this.searchArrayList(value) != -1) {
      console.log("insertAtEnd Error: List already contains value '%s'.  Cannot add item", value);
      return false;
    }

    // Otherwise we can add item
    this.aList.push(value);

    // Increment the length indexer
    this.length++;

    return true;

  }

  // --------------------------------------------------------------------------

  // Insert an item at the specified index.  This will insert the item at the
  // index specified and shift all values to the right of insertion point.
  // The list cannot be full and the item cannot exist currently in the list
  insertAtIndex(index, value) {

    // Is the list already full?
    if (this.isFull) {
      console.log("insertAtIndex Error:  List is full. Cannot add new item");
      return false;
    }

    // Is item already in the list?
    if (this.searchArrayList(value) != -1) {
      console.log("insertAtIndex Error: List already contains value '%s'.  Cannot add item", value);
      return false;
    }

    // Is the index in the appropriate range
    if (index < 0 || index > this.length) {
      console.log("insertAtIndex Error: Index is outside of list current range.  Cannot add item");
      return false;
    }

    // Let's add the value at index, remove 0 items and let this internal
    // function shift everything else
    this.aList.splice(index, 0, value);

    // Increment the length indexer
    this.length++;

    return true;
  }

  // --------------------------------------------------------------------------

  // Remove an item at a give index
  removeAtIndex(index) {

    // Is the index in the appropriate range
    if (index < 0 || index > this.length) {
      console.log("insertAtIndex Error: Index is outside of list current range.  Cannot add item");
      return false;
    }

    this.aList.splice(index, 1);

    this.length--;

    return true;

  }

  // --------------------------------------------------------------------------

  // Remove an item by value from the list
  remove(value) {

    var index = this.searchArrayList(value);

    // Is item already in the list?
    if (index == -1) {
      console.log("remove Error: List does not contain value '%s'.  Cannot remove item", value);
      return false;
    }

    this.aList.splice(index,1);

    this.length--;

  }

  // --------------------------------------------------------------------------

  // Return the item at the given index
  getItemAtIndex(index) {

    // Is the index in the appropriate range
    if (index < 0 || index > this.length) {
      console.log("getItemAtIndex Error: Index is outside of list current range.");
      return false;
    }

    return this.aList[index];
  }

  // --------------------------------------------------------------------------

  // Print the list content
  printList() {
    var i;
    console.log("\n Array List Content:");
    for (i=0; i<this.length; i++) {
      if (i != 0 && i % 10 == 0) {
        console.log("");
      }
      process.stdout.write(this.aList[i] + ", ");
    }
    console.log("\n\n");
  }

}

// --------------------------------------------------------------------------
// Main
// Do some testing

var intArrayList = new ArrayList(10);

intArrayList.insertAtEnd(1);
intArrayList.insertAtEnd(2);
intArrayList.insertAtEnd(3);
intArrayList.insertAtEnd(4);
intArrayList.insertAtEnd(5);
intArrayList.insertAtEnd(6);
intArrayList.insertAtEnd(7);
intArrayList.insertAtEnd(8);
intArrayList.insertAtEnd(9);
intArrayList.insertAtEnd(10);

console.log("\n INTEGER ONLY ARRAY LIST\n");

console.log(" Original List");
intArrayList.printList();

console.log("Let's remove item at index 4.  Should work");
intArrayList.removeAtIndex(4);
intArrayList.printList();

console.log("Let's remove item 9.  Should work");
intArrayList.remove(9);
intArrayList.printList();

console.log("Let's remove item 99.  Should fail since 99 isn't in the list");
intArrayList.remove(99);
intArrayList.printList();

console.log("Let's add item 99 to index 6.");
intArrayList.insertAtIndex(6, 99);
intArrayList.printList();

console.log("Let's return the item at index 2");
console.log("Item at index 2 is " + intArrayList.getItemAtIndex(2));
