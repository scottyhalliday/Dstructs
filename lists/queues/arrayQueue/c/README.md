# Queue
## C Array List Implmentation

This implementation of a queue is done using an array list.  The queue uses a fixed size.  If the size of the queue
is exceeded then an error is thrown and the item is not added.  The implementations allow a queue of a specific type
to be created.
1. Integer
2. Double (Floating-Point)
3. String

A queue can only consist of a single data type and cannot use combinations.

To build and run the binaries do the following.

```bash
make
./int_array_queue
./float_array_queue
./string_array_queue
```

Additionally, the programs can be compiled with the debug flag which will allow the binaries to be scanned by a heap
leakage detector such as Valigrind.

```bash
make debug
../../../../valigrind_debug ./int_array_queue
../../../../valigrind_debug ./float_array_queue
../../../../valigrind_debug ./string_array_queue
```

This was compiled on Linux Mint 19 using *gcc* 7.3.0