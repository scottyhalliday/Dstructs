# Binary Search Tree
## C Binary Search Tree Implementation

The C implementation of the binary tree consists of three data types:
1. Integer
2. Double (Floating Point)
3. String

Since C is a static typed language there are three different implementations to model integers,
floating point and string based trees.

This was compiled on Linux Mint 19 using *gcc* 7.3.0

## Running

To execute you simply need to build the executables.  A *makefile* was included for convenience.

```bash
make
```

Once the makefile has completed the binaries can be run.

```bash
./int_binary_search_tree
./float_binary_search_tree
./string_binary_search_tree
```

Additionally, the makefile also includes commands for compiling with debug mode.  This is useful if you want
to run various tools to check your code.  In particular I used Valgrind to detect memory leaks so I could
fix them.

```bash
make debug
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./int_binary_search_tree
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./float_binary_search_tree
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./string_binary_search_tree
```

You can quickly remove all built binaries by calling the *clean* tag in the makefile.

```bash
make clean
```