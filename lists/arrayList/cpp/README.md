# C++ Implementation of Array List Data Structure

The ArrayList is a fixed array-based list which can store any data type
(consistent data type).  The implementation in C++ uses the template feature
to allow single piece of code but usable for different datatypes.
The features implemented for this data structure are described below.
1. Create the list.  List is initialized to empty state
2. Determine whether the list is full
3. Determine whether the list is empty
4. Find the size of the list
5. Destroy/Clear the list
6. Determine whether an item is the same as a given list element
7. Insert an item in the list at a specified location
8. Remove an item from the list at a specified location
9. Replace an item at a specified location with another item
10. Retrieve an item at a specified location
11. Search the list for a given item

To build the binaries (Linux) a makefile was created to easily compile the code.

```bash
make
```

This will build a single binary.  The main method
for the program will test the functionality of the implementation.  To run the 
binary simply invoke it from the shell.

```bash
./arrayList
```

Additionally, you can build the binary with debugging to pass to a memory leak
detection program such as Valgrind.  You must have Valgrind installed to take
advantage of this.

```bash
make debug
../../../valigrind_debug ./arrayList
```

Compiled against g++ 7.3.0
