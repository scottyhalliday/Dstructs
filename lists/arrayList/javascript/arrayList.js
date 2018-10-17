//
// ArrayList.js
// By Scott Hall
//
class ArrayList {

  // Initialize the object.  If isStrict is true then the list only allows
  // data types consistent with the first item added
  constructor(size, isStrict) {
    if (isStrict == undefined || isStrict == false) {
      this.isStrict = false;
    } else {
      this.isStrict = true;
    }
    this.maxSize = size;
    this.length  = 0;
    this.aList   = [];
    this.aType   = undefined;
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

    // If the list is strict then check the type of the value prior to adding
    if (this.isStrict && this.isEmpty == false) {
      if (this.aType != typeof(value)) {
        console.log("insertAtEnd Error: ArrayList is set to strict.  Value '%s' does not match array list type.  Cannot add", value);
        return false;
      }
    }

    // Set the array type if not done so already and list is strict
    if (this.aType == undefined && this.isStrict) {
      this.aType = typeof(value);
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

    // If the list is strict then check the type of the value prior to adding
    if (this.isStrict && this.isEmpty == false) {
      if (this.aType != typeof(value)) {
        console.log("insertAtIndex Error: ArrayList is set to strict.  Value '%s' does not match array list type.  Cannot add", value);
        return false;
      }
    }

    // Set the array type if not done so already and list is strict
    if (this.aType == undefined && this.isStrict) {
      this.aType = typeof(value);
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

var numArrayList = new ArrayList(10, true);
var mixArrayList = new ArrayList(10);

numArrayList.insertAtEnd(1);
numArrayList.insertAtEnd(2);
numArrayList.insertAtEnd(3);
numArrayList.insertAtEnd(4);
numArrayList.insertAtEnd(5);
numArrayList.insertAtEnd(6);
numArrayList.insertAtEnd(7);
numArrayList.insertAtEnd(8);
numArrayList.insertAtEnd(9);
numArrayList.insertAtEnd("Bad Value");

console.log("\n NUMBER ONLY ARRAY LIST\n");

console.log(" Original List");
numArrayList.printList();

console.log("Let's remove item at index 4.  Should work");
numArrayList.removeAtIndex(4);
numArrayList.printList();

console.log("Let's remove item 9.  Should work");
numArrayList.remove(9);
numArrayList.printList();

console.log("Let's remove item 99.  Should fail since 99 isn't in the list");
numArrayList.remove(99);
numArrayList.printList();

console.log("Let's add item 99 to index 6.");
numArrayList.insertAtIndex(6, 99);
numArrayList.printList();

console.log("Let's return the item at index 2");
console.log("Item at index 2 is " + numArrayList.getItemAtIndex(2));

mixArrayList.insertAtEnd(1);
mixArrayList.insertAtEnd(2);
mixArrayList.insertAtEnd(3);
mixArrayList.insertAtEnd(4);
mixArrayList.insertAtEnd("Hello");
mixArrayList.insertAtEnd(6);
mixArrayList.insertAtEnd(7);
mixArrayList.insertAtEnd(8);
mixArrayList.insertAtEnd(9);
mixArrayList.insertAtEnd("Ok");

console.log("\n MIXED ARRAY LIST\n");

console.log(" Original List");
mixArrayList.printList();

console.log("Let's remove item at index 4.  Should work");
mixArrayList.removeAtIndex(4);
mixArrayList.printList();

console.log("Let's remove item 'Hello'.  Should work");
mixArrayList.remove("Hello");
mixArrayList.printList();

console.log("Let's remove item 'Not in here'.  Should fail since 99 isn't in the list");
mixArrayList.remove("Not in here");
mixArrayList.printList();

console.log("Let's add item 'Not in here' to index 6.");
mixArrayList.insertAtIndex(6, "Not in here");
mixArrayList.printList();

console.log("Let's return the item at index 2");
console.log("Item at index 2 is " + mixArrayList.getItemAtIndex(2));
