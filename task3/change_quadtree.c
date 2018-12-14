#include "nodeValue.h"
#include "removeChildren.h"
#include "creatNode.h"
// calculate the flag of each node
void calflag(Node *node)
{
  double value;

  value=nodeValue(node,0);
  if(value>0.5)//calculate the flag of the node assume it is a leaf node
  {
    node->flag=1;
  }
  else if(value<-0.5)
  {
    node->flag=-1;
  }

  if(node->child[0]!=NULL)//set flag to zero if it`s not a leaf node
  {
    node->flag=0;
  }
}

//add node or remove node according to the flag of each node
int *makechang(Node *node,int st[])
{
  int isremove;
  int i;

  calflag(node);
  if(node->flag==1)//leaf node and flag is 1, make children fot it
  {
    makeChildren(node);
    st[0]+=4;
    node->flag=0;
  }
  else if(node->child[0]!=NULL && node->child[0]->child[0]==NULL)//second last level node
  {
    isremove=1;
    for(i=0;i<4;i++)
    {
      calflag(node->child[i]);
      if(node->child[i]->flag!=-1)//if any one of the flag of this its chilren is not -1,set isremove to 0
      {
        isremove=0;
      }
    }
    if(isremove)//if isremove is not be set to 0 remove its children
    {
      st[1]+=4;
      removeChild(node);
      makechang(node,st);
    }
    else
    {
      for(i=0;i<4;i++)
      {
        makechang(node->child[i],st);
      }
    }
  }
  else if(node->child[0]!=NULL && node->child[0]->child[0]!=NULL)//if it is a node in the middle or top,go to next level
  {
      for(i=0;i<4;i++)
      {
        makechang(node->child[i],st);
      }
  }

}
