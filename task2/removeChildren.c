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
    for(i=0;i<4;i++)// remove the children of a node only it is a second last level node
    {
      free(parent->child[i]);
      parent->child[i]=NULL;
    }
  }
}
