#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// tree data structure

struct qnode {
  int flag;
  int level;
  double xy[2];
  struct qnode *child[4];
};
typedef struct qnode Node;

// function definitions

double nodeValue( Node *node, double time );
double value( double x, double y, double time);
Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void writeTree( Node *head );
void writeNode( FILE *fp, Node *node );
void printOut( FILE *fp, Node *node );
void growTree(Node *current);
void removeChild(Node *parent);
int *adapt(Node *head,int st[2]);
void calflag(Node *node);
// main


int main( int argc, char **argv ) {

  Node *head;
  int st[2];

  // make the head node
  head = makeNode( 0.0,0.0,0);

  // make a tree
  growTree( head );
  growTree(head);
  growTree(head);

  do
  {
    st[0]=0;
    st[1]=0;
    adapt(head,st);
    printf("The number of addChild: %d\nThe number of removeChild: %d\n",st[0],st[1]);
  }while((st[0]!=0 && st[1]!=0));

  // print the tree for Gnuplot
	writeTree( head );
  return 0;
}

//calculate the flag of the node
void calflag(Node *node)
{
  double value;

  value=nodeValue(node,0);
  if(value>0.5)
  {
    node->flag=1;
  }
  else if(value<-0.5)
  {
    node->flag=-1;
  }

  if(node->child[0]!=NULL)
  {
    node->flag=0;
  }
}

//adpat the quadtree

int *adapt(Node *node,int st[])
{
  int isremove;
  int i;
  int maxlevel=6;

  calflag(node);
  if(node->flag==1 && node->level<maxlevel)
  {
    makeChildren(node);
    node->flag=0;
    for(i=0;i<4;i++)
    {
      st[0]++;
      adapt(node,st);
    }
  }
  else if(node->child[0]!=NULL && node->child[0]->child[0]==NULL)
  {
    isremove=1;
    for(i=0;i<4;i++)
    {
      calflag(node->child[i]);
      if(node->child[i]->flag!=-1)
      {
        isremove=0;
      }
    }
    if(isremove)
    {
      st[1]+=4;
      removeChild(node);
      adapt(node,st);
    }
    else
    {
      for(i=0;i<4;i++)
      {
        adapt(node->child[i],st);
      }
    }
  }
  else if(node->child[0]!=NULL && node->child[0]->child[0]!=NULL)
  {
      for(i=0;i<4;i++)
      {
        adapt(node->child[i],st);
      }
  }

  return st;
}

// Evaluate function at centre of quadtree node

double nodeValue( Node *node, double time ) {

  int level = node->level;
  double x = node->xy[0];
  double y = node->xy[1];

  double h = pow(2.0,-level);

  return( value( x+0.5*h, y+0.5*h, time ) );
}

// Data function

double value( double x, double y, double time ) {

  return( 2.0*exp(-8.0*(x-time)*(x-time)) - 1.0 ) ;
}

// make a node at given location (x,y) and level

Node *makeNode( double x, double y, int level ) {

  int i;

  Node *node = (Node *)malloc(sizeof(Node));

  node->level = level;

  node->xy[0] = x;
  node->xy[1] = y;
  node->flag=0;
  for( i=0;i<4;++i )
    node->child[i] = NULL;

  return node;
}

// split a leaf nodes into 4 children

void makeChildren( Node *parent ) {

  double x = parent->xy[0];
  double y = parent->xy[1];

  int level = parent->level;

  double hChild = pow(2.0,-(level+1));

  parent->child[0] = makeNode( x,y, level+1 );
  parent->child[1] = makeNode( x+hChild,y, level+1 );
  parent->child[2] = makeNode( x+hChild,y+hChild, level+1 );
  parent->child[3] = makeNode( x,y+hChild, level+1 );

  return;
}

//grow the Tree with a full level

void growTree(Node *parent)
{
  int i;
  if(parent->child[0]==NULL)
  {
      makeChildren(parent);
  }
  else
  {
      for(i=0;i<4;i++)
      {
          growTree(parent->child[i]);
      }
  }
}

//remove the children of a node

void removeChild(Node *parent)
{
  int i;
  if(parent->child[0]==NULL)
  {
    printf("This node doesn`t have children now");
  }
  else if(parent->child[0]!=NULL && parent->child[0]->child[0]!=NULL)
  {
    printf("Error, this node`s children are not leaf node!!!");
  }
  else
  {
    for(i=0;i<4;i++)
    {
      free(parent->child[i]);
      parent->child[i]=NULL;
    }
  }
}

//release all the storage

void destroyTree(Node *head)
{
  int i;
  if(head->child[0]==NULL)
  {
    free(head);
    head=NULL;
  }
  else
  {
    for(i=3;i>=0;i--)
    {
      destroyTree(head->child[i]);
    }
    destroyTree(head);
  }
}

// write out the tree to file 'quad.out'

void writeTree( Node *head ) {

  FILE *fp = fopen("quad.out","w");

  writeNode(fp,head);

  fclose(fp);

  return;
}

// recursively visit the leaf nodes

void writeNode( FILE *fp, Node *node ) {

  int i;

  if( node->child[0] == NULL )
    printOut( fp, node );
  else {
    for ( i=0; i<4; ++i ) {
      writeNode( fp, node->child[i] );
    }
  }
  return;
}

// write out the (x,y) corners of the node

void printOut( FILE *fp, Node *node ) {
  double x = node->xy[0];
  double y = node->xy[1];
  int level = node->level;
  double h = pow(2.0,-level);

  fprintf(fp, " %g %g\n",x,y);
  fprintf(fp, " %g %g\n",x+h,y);
  fprintf(fp, " %g %g\n",x+h,y+h);
  fprintf(fp, " %g %g\n",x,y+h);
  fprintf(fp, " %g %g\n\n",x,y);

  return;
}
