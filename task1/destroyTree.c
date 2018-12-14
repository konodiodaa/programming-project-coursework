//destroy the whole tree and release all the storage
void destroyTree(Node *head)
{
   	int i;
	if(head->child[0]!=NULL)//go to the next level if it not a leaf node
	{
		for(i=0;i<4;i++)
		{
			destroyTree(head->child[i]);
		}
		free(head);
		head==NULL;
	}else //destroy only when it is a leaf node
	{
		free(head);
		head==NULL;
	}
}
