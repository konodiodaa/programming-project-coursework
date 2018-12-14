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
