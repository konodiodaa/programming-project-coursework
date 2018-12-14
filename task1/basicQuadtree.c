
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "quad_tree_structure.h"
#include "createnode.h"
#include "createnode.c"
#include "writeTree.h"
#include "writeTree.c"
#include "growTree.h"
#include "growTree.c"
#include "destroyTree.h"
#include "destroyTree.c"

// main

int main( int argc, char **argv ) {
  Node *head;

  // make the head node
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  growTree(head);
  growTree(head);

  // print the tree for Gnuplot
	writeTree( head );
  destroyTree(head);
  return 0;
}
