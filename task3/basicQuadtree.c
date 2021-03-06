#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "quad_tree_structure.h"
#include "change_quadtree.h"
#include "change_quadtree.c"
#include "nodeValue.h"
#include "nodeValue.c"
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

  int st[2];

  st[0]=0;
  st[1]=0;
  Node *head;
  // make the head node
  head = makeNode( 0.0,0.0,0);
  // make a tree
  growTree(head);
  growTree(head);
  growTree(head);
  makechang(head,st);
  printf("The added node:%d    The removed node:%d\n",st[0],st[1]);
  // print the tree for Gnuplot
	writeTree( head );
	destroyTree(head);
  return 0;
}
