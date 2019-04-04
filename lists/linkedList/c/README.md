# Linked List Data Structure in C

This directory contains the code for a basic linked list developed in C.  Since C is a statically
typed language, multiple instances needed to be created based on the type of the value being stored.
This is a bit redundant since most of the code does not change just the type of the variable
stored.  

The main types supported are
1. Integer
2. Double (Floating point)
3. String

These implementations do not allow the three types to be used together in a single list.  This can
be achieved with unions or a more intelligent structure but since this is for simplicity I will 
keep the types seperate.

The linked lists have the following capabilities:
1. get_list_length
2. get_node_at_index
3. initialize_linked_list
4. insert_node
5. insert_node_at_end
6. print_list
7. remove_node
8. remove_node_at_end
9. delete_list

To use this code simply execute the makefile

```bash
make
```

If you wish to enable the compiler debugger to check against tools like Valgrind then use the *debug* tag
in the makefile.

```bash
make debug
```

This will compile the three C files and produce three seperate binaries.  There is no command line
interface with these programs.  The testing of the program is done in the *main* method.  To launch
these simply call them in your shell.

```bash
./int_linked_list
./float_linked_list
./string_linked_list
```

I developed and compiled these on Linux Mint 19.  My *gcc* version is 7.3.0.

TODO:
1. Implement some basic search tools
2. Create functionality to read in large data sets to test data structure robustness
3. Create a more dynamic implementation which allows different data types to exist in the list.
