# Linked List Queue Data Structure in C

This directory contains the code for a basic linked list queue developed in C.  Since C is a statically
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

The linked list queue has the following capabilities:
1. clear_queue
2. delete_queue
3. initialize_queue
4. is_empty
5. print_queue
6. print_queue_status
7. enqueue
8. dequeue
9. remove_at_index

Since this is a linked list implementation there is no limit on the size of the queue.  The maximum size
is limited to the capacity of your computer.

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
./int_linked_queue
./float_linked_queue
./string_linked_queue
```

I developed and compiled these on Linux Mint 19.  My *gcc* version is 7.3.0.

TODO:
1. Implement some basic search tools
2. Create functionality to read in large data sets to test data structure robustness
3. Create a more dynamic implementation which allows different data types to exist in the list.
