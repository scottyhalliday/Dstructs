# Binary Tree Data Structure

A binary tree data structure is modeled so that each node has at most two children referred to as the 
left and right child.

The contents within this directory are implementations of the linked list data structure.  Each language 
will build the data structure for three data types.
1. Integer
2. Double (Floating Point) 
3. String

For languages that support dynamic typing (i.e. Python, Ruby, etc.) these three types can easily coexist
in a single implementation.  For non-dynamic languages (i.e. C, Go, etc.) three seperate implementations
exist for the three types.  C++ implementation uses templates and lets the precompiler take care of the
three type builds while Java uses generic Objects to implement the data structure.  

## Implementation

A linked list is a combination of a value and an address wrapped up into a single structure.  The desired
value is stored and a link(pointer) points to the next item in the list.  The last item in the list always
points to NULL.  

A linked list is made up of a series of Nodes (depending how large your list is) and two seperate nodes
called the **HEAD** and the **TAIL**.  The **HEAD** always points to the beginning of the list while the
**TAIL** always points to the end.

Each node is dynamically initialized in memory as it is needed.  For this reason a known initial size is
not needed which makes this a very useful data structure.  While the data structure requires an additional
item to point to another memory location, it still serves as a very robust data structure.

The figure below shows the basic structure of a single linked list.

![alt text](./linked_list1.png "Linked List Data Structure Overview")

### Inserting

Inserting items into a linked list is much like an array.  You can specify the index, head or tail.  From
these locations the data structure will insert the node by breaking appropriate pointers/links, inserting
the new node and then reestablish pointers/links appropriately.

The figure below shows a basic insert.

![alt text](./linked_list2.png "Linked List Data Insertion Overview")

Since there is no dependency on the size of the list and the fact that memory is dynamically allocated,
there is no need to know the initial size of the list.  Theoretically, you can continue to add new items
until you run out of memory.

### Deleting

Deleting nodes is similar to inserting.  You can delete a node at a given index, head or tail.  The data
structure will remove pointers/links to the deleted node and then reassign pointers/links to reflect the 
new list.

The figure below shows a basic delete.

![alt text](./linked_list3.png "Linked List Data Deletion Overview")

### Applications

While this implementation only considers a singly linked list (one direction) this can be easily extended
to create doubly-linked lists and circular-linked lists.