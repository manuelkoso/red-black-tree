# Red-black-tree

This repository contains a red black tree implementation for the Advanced Programming course 
exam. 

From [ 1 ], a red-black tree is a binary tree that satisfies the following red-black properties:
1. Every get_node is either red or black.
2. The root is black.
3. Every leaf ( NIL) is black.
4. If a get_node is red, then both its children are black.
5. For each get_node, all simple paths from the get_node to descendant leaves contain the
same number of black nodes.

## Project structure

The `include` folder contains the implementation 
of the `RBTree` class (and the `catch.hpp` header). For readability reasons, the implementation 
is split among different files as follows:
- `RBTree.h`: declaration of the RBTree class
- `RBTNode.h`: implementation of the private struct Node
- `RBTCheckPropertiesFunctions.h`: implementation of functions that check black properties
- `RBTConstIterator.h`: implementation of the constant forward iterator
- `RBTInterface.h`: implementation of the public methods
- `RBTPrivateFunctions`: implementation of the private functions

In the `test` folder there are all the tests that verify the public interface and a simple benchmark. There are 8 test cases:
- Initialization
- Insertion
- Deletion
- Searching
- Move semantics
- Copy semantics
- Iterator
- Output operator 

The benchmark compares the `contains` function with the `find` function of the `std::set` container.  

## Implementation choices

- I considered the NIL node as `nullptr`.
- `Node` is a private nested struct of the `RBTree` class.
- I used `std::unique_ptr` to avoid any memory leaks.
- At the end of the `insert` and `erase` functions I put an assertion that check if
the tree still satisfies the red black properties. When benchmarking the assertion is disabled with
`NDEBUG` flag.

## Building and running

### Build project
```commandline
mkdir RBT-build
cd RBT-build
cmake ../
cmake --build .
```
### Run tests
```commandline
./RBT-test
```
### Benchmark
```commandline
./RBT-benchmark
```

## References
[ 1 ] <cite>Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford
  Stein. Introduction to Algorithms. The MIT Press, 2nd edition, 2001</cite>