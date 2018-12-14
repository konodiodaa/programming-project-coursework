//destroy the whole tree and release all the storage
void destroyTree(Node *head)
{
  	int i;
	if(head->child[0]!=NULL)// go to next level when it not a leaf node
	{
		for(i=0;i<4;i++)
		{
			destroyTree(head->child[i]);
		}
		free(head);
		head==NULL;
	}else //destroy the node only if it is a leaf node
	{
		free(head);
		head==NULL;
	}
}
