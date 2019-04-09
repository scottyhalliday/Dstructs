# Array List Data Structure

The contents within this directory are implementations of the array list data structure.  This data structure
uses the languages built in array functionality to build the data structure.  Each language will build the
data structure for three data types.
1. Integer
2. Double (Floating Point) 
3. String

For languages that support dynamic typing (i.e. Python, Ruby, etc.) these three types can easily coexist
in a single implementation.  For non-dynamic languages (i.e. C, Go, etc.) three seperate implementations
exist for the three types.  C++ implementation uses templates and lets the precompiler take care of the
three type builds while Java uses generic Objects to implement the data structure.  

## Implementation

At the core an array list data structure uses an array to store and manage data.  Essentially it is more
advanced wrapper around a normal array.  This data structure will manage the insertion and deletion of 
data while ensuring that data is shifted appropriately to keep it sequential.  

The figure below shows an example of the array list data structure.

![alt text](./array_list1.png "Array List Data Structure Overview")
