#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "quad_tree_structure.h"
#include "creatNode.h"
#include "creatNode.c"
#include "writeTree.h"
#include "writeTree.c"
#include "destroyTree.h"
#include "destroyTree.c"
#include "removeChildren.h"
#include "removeChildren.c"
#include "growTree.h"
#include "growTree.c"
// main
int main( int argc, char **argv ) {

  Node *head;
  int st[2];
  // make the head node
  head = makeNode( 0.0,0.0,0);
  // make a tree
  growTree( head );
  growTree(head);
  removeChild(head->child[2]);
  // print the tree for Gnuplot
	writeTree( head );
  destroyTree(head);
  return 0;
}
