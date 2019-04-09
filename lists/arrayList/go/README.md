# Go Implementation of Array List Data Structure

The ArrayList is a fixed array-based list which can store any data type
(consistent data type).  Since Go doesn't allow overloading, there are three
different implementations of the overall data structure.  One to support
integers, another to support double/floats and a final to support strings.
The available features for all three implementations are itemized below.
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

The workspace is setup consistent with Go practices.  The source files for
the different ArrayList's are in the **go/src/arrayList** directory.  The test
file is in the **go/src/test** directory.  This contains the main function call.
A simple makefile has been supplied to allow easy install of packages and
compile of the final executable named **test**.  A symbolic link will point to
the created **test** executable in the **go/bin** directory.  The GOPATH will be
set for the current workspace.

To build and test the binaries (Linux) a makefile was created to easily compile the code.

```bash
make
./test
```

Compiled with go version go1.10.1 linux/amd64
