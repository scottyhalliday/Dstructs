# Stack
## C Linked List Implmentation

This implementation of a stack is done using a linked list.  Since this is implemented with a linked list there is no size restriction.  The implementations allow a stack of a specific type
to be created.
1. Integer
2. Double (Floating-Point)
3. String

A stack can only consist of a single data type and cannot use combinations.  Additionally, this implementation is not
such that you can create multiple instances of the stack.  The code works with a single stack mainly to just demonstrate
functionallity.  If you want the code to be able to handle a number of different stacks then you would need to extend
this code to allow that.  It would really be a seperate struct that embeds the core functionallity of this code and
then adding function arguments to handle the stack structs.

This was compiled on Linux Mint 19 using *gcc* 7.3.0