# Ruby Implementation of Array List Data Structure

The ArrayList is a fixed array-based list which can store any data type
(consistent data type).  Ruby allows multiple different data types (objects)
to exist in its arrays.  For that reason a 'strict' argument is added to 
the initialization of the ArrayList class that, when set to true, will 
ensure that data types are all of the same type in the list.  The datatype 
chosen is based on the first one passed.  After that all added items must be 
the same data type or else an error is thrown.  If you wish for strict data 
typing to be disabled then simply pass false to the ArrayList initializer.  
This implementation takes advantage of Ruby's built-in convenience features 
such as removing items from the array.  The features implemented for this 
data structure are described below.
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

To view the small test suite connected to this program simply launch
arrayList.py with your Python3 interpreter.

```bash
ruby ArrayList.rb
```

I used Ruby 2.5.1p57 on x86_64-linux-gnu for this development.

