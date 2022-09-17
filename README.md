# Red-black-tree

This repository contains a red black tree implementation for the Advanced Programming course 
exam. 

From [1], a red-black tree is a binary tree that satisfies the following red-black properties:
1. Every node is either red or black.
2. The root is black.
3. Every leaf ( NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain the
same number of black nodes.

## Project structure

The `include` folder contains the implementation 
of the `RBTree` class (and the `catch.hpp` header). For readability reasons, the implementation 
is split among different files as follows:
- `RBTree.h`: declaration of the RBTree class
- `RBTNode.h`: implementation of the private struct Node
- `RBTCheckPropertiesFunctions.h`: implementation of functions that check 2, 4 and 5 red black properties
- `RBTConstIterator.h`: implementation of the constant forward iterator
- `RBTInterface.h`: implementation of the public methods
- `RBTPrivateFunctions`: implementation of the private functions

In the `test_tree` folder there are all the tests that verify the public interface. There are 8 test_tree cases:
- Red black tree initialization
- Insertion
- Deletion
- Searching
- Move semantics
- Copy semantics
- Iterator
- Output operator 


## Implementation choices

I considered the NIL node as `nullptr`.

The right and the left members of the `RBTree<T, CMP>::Node` class (that represent
the right and the left child of the node) are unique pointers, unlike of the parent member
(that represent the parent node) that is a raw pointer. I used unique pointers to avoid
memory leaks.

The implementation of the `insert` and `erase` public functions follows the pseudocode in [1]. 
I had to do some changes from the original pseudocode because of the unique pointers that don't permit copy
assignment. 

At the end of the `insert` and `erase` functions I put three assertions that check if
the tree still satisfies the 2, 4 and 5 red black properties. The functions that check
these properties are implemented in the `RBTCheckPropertiesFunctions.h` file.

## Building project and running tests

```commandline
mkdir RBT-build
cd RBT-build
cmake ../
cmake --build .
./RBT-test_tree
```

## References
[1] <cite>Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford
  Stein. Introduction to Algorithms. The MIT Press, 2nd edition, 2001</cite>